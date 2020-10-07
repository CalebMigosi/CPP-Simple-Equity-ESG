#include <iostream>
#include "stdafx.h"
#include "matlib.h"

using namespace std;

// 64 bit Mersenne Twister
static 	mt19937_64 generator;

//				GAUSSIANS
//------------------------------------------------
// Generate a vector of gaussian generated random values
Matrix randGaussianVector(int length){
	// Length of the vector to be obtained
	Matrix result(length);
	
	// We use the 64 bit Mersenne Twister: For other examples (http://www.cplusplus.com/reference/random/)
	// This generates the random number i.e. uniforms
	
	// Define the distribution
	normal_distribution<double> gaussianFunc(0.0, 1.0);
	
	// Loop to generate the vector
	for (int i =0; i< length; i++){
		result(i) = gaussianFunc(generator);
	}
	
	return result; 
}

// Gaussian CDF for any x
//For more info: https://en.wikipedia.org/wiki/Error_function
double normCDF(double x){
	double proba = erfc( - x /sqrt(2.0))/2.0;
	return proba;
}


//				STATISTICS
//------------------------------------------------

// Vector Mean
double mean(const Matrix& inputVector){
	double sumTotal = 0.0;
	
	int n = inputVector.nRow();
	
	for(int i = 0; i < n; i++){
		sumTotal += inputVector(i);
	}
	
	return (sumTotal/(double) n );
}

//Vector std
double sdev(const Matrix& inputVector){
	int n = inputVector.nRow();
	
	double average = mean(inputVector);
	double sumSquares = 0;
	
	for(int i = 0; i<n; i++){
		sumSquares += square(inputVector(i) - average);
	}
	return sqrt(sumSquares/(double) n);
}


