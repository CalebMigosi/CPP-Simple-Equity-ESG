#pragma once
#include "stdafx.h"
#include "matlib.h"

//INTERFACE

/*
			NOTE
=============================

- Each model has a default stock Price and interest rate. Ideally, the model itself should contain a shared_ptr to market data.
- This way, each option only has its own information i.e. strike and expiry.
*/
#ifndef MODEL_H
#define MODEL_H
class Model{
public:
	virtual double callPrice(double strike, double expiry) const = 0;
	virtual double putPrice(double strike, double expiry) const = 0;
	virtual Matrix RNPricePathGenerator(double expiry, int timeStepsPerYear) const = 0;
	/* virtual std::vector<double> calibrator(std::vector<double> marketPrices,
											std::vector<double> strikes,
											std::vector<double> expiries) = 0;
	*/
	virtual ~Model(){};
};

#endif
