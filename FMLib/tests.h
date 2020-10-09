#pragma once
#include <iostream>
#include "CallOption.h"
#include "Model.h"
#include "BlackScholes.h"
#include "matlib.h"
#include "matrix.h"
#include "objectiveFunction.h"


using namespace std;

// Test Functions
double square2(const Matrix& x);
Matrix squareM(const Matrix& x);

// Test Definitions
void testMatrixClass();
void testBlackScholesModel();
void testObjectiveFunction();



//========================================
// 		HELPER FUNCTIONS FOR TESTS
//========================================
double square2(const Matrix& x){
	int rows = x.nRow();
	double norm2 = 0.0;
	
	for (int i = 0; i < rows; i++){
		norm2 += 1/(x(i) * x(i));	
	}
	
	return norm2;
}


// Square function
Matrix squareM(const Matrix& x){
	int rows = x.nRow();
	Matrix result(rows);
	Matrix y = x;
	
	for (int i = 0; i < rows; i++){
		result(i) = (x(i) * y(i));	
	}
	
	return result;
}

//----------------------------------
// 		TEST DEFINITIONS
//----------------------------------

// Test Matrix Class
void testMatrixClass(){
	
	// Define the matrix
	Matrix mat(2, 2);
	mat.set(1, 1, 100.0);
	
	Matrix mat2(2, 2);
	mat2.set(1, 1, 100.0);
	mat2 = mat2 + 1.0;
	mat = mat + 100.0;
	
	// Matrix multiplication
	Matrix mat3 = mat * mat2;
	
	// Test for single row as matrix
	Matrix rowMatrix(10);
	
	// Assigning random numbers to matrix	
	Matrix test = randGaussianVector(10);
	int cols = test.nCol();
	int rows = test.nRow();
	
	cout << cols << "\n";
	cout << test(9)  << "\n";
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
	Matrix test1 = model.RNPricePathGenerator(1.0, 12.0);
	Matrix test2 = model.RNPricePathGenerator(1.0, 12.0);
	Matrix test3 = model.RNPricePathGenerator(1.0, 12.0);
}


void testObjectiveFunction(){
	
	Matrix input = randGaussianVector(10);
	RealVectFunction testFunc(square2);
	Matrix derive = testFunc.gradient(input);
	Matrix hess = testFunc.hessian(input);
	cout << input;
	cout << derive;
	cout << hess; 
	
	ObjectiveFunction testObj(squareM);
	Matrix jacobSlice = testObj.jacobian(input);
	cout << jacobSlice;}
