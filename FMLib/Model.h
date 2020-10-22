#pragma once
#include "stdafx.h"
#include "optimize.h"
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
	virtual Eigen::VectorXd RNPricePathGenerator(double expiry, int timeStepsPerYear) const = 0;
	
	// For model calibration
	//virtual Eigen::VectorXd callPriceVect(double strike, double expiry, Eigen::VectorXd params) const = 0;
	//virtual Eigen::VectorXd putPriceVect(double strike, double expiry, Eigen::VectorXd params) const = 0;
	/* virtual CalibResult calibrator(const Optimizer& algorithm) = 0;*/
	virtual ~Model(){};
};

#endif
