#pragma once
#include "stdafx.h"
#include "Model.h"
#include "matlib.h"

class Heston: public Model{
public:
	// Constructor (Default values selected in case pricing is needed)
	Heston(double sigma = 0.575, double kappa = 1.5768, double theta = 0.0398, double v0 = 0.1, double rho = -0.5711) : 
		sigma(sigma), kappa(kappa), theta(theta), v0(v0), rho(rho), 
		i(std::complex<double>(0, 1)), numMax(100), iterations(1000){};
	
	// Plain vanilla pricers
	double callPrice(double K, double T) const;
	double putPrice(double K, double T) const;
	
	// To be used in Monte Carlo Pricing
	Eigen::VectorXd RNPricePathGenerator(double expiry,int timeStepsPerYear) const;
	
	// Market Data
	double S0;
	double r;
	double q;

private:
	std::complex<double> hestonf(std::complex<double> u, double K, double T) const; // characteristic function of terminal stock price
		
	// Model Parameters
	double sigma; // volatility of the variance (volvol) 
	double kappa; // Mean reversion speed for the variance
	double theta; // Long term mean
	double v0;	  // Initial level of volatility
	double rho;   // Correlation between the brownian motions
	std::complex<double> i; // should represent the complex number: sqrt(-1)
	
	int numMax;			// Maximum number to be reached by complex integral
	int iterations;		// Total number of iterations to be used
};
