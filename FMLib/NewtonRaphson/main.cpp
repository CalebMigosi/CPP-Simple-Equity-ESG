#include <iostream>
#include "stdafx.h"
#include "matrix.h"

// Use template to manage inputs and outputs
//------------------------------------------------
template<typename Input, typename Output>
class RealFunction{
public:
	std::function<Input(Output)> f;
	
	// Constructor
	RealFunction(std::function<Input(Output)> fInput): f(fInput) {};
	
	// Override the () operator
	Output operator() (Input x) {return f(x) ;}
	
	// Find the derivative of the function
	Output firstDerivative(Input x, Input h){
		return (f(x+h) - f(x))/h;
	}
	
	// Find the second derivative of the function
	Output secondDerivative(Input x, Input h){
		return (firstDerivative(x, h) - firstDerivative(x-h, h))/h;
	}	
};

// Test Function declarations
double vectorSum(std::vector<double>& testVect);
void testRealFunctionClass();
double power2(double x);


//==============================
//			MAIN
//==============================
using namespace std;
int main(){

Matrix mat(1, 1); 
// mat.set(0,0, 1.0);

// cout << mat.get(0,0) << "\n";

testRealFunctionClass();
}


// 				TESTS
//=================================

//Test for a vector function
double vectorSum(std::vector<double>& testVect){
	double total = 0.0;
	for (int i = 0; i <testVect.size(); i++){
		total += testVect[i];
	}
	
	return total;
}

// Test power function
double power2(double x){
	return x *x*x;
}

void testRealFunctionClass(){
// Test the Real Function object
// Change the function to a proper function object
function<double(double)> ppower2 = power2;

// Declare the function
RealFunction<double, double> test(ppower2);

//Evaluate the functions
cout << test(2.0) << "\n";
cout << test.firstDerivative(3.0, 1e-10)<< "\n";
cout << test.secondDerivative(3.5, 1e-4)<< "\n"; 
}
