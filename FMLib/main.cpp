#include <iostream>

#include "CallOption.h"
#include "Model.h"
#include "BlackScholes.h"
#include "matlib.h"

using namespace std;
int main(){
	
	// Define the matrix
	Matrix mat(2, 2);
	mat.set(1, 1, 100.0);
	cout << mat.get(1, 1) << "\n";
	
	// Declare the black scholes model
	BlackScholes model;	
	model.interestRate = 0.01;
	model.stockPrice = 100;
	model.volatility = 0.25;
	
	// Test for the model call price
	cout << model.callPrice(100.0, 1.0) <<"\n";
	cout << model.putPrice(100.0, 1.0)<<"\n";
	
	// Test the Price path generator
	vector<double> test1 = model.RNPricePathGenerator(1.0, 12.0);
	vector<double> test2 = model.RNPricePathGenerator(1.0, 12.0);
	vector<double> test3 = model.RNPricePathGenerator(1.0, 12.0);
	
}
