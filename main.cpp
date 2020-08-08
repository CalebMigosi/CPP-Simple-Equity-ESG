#include <iostream>
#include "CallOption.h"
#include "PutOption.h"
#include "BlackScholes.h"
#include "matlib.h"
#include "MonteCarlo.h"
#include "plots.h"

using namespace std;
int main() {
	BlackScholes test;
	test.date = 2014.0;
	test.riskFreeRate = 0.005;
	test.stockPrice = 100.0;
	test.volatility = 0.1;

	// Call Option
	CallOption aapl;
	aapl.expiry = 2015.0;
	aapl.strike = 99.0;

	// Put Option
	PutOption aaplPut;
	aaplPut.expiry = 2015.0;
	aaplPut.strike = 99.0;

	// Up and Out Option
	UpAndOutOption aaplUAO;
	aaplUAO.expiry = 2015.0;
	aaplUAO.strike = 99.0;
	aaplUAO.barrier = 120.0;

	// Model Price
	cout << "Model Call Price: " <<aapl.price(test) << "\n";
	cout << "Model Put Price: " << aaplPut.price(test) << "\n";

	// Plots
	vector<double> result = test.riskNeutralPathGenerator(2020.0, 10);
	vector<double> indices = linspace(2014.0, 2020.0, 60);

	// Plot Stock Chart
	lineChartHTML("Outputs/StockChart", indices, result);
	histogramHTML("Outputs/StockHist", result);

	// Monte Carlo Pricing
	MonteCarlo mcTest;
	mcTest.nScenarios = 1000;
	
	cout << "Monte Carlo Call Price: " << mcTest.pricer(aapl, test) << "\n";
	cout << "Monte Carlo Put Price: " << mcTest.pricer(aaplPut, test) << "\n";
	cout << "Monte Carlo Up and Out Price: " << mcTest.pricer(aaplUAO, test) << "\n";
	mcTest.distributionHist(aaplPut, test);
	mcTest.distributionHist(aapl, test);

	// GREEKS
	cout << "Monte Carlo Call Delta: " << mcTest.delta(aapl, test) << "\n";
	
	// STATISTICS
	cout << "Monte Carlo Call Standard Error: " << mcTest.standardError(aapl, test) << "\n";
	cout << "Monte Carlo Call Confidence Interval: [" << mcTest.pricer(aapl, test) - 1.96 * mcTest.standardError(aapl, test) 
		<< ", " << mcTest.pricer(aapl, test) + 1.96 * mcTest.standardError(aapl, test) << "]\n";

}