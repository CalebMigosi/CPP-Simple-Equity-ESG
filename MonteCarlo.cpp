#include "MonteCarlo.h"
#include "stdafx.h"
#include "matlib.h"

using namespace std;

MonteCarlo::MonteCarlo(): nScenarios(10000) {}

//==========================================
//			PRICERS
//==========================================
// Monte Carlo Call Pricer
double MonteCarlo::pricer(const CallOption& callOption,
							const BlackScholes& model) const{
	double spot = model.stockPrice;
	double riskFreeRate = model.riskFreeRate;
	double volatility = model.volatility;
	double expiry = callOption.expiry;
	double strike = callOption.strike;
	double timeToMaturity = expiry - model.date;

double scenarioSum = 0;

for (int i = 0; i < nScenarios; i++) {
	vector<double> path = model.riskNeutralPathGenerator(expiry, 252, spot);
	double stockPriceatMaturity = path.back();
	scenarioSum += callOption.payoff(stockPriceatMaturity);
}

return scenarioSum * exp(-riskFreeRate * timeToMaturity) / (double)nScenarios;

}

// Monte Carlo Put Pricer
double MonteCarlo::pricer(const PutOption& putOption,
	const BlackScholes& model) const {
	double spot = model.stockPrice;
	double riskFreeRate = model.riskFreeRate;
	double volatility = model.volatility;
	double expiry = putOption.expiry;
	double strike = putOption.strike;
	double timeToMaturity = expiry - model.date;

	double scenarioSum = 0;

	for (int i = 0; i < nScenarios; i++) {
		vector<double> path = model.riskNeutralPathGenerator(expiry, 252, spot);
		double stockPriceatMaturity = path.back();
		scenarioSum += putOption.payoff(stockPriceatMaturity);
	}

	return scenarioSum * exp(-riskFreeRate * timeToMaturity) / (double)nScenarios;

}

// Monte Carlo Up and Out Pricer
double MonteCarlo::pricer(const UpAndOutOption& option,
	const BlackScholes& model) const {
	double spot = model.stockPrice;
	double riskFreeRate = model.riskFreeRate;
	double expiry = option.expiry;
	double strike = option.strike;
	double timeToMaturity = expiry - model.date;

	double scenarioSum = 0.0;


	for (int i = 0; i < nScenarios; i++) {
		rng("default");
		vector<double> path = model.riskNeutralPathGenerator(expiry, 252, spot);
		scenarioSum += option.payoff(path);
	}

	return scenarioSum * exp(-riskFreeRate * timeToMaturity) / (double)nScenarios;

}

//==========================================
//			GREEKS
//==========================================
double MonteCarlo::delta(const CallOption& option,
	const BlackScholes& model) const {
	double spot = model.stockPrice;
	double expiry = option.expiry;
	double riskFreeRate = model.riskFreeRate;
	double timeToMaturity = option.expiry - model.date;

	// Define h
	double h = spot * 1e-7;

	// f(x +h) and f(x -h)
	double spotPriceHigh = spot + h;
	double spotPriceLow = spot - h;

	double priceUp = 0;
	double priceDown = 0;

	// Run simulation
	for (int i = 0; i < nScenarios; i++) {
		vector<double> pathUp = model.riskNeutralPathGenerator(expiry, 252, spotPriceHigh);
		vector<double> pathDown = model.riskNeutralPathGenerator(expiry, 252, spotPriceLow);

		double stockPriceatMaturityUp = pathUp.back();
		double stockPriceatMaturityDown = pathDown.back();

		priceUp += option.payoff(stockPriceatMaturityUp);
		priceDown += option.payoff(stockPriceatMaturityDown);
	}

	return (priceUp - priceDown) * exp(-riskFreeRate * timeToMaturity) / (2 * h * (double)nScenarios);
}


//========================================
//			STATISTICS
//========================================
// STANDARD ERROR
double MonteCarlo::standardError(const PutOption& option,
	const BlackScholes& model) const {
	vector<double> payoffVect = model.riskNeutralPathGenerator(option.expiry, 252, model.stockPrice);
	double N = (double)payoffVect.size();
	return sdev(payoffVect) * pow(N, -1.2);
}

double MonteCarlo::standardError(const CallOption& option,
	const BlackScholes& model) const {
	vector<double> payoffVect = model.riskNeutralPathGenerator(option.expiry, 252, model.stockPrice);
	double N = (double)payoffVect.size();
	return sdev(payoffVect) * pow(N, -1.2);
}

//HELPER:: Generates the vector of payoffs at maturity
vector<double> MonteCarlo::discountedPayoffVector(const CallOption& option,
								const BlackScholes& model) const{
	double spot = model.stockPrice;
	double riskFreeRate = model.riskFreeRate;
	double volatility = model.volatility;
	double expiry = option.expiry;
	double strike = option.strike;
	double timeToMaturity = expiry - model.date;

	vector<double> payOffSet(nScenarios);

	for (int i = 0; i < nScenarios; i++) {
		vector<double> path = model.riskNeutralPathGenerator(expiry, 252, spot);
		double stockPriceatMaturity = path.back();
		payOffSet[i] = option.payoff(stockPriceatMaturity) * exp(-riskFreeRate * timeToMaturity);
	}
	return payOffSet;
}

//HELPER:: Generates the vector of payoffs at maturity (Puts)
vector<double> MonteCarlo::discountedPayoffVector(const PutOption& option,
	const BlackScholes& model) const {
	double spot = model.stockPrice;
	double riskFreeRate = model.riskFreeRate;
	double volatility = model.volatility;
	double expiry = option.expiry;
	double strike = option.strike;
	double timeToMaturity = expiry - model.date;

	vector<double> payOffSet(nScenarios);

	for (int i = 0; i < nScenarios; i++) {
		vector<double> path = model.riskNeutralPathGenerator(expiry, 252, spot);
		double stockPriceatMaturity = path.back();
		payOffSet[i] = option.payoff(stockPriceatMaturity) * exp( - riskFreeRate * timeToMaturity) ;
	}
	return payOffSet;
}


//========================================
//		 DISTRIBUTION PLOTS
//========================================

// Put Option Distribution Graphs
void MonteCarlo::distributionHist(const PutOption& putOption, const BlackScholes& model){
	vector<double> payOffVect(nScenarios);
	payOffVect = discountedPayoffVector(putOption, model);

	//Plot Histogram
	histogramHTML("Outputs/Put MC Distribution", payOffVect);
}

// Call Option Distribution Graphs
void MonteCarlo::distributionHist(const CallOption& callOption, const BlackScholes& model) {
	vector<double> payOffVect(nScenarios);
	payOffVect = discountedPayoffVector(callOption, model);

	//Plot Histogram
	histogramHTML("Outputs/Call MC Distribution", payOffVect);
}