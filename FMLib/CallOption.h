#pragma once
#include "BlackScholes.h"

class CallOption
{
public:
	double strike;
	double expiry;
	
	// Constructor
	CallOption();

	// Declare member functions
	double payoff(double stockAtMaturity) const;
	double price(const BlackScholes& bsm) const;
};

