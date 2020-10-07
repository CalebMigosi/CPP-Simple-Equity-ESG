#include "stdafx.h"
#include "Model.h"
#include "matlib.h"

class BlackScholes: public Model{
public:
	double callPrice(double strike, double expiry) const;
	double putPrice(double strike, double expiry) const;
	
	// To be used in Monte Carlo Pricing
	Matrix RNPricePathGenerator(double expiry,int timeStepsPerYear) const;
	
	// Market Data
	double stockPrice;
	double interestRate;
	
	// Model Parameters
	double volatility;

};
