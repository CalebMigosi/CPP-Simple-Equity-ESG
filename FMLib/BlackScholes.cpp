#include "stdafx.h"
#include <iostream>
#include "BlackScholes.h"
#include "matlib.h"

using namespace std;
using namespace Eigen;

// 			CALL PRICE
//-------------------------------------
double BlackScholes::callPrice(double strike, double expiry) const{
	double logMoneyness = log(stockPrice/strike);
	double varianceTime = square(volatility * expiry);
	
	double d1 = (logMoneyness + interestRate * expiry + varianceTime)/sqrt(varianceTime);
	double d2 = d1 - sqrt(varianceTime);
	
	double price =  normCDF(d1) * stockPrice - normCDF(d2) * strike *exp( - interestRate * expiry);
	return price;
}

// 			PUT PRICE
//-------------------------------------
double BlackScholes::putPrice(double strike, double expiry) const{
		double logMoneyness = log(stockPrice/strike);
	double varianceTime = square(volatility * expiry);
	
	double d1 = (logMoneyness + interestRate * expiry + varianceTime)/sqrt(varianceTime);
	double d2 = d1 - sqrt(varianceTime);
	
	double price =  normCDF(-d2) * strike *exp( - interestRate * expiry) - normCDF(-d1) * stockPrice;
	
	return price;
}


// 		PRICE PATH GENERATOR
//-------------------------------------
VectorXd BlackScholes::RNPricePathGenerator(double expiry, int timeStepsPerYear) const{
	double totalSteps =  expiry * (double) timeStepsPerYear;
	double dt = 1.0 /(double) timeStepsPerYear;
	
	// Resulting vector
	VectorXd pricePath((int)(totalSteps+1));
	
	// To be used to scale Gaussians to make browniens
	double timeVolatility =  volatility * sqrt(dt);
	
	// Gaussians to be used multiplied by volatility
	VectorXd gaussians = randGaussianVector(totalSteps);
	
	//Initialize price path
	pricePath(0) = stockPrice;
	
	for(int i = 1; i < totalSteps+1; i++){
	
	// Use Euler discretization scheme
		double delta = exp(((interestRate - 0.5 * square(volatility)) * dt) + timeVolatility * gaussians(i-1));
		pricePath(i) = pricePath(i -1) * delta;
		}
		
	return pricePath;
}
