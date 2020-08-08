#pragma once
#include "stdafx.h"

class BlackScholes {
public:
	double stockPrice;
	double volatility;
	double date;
	double riskFreeRate;

	std::vector<double> riskNeutralPathGenerator(double toDate, int timeStepsPerYear, double spotPrice = 1) const;

private:
	std::vector<double> pricePathGenerator(double toDate,
											int timeStepsPerYear,
											double drift = 0,
											double spotPrice = 1) const;
};

