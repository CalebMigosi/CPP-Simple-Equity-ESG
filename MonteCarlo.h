#pragma once
#include "stdafx.h"
#include "BlackScholes.h"
#include "CallOption.h"
#include "PutOption.h"
#include "UpAndOutOption.h"
#include "plots.h"

class MonteCarlo
{
public:
	// Constructor
	MonteCarlo();

	// Number of scenarios
	int nScenarios;

	// PRICERS
	double pricer(const CallOption& option,
		const BlackScholes& model) const;
	double pricer(const PutOption& option,
		const BlackScholes& model) const;
	double pricer(const UpAndOutOption& option,
		const BlackScholes& model) const;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//			GREEKS (TO BE DONE)
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	double delta(const CallOption& option,
		const BlackScholes& model) const;
	double delta(const PutOption& option,
		const BlackScholes& model) const;
	double delta(const UpAndOutOption& option,
		const BlackScholes& model) const;
	
	// STATISTIC
	// Standard Error
	double standardError(const PutOption& option,
		const BlackScholes& model) const;
	double standardError(const CallOption& option,
		const BlackScholes& model) const;

	// Distribution Plots
	void distributionHist(const PutOption& putOption,
		const BlackScholes& model);
	void distributionHist(const CallOption& callOption,
		const BlackScholes& model);

private:
	std::vector<double> discountedPayoffVector(const CallOption& option,
		const BlackScholes& model) const;
	std::vector<double> discountedPayoffVector(const PutOption& option,
		const BlackScholes& model) const;
};

