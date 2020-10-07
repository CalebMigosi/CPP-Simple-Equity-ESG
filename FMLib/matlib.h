#pragma once
#include "stdafx.h"

//INLINES
// Square function
inline double square(double x) {return x * x;}


// GAUSSIAN RANDOM VARIABLES
std::vector<double> randGaussianVector(int length);

double normCDF(double x);

// STATISTICS
double mean(std::vector<double> inputVector);

double sdev(std::vector<double> inputVector);

//double stdError(std::vector<double> inputVector);


// 		DEFINE A MATRIX
//------------------------------ 
class Matrix{
public:	
	// Constructor
	Matrix(int nrow, int ncol, bool zeroBool = 1);
	
	// Get the number of colums and rows
	int nRow() const{return nrow;}
	int nCol() const{return ncol;}
	
	// HELPER FUNCTIONS (All inlined because of heavy use)
	// -------------------------------------------------------
	// 1) Offset function
	int offset(int i, int j) const{
		assert( i >= 0 && j >=0 && i < nrow && j < ncol );

		// Data is stored rowwise
		return j*nrow+i;
	}
	
	// 2) get and set functions
	// Get
	double get(int i, int j ) const {
			return data[ offset(i, j) ] ;
	}
	
	// Set
	void set(int i, int j , double value){
		data[offset(i, j)] = value;
	} 
	
	
private:
	int nrow;
	int ncol;
	
	// Pointer to the first element in the data
	double* data;
	
	// Pointer to the last element in the data
	double* endPointer;
	
};


// 				DEFINE REAL FUNCTION
//------------------------------------------------

// Use template to manage inputs and outputs
//------------------------------------------------
template<typename Input, typename Output>
class RealFunction{
public:
	std::function<Input(Output)> f;
	
	// Constructor
	RealFunction(std::function<Input(Output)> fInput): f(fInput) {};
	
	// Override the () operator
	Output operator() (Input x) {return f(x);}
	
	// Find the derivative of the function
	Output firstDerivative(Input x, Input h){
		return (f(x+h) - f(x))/h;
	}
	
	// Find the second derivative of the function
	Output secondDerivative(Input x, Input h){
		return (firstDerivative(x, h) - firstDerivative(x-h, h))/h;
	}	
};

