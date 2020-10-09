#pragma once
#include "stdafx.h"
#include "matlib.h"
#include "matrix.h"

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


// 				DEFINE MATRIX FUNCTION
//------------------------------------------------
// Inlined all functions for performance
// These will be used in the minimization algorithm
class RealVectFunction{
public:
	std::function<double(const Matrix&)> f;
	
	// Constructor
	RealVectFunction(std::function<double(const Matrix&)> fInput): f(fInput){}
	
	// Override the () operator to evaluate the function
	double operator()(const Matrix& x){ return f(x);}
	
	
	
	// Helper function to calculate the derivative
	double derivative(const Matrix& x, int i, double h){
		Matrix xCopy = x;
		
		// Change the ith value of x
		xCopy.set(i, 0, x(i)+h);
		
		double deriv =  (f(xCopy) - f(x))/h;
		
		return deriv;
	}
		
	// 				GRADIENT
	//--------------------------------------
	Matrix gradient(const Matrix& x, double h = 1e-10){
	
		// Note that x is the input vector
		int rows = x.nRow();
		
		// Output
		Matrix result(rows);
		
		for (int i = 0; i < rows; i++){
			// Return the derivative
			result.set(i, 0, derivative(x, i, h));	
		}
		
		return result;
	}
	
	
	// Helper function to calculate the second derivative
	double secondDerivative(const Matrix& x, int i, int j, double h){
		// Copy of x
		Matrix xCopy = x;
		
		// Find the first derivative
		Matrix gradientMatrix = gradient(x);
		
		// Find the derivative with x_j shifted by h	
		xCopy.set(j, 0, x(j)+h);
		Matrix deltaGradient = gradient(xCopy);
		
		// Calculate the derivative of the gradient at i wrt j
		double deriv = (deltaGradient(i) - gradientMatrix(i))/h;
		
		return deriv;	
	}


	// 					HESSIAN
	//-------------------------------------------------
	Matrix hessian(const Matrix& x, double h = 1e-2){
		int nrow = x.nRow();
		
		// Output
		Matrix result(nrow, nrow);
		
		for(int i = 0; i < nrow; i++){
			for(int j = 0; j < nrow; j++){
				result.set(i, j, secondDerivative(x, i, j, h));
			}
		}
		
		return result;
	}	

};


// 				DEFINE SYSTEM OF EQUATIONS
//----------------------------------------------------
// Inlined all functions for performance
// These will be used in the minimization algorithm
class ObjectiveFunction{
public:
	// Empty function
	std::function<Matrix(const Matrix&)> f;
	
	// Constructor
	ObjectiveFunction(std::function<Matrix(const Matrix&)> fInput): f(fInput){}
	
	// Override the () operator to evaluate the function
	Matrix operator()(const Matrix& x){ return f(x);}
	
	// Calculate the derivative of the function f
	Matrix derivative (const Matrix& x, int i, double h = 1e-10){
		// Copy matrix x
		Matrix xCopy = x;
		
		// Change the value of the copy
		xCopy.set(i, 0, x(i)+h);
		
		// Calculate the derivative
		Matrix deriv = (f(xCopy) - f(x))/h;
		
		return deriv;
	}
		
	Matrix jacobian(const Matrix& x){
		// Find the number of columns in the jacobian
		// This is the number of derivatives we will have to calculate
		int ncol = x.nRow();
		
		// Find the length of the outputs
		int nrow = f(x).nRow();
		
		// Jacobian matrix
		Matrix result(nrow, ncol);
		
		for (int i = 0; i < nrow; i++){
			Matrix gradientVect =  derivative(x, i);
			
			for(int j = 0; j < ncol; j++){
				result.set(i, j, gradientVect(j));	
			}
		}
		
		return result;
	}

private:

};


