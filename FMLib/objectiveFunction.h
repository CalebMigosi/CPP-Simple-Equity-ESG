#pragma once
#include "stdafx.h"
#include "matlib.h"

// Not typical for a header file but just easier to use
using namespace Eigen;

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


// 				DEFINE VectorXd FUNCTION
//------------------------------------------------
// Inlined all functions for performance
// These will be used in the minimization algorithm
class RealVectFunction{
public:
	std::function<double(const VectorXd&)> f;
	
	// Constructor
	RealVectFunction(std::function<double(const VectorXd&)> fInput): f(fInput){}
	
	// Override the () operator to evaluate the function
	double operator()(const VectorXd& x) const{ return f(x);}
	
	// Helper function to calculate the derivative
	double derivative(const VectorXd& x, int i, double h) const{
		VectorXd xCopy = x;
		
		// Change the ith value of x
		xCopy(i) =  x(i)+h;
		
		double deriv =  (f(xCopy) - f(x))/h;
		
		return deriv;
	}
		
	// 				GRADIENT
	//--------------------------------------
	VectorXd gradient(const VectorXd& x, double h = 1e-11) const{
	
		// Note that x is the input vector
		int rows = x.rows();
		
		// Output
		VectorXd result(rows);
		
		for (int i = 0; i < rows; i++){
			// Return the derivative
			result(i) = derivative(x, i, h);	
		}
		
		return result;
	}
	
	
	// Helper function to calculate the second derivative
	double secondDerivative(const VectorXd& x, int i, int j, double h) const{
		// Copy of x
		VectorXd xCopy = x;
		
		// Find the first derivative
		VectorXd gradientVectorXd = gradient(x);
		
		// Find the derivative with x_j shifted by h	
		xCopy(j)= x(j)+h;
		VectorXd deltaGradient = gradient(xCopy);
		
		// Calculate the derivative of the gradient at i wrt j
		double deriv = (deltaGradient(i) - gradientVectorXd(i))/h;
		
		return deriv;	
	}


	// 					HESSIAN
	//-------------------------------------------------
	MatrixXd hessian(const VectorXd& x, double h = 1e-2) const{
		int rows = x.rows();
		
		// Output
		MatrixXd result(rows, rows);
		
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < rows; j++){
				result(i, j) = secondDerivative(x, i, j, h);
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
	std::function<VectorXd(const VectorXd&)> f;
	
	// Constructor
	ObjectiveFunction(std::function<VectorXd(const VectorXd&)> fInput): f(fInput){}
	
	// Override the () operator to evaluate the function
	VectorXd operator()(const VectorXd& x) const{ return f(x);}
	
	// Calculate the derivative of the function f
	VectorXd derivative (const VectorXd& x, int i, double h = 1e-11) const{
		// Copy VectorXd x
		VectorXd xCopy = x;
		
		// Change the value of the copy
		xCopy(i) =  x(i) + h;
		
		// Calculate the derivative
		VectorXd deriv = (f(xCopy) - f(x))/h;
		
		return deriv;
	}
		
	MatrixXd jacobian(const VectorXd& x) const{
		// Find the number of columns in the jacobian
		// This is the number of derivatives we will have to calculate
		int cols = x.rows();
		
		// Find the length of the outputs
		int rows = f(x).rows();
		
		// Jacobian VectorXd
		MatrixXd result(rows, cols);
		
		for (int i = 0; i < rows; i++){
			VectorXd gradientVect =  derivative(x, i);
			
			for(int j = 0; j < cols; j++){
				result(i, j) =  gradientVect(j);	
			}
		}
		
		return result;
	}

private:
	VectorXd input;
};


