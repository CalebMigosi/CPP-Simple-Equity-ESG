#include "PutOption.h"
#include "stdafx.h"
#include "BlackScholes.h"
#include "matlib.h"

using namespace std;

// Constructor
PutOption::PutOption(): strike(100.0), expiry(2020.0) {
}

// Define the payoff function
double PutOption::payoff(double stockAtMaturity) const {
	return max(strike - stockAtMaturity, 0.0);
}

double PutOption::price(const BlackScholes& bsm) const {
	double spot = bsm.stockPrice;
	double riskFreeRate = bsm.riskFreeRate;
	double volatility = bsm.volatility;
	double timeToMaturity = expiry - bsm.date;

	double variance = pow(volatility, 2);
	double d1Numerator = (log((spot / strike)) + (riskFreeRate + variance / 2) * timeToMaturity);

	double d1Denominator = pow(variance * timeToMaturity, 0.5);

	double d1 = d1Numerator / d1Denominator;
	double d2 = d1 - d1Denominator;
	double strikeDiscounted = strike * exp(-riskFreeRate * timeToMaturity);

	return strikeDiscounted * normCDF(-d2) - spot * normCDF(-d1);
}
