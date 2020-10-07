#pragma once
#include "stdafx.h"
#include "matrix.h"

//INLINES
// Square function
inline double square(double x) {return x * x;}

// GAUSSIAN RANDOM VARIABLES
Matrix randGaussianVector(int length);

double normCDF(double x);

// STATISTICS
double mean(const Matrix& inputVector);

double sdev(const Matrix& inputVector);


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

