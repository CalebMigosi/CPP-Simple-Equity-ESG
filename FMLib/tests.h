#pragma once
#include <iostream>
#include "CallOption.h"
#include "Model.h"
#include "BlackScholes.h"
#include "matlib.h"
#include "objectiveFunction.h"
#include "optimize.h"

using namespace std;
using namespace Eigen;

// Test Functions
double square2(const VectorXd& x);
VectorXd squareM(const VectorXd& x);

// Test Definitions
void testVectorXdClass();
void testBlackScholesModel();
void testObjectiveFunction();


//========================================
// 		HELPER FUNCTIONS FOR TESTS
//========================================
double square2(const VectorXd& x){
	int rows = x.rows();
	double norm2 = 0.0;
	
	for (int i = 0; i < rows; i++){
		norm2 += 1/(x(i) * x(i));	
	}
	
	return norm2;
}


// Square function
VectorXd squareM(const VectorXd& x){
	int rows = x.rows();
	VectorXd result(rows);
	VectorXd y = x;
	
	for (int i = 0; i < rows; i++){
		result(i) = (x(i) * y(i));	
	}
	
	return result;
}


//----------------------------------
// 		TEST DEFINITIONS
//----------------------------------

// Test VectorXd Class
void testVectorXdClass(){
	
	// Define the VectorXd
	MatrixXd mat(2, 2);
	mat(1, 1) =  100.0;
	
	MatrixXd mat2(2, 2);
	mat2(1, 1) = 100.0;
	mat2 = mat2.array() + 1.0;
	mat = mat.array() + 100.0;
	
	cout << "First Matrix: \n";
	cout << mat;
	
	cout << "\n \n";
	cout << "Second Matrix: \n";
	cout << mat2;
		
	// VectorXd multiplication
	MatrixXd mat3 = mat * mat2;
	
	cout << "\n \n";
	cout << "Third Matrix: \n";
	cout << mat3;
	
	// Test for single row as VectorXd
	VectorXd rowVectorXd(10);
	
	// Assigning random numbers to VectorXd	
	VectorXd test = randGaussianVector(10);

	double meanTest = mean(test);
	 
	meanTest = sdev(test);
	double norm = square2(test);
	cout << meanTest  << "\n";
	
	cout << "Norm 2: \n";
	cout << norm  << "\n";
	
}


// Test Black Scholes Model
//--------------------------------
void testBlackScholesModel(){
	// Declare the black scholes model
	BlackScholes model;	
	model.interestRate = 0.01;
	model.stockPrice = 100;
	model.volatility = 0.25;
	
	// Test for the model call price
	cout << model.callPrice(100.0, 1.0) <<"\n";
	cout << model.putPrice(100.0, 1.0)<<"\n\n";
	
	// Test the Price path generator
	VectorXd test1 = model.RNPricePathGenerator(1.0, 12.0);
	VectorXd test2 = model.RNPricePathGenerator(1.0, 12.0);
	VectorXd test3 = model.RNPricePathGenerator(1.0, 12.0);
	
	// Print Values
	cout << "Gaussian Vector1 \n";
	cout << test1;
	cout << "\n \n";
	cout << "Gaussian Vector2 \n";
	cout << test2;
	cout << "\n \n";	cout << "Gaussian Vector3 \n";
	cout << test3;
	cout << "\n \n";	
}


void testObjectiveFunction(){
	
	VectorXd input = randGaussianVector(10);
	RealVectFunction testFunc(square2);
	VectorXd derive = testFunc.gradient(input);
	MatrixXd hess = testFunc.hessian(input);
	
	cout << "Input Vector: \n";
	cout << input;
	cout << "\n \n";
	
	cout << "Input Vector multiplied by 2: \n";
	cout << input.array()*2;
	cout << "\n \n";
		
	cout << "Derivative: \n";
	cout << derive;
	cout << "\n \n";
	cout << "Hessian: \n";
	cout << hess; 
	cout << "\n \n";
	
	ObjectiveFunction testObj(squareM);
	
	// Jacobian Test
	MatrixXd jacobSlice = testObj.jacobian(input);
	cout << "Jacobian: \n";
	cout << jacobSlice * testObj(input);
	cout << "\n \n";
	
	// Test for the optimizer
	CalibResult res;
	LevMarquardt calibrator;
	res = calibrator.calibrate(testObj, input);
	cout << res.initialParam;
	
	cout << "\n \n";
	cout << "Optimal Parameters: \n";
	cout << res.optimalParam;
	
	cout << "\n \n";
	cout << "SS Error: \n";
	cout << res.SSE;
	
	cout << "\n \n";
	cout << "Time Elapsed: \n";
	cout << res.timeElapsed;
	
	cout << "\n \n";
	cout << "Optimization Steps: \n";
	cout << res.iterations << " iterations \n \n";
	cout << res.optimizationSteps;
	}
	

