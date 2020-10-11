#include "optimize.h"

using namespace std;
using namespace Eigen;

CalibResult LevMarquardt::calibrate(const ObjectiveFunction& func, const VectorXd& initialParam) const{
	// Container for the calibration result
	CalibResult result;
	
	// Will be used as a threshold to the tolerance
	double diff = 1.0;
	int iteration = 0;
	double alpha = 0.1;			// Convergence of damping parameter
	double lambda = 0.1;		// Convergence of damping parameter
	
	// Fill the data
	result.initialParam = initialParam;
	VectorXd paramT = initialParam;
	VectorXd paramTMinus1 = initialParam;
	
	// The specific during for the minimization
	MatrixXd steps(1, initialParam.rows());
	
	// Fill the first row with the initial parameters
	steps.row(0) = paramT;
	
	time_t start;
	while (diff > tolerance){
		// Add a row in steps
		steps.conservativeResize(iteration+1, NoChange);
		
		// Fill previous paramT to paramT-1
		paramTMinus1 = paramT;
		
		// Evaluate Function at T-1
		VectorXd fXminus1 = func(paramTMinus1);
		
		// Calculate Jacobian & pseudo inverse
		MatrixXd J = func.jacobian(paramTMinus1);
		MatrixXd Jt = J.transpose();
		
		// damping parameter
		double jrows = J.rows();
		MatrixXd damp = MatrixXd::Identity(jrows, jrows) * lambda;
		MatrixXd Jinverse = ((J * Jt) + damp).inverse() * Jt;
		
		// Xn = Xn-1 - ((Jacob_n)-1 x F(Xn-1)) 
		paramT = paramT - Jinverse * fXminus1;
		
		// Evaluate Function at T
		VectorXd fX = func(paramT);
		
		// Calculate sum of squared error using the 2 sets of parameters
		double errorXminus1 = fXminus1.squaredNorm();
		double errorX = fX.squaredNorm();
		
		// Increment in the damping factor
		// dot(w_trial, w)/ (norm(w_trial) x norm(x))
		double wip = paramT.dot(paramTMinus1)/(paramT.norm() * paramTMinus1.norm());
		
		if(errorX < errorXminus1){
			lambda = lambda * pow(alpha, wip);  // Decrease the damping parameter
			diff = errorXminus1 - errorX;		// Change the diff
		}else{
			// diff is not changed because convergence hasn't been reached
			lambda = lambda/alpha;				// Increase the damping parameter
		}
		
		//Add new params to steps
		steps.row(iteration) = paramT;
		iteration++;
	}
	time_t end;
	
	// Fill the result class
	result.optimalResult = func(paramT);
	result.timeElapsed = difftime(start, end);
	result.optimalParam = paramT;
	result.iterations = iteration;
	result.optimizationSteps = steps;
	return result;
}

