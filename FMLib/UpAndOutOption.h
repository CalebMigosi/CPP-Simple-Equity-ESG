#pragma once
#include "BlackScholes.h"

class UpAndOutOption
{
public:
	double strike;
	double barrier;
	double expiry;

	// Constructor
	UpAndOutOption();

	// Declare member functions
	double payoff(std::vector<double>& pricePath) const;
};

