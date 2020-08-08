#include "BlackScholes.h"
#include "stdafx.h"
#include "matlib.h"
using namespace std;

vector<double> BlackScholes::pricePathGenerator(double toDate, int timeStepsPerYear, double drift, double spotPrice) const {
	int n = (int)(toDate - date) * timeStepsPerYear;
	double dt = 1 / (double) timeStepsPerYear; //Dt in discretization scheme

	// Generate vector of Gaussians
	vector<double> gaussians = randgaussianBoxMuller(n);

	// Container for price path
	vector<double> pricePath(n);
	pricePath[0] = spotPrice;
	double driftImpact = (drift - 0.5 * volatility * volatility) * dt;

	// Loop through the 
	for (int i = 1; i < n; i++) {
		pricePath[i] = pricePath[i-1] * exp(driftImpact + volatility * sqrt(dt) * gaussians[i - 1]);
	}

	return pricePath;
}

vector<double> BlackScholes::riskNeutralPathGenerator(double toDate, int timeStepsPerYear, double spotPrice) const{
	return pricePathGenerator(toDate, timeStepsPerYear, riskFreeRate, spotPrice);
}