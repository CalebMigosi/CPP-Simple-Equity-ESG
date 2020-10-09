#pragma once
#include "stdafx.h"
#include "Model.h"
#include "Security.h"

//INTERFACE

class CallOption: public Security{
public:
	double price(std::shared_ptr<Model> model) const;
	
	//Access to data: Inline functions
	double getExpiry() const{ return expiry;}	
	double getStrike() const{ return strike;}
	
	void setExpiry(double inputExpiry){expiry = inputExpiry;}
	void setStrike(double inputStrike){strike = inputStrike;}
	
	double strike;
	double expiry;
};
