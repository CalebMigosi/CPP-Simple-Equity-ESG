#include <iostream>
#include "stdafx.h"
#include "matlib.h"

using namespace std;

// 64 bit Mersenne Twister
static 	mt19937_64 generator;

//				GAUSSIANS
//------------------------------------------------
// Generate a vector of gaussian generated random values
vector<double> randGaussianVector(int length){
	// Length of the vector to be obtained
	vector<double> result(length);
	
	// We use the 64 bit Mersenne Twister: For other examples (http://www.cplusplus.com/reference/random/)
	// This generates the random number i.e. uniforms
	
	// Define the distribution
	normal_distribution<double> gaussianFunc(0.0, 1.0);
	
	// Loop to generate the vector
	for (int i =0; i< length; i++){
		result[i] = gaussianFunc(generator);
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
double mean(vector<double> inputVector){
	double sumTotal = 0.0;
	
	int n = inputVector.size();
	
	for(int i = 0; i < n; i++){
		sumTotal += inputVector[i];
	}
	
	return (sumTotal/(double) n );
}

//Vector std
double sdev(std::vector<double> inputVector){
	int n = inputVector.size();
	
	double average = mean(inputVector);
	double sumSquares = 0;
	
	for(int i = 0; i<n; i++){
		sumSquares += square(inputVector[i] - average);
	}
	return sqrt(sumSquares/(double) n);
}




//			MATRIX CONSTRUCTOR
//-------------------------------------------

//			Matrix Constructor
Matrix::Matrix(int nrow, int ncol, bool zeroBool): nrow(nrow), ncol(ncol) {

// Number of elements in the matrix
int size = nrow * ncol;

// Allocate memory for the matrix
data = new double[size];
endPointer = data + size;

if(zeroBool){
	// Fill the matrix with 0s
	memset(data, 0, sizeof(double)*size);
}

}


