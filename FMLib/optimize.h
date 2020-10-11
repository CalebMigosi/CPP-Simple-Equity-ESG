#pragma once
#include "stdafx.h"
#include "objectiveFunction.h"

// Container for calibrated results
class CalibResult{
public:
	Eigen::VectorXd initialParam; 
	Eigen::VectorXd optimalParam;
	Eigen::MatrixXd optimizationSteps;
	Eigen::MatrixXd optimalResult;
	double SSE = optimalResult.squaredNorm();
	double timeElapsed;
	int iterations;
};

// Interface for optimization algorithms
class Optimizer{
public:
	// Calibrator
	virtual	CalibResult calibrate(const ObjectiveFunction& func, const Eigen::VectorXd& initialParam) const = 0;

	// Destructor
	virtual	~Optimizer(){};
	
};

// Levenberg Marquardt Algorithm
class LevMarquardt: public Optimizer{
public:	
	// Calibrator
	CalibResult calibrate(const ObjectiveFunction& func, const Eigen::VectorXd& initialParam) const;
	
private:
	double tolerance = 1e-12;
	int maxiter;
};
