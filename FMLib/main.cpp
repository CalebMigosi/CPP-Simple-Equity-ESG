#include <iostream>
#include "CallOption.h"
#include "Model.h"
#include "BlackScholes.h"
#include "matlib.h"
#include "matrix.h"

using namespace std;

// Test Definitions
void testMatrixClass();

void testBlackScholesModel();


// MAIN
//===============================
int main(){
	
	// Test Matrix class
	testMatrixClass();
	testBlackScholesModel();
	
}


// TEST DEFINITIONS
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
	
	// Print matrices
	cout << mat3; 	
	cout << "\n";
	cout << rowMatrix;
	
	// Assigning random numbers to matrix	
	Matrix test = randGaussianVector(10);
	int cols = test.nCol();
	int rows = test.nRow();
	
	cout << cols << "\n";
	cout << test(9)  << "\n";
	double meanTest = mean(test);
	 
	meanTest = sdev(test);
	cout << meanTest  << "\n";
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
	cout << test1;
	
	Matrix test2 = model.RNPricePathGenerator(1.0, 12.0);
	cout << test2;
	
	Matrix test3 = model.RNPricePathGenerator(1.0, 12.0);
	cout << test3;
}
