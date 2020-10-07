#include "stdafx.h"
#include "Model.h"
#include "Security.h"

//INTERFACE

class PutOption : public Security{
public:
	double price(std::shared_ptr<Model> model);
	
	//Access to data: Inline functions
	double getExpiry() const{ return expiry;}	
	double getStrike() const{ return strike;}
	
	void setExpiry(double inputExpiry){expiry = inputExpiry;}
	void setStrike(double inputStrike){strike = inputStrike;}
	
	double strike;
	double expiry;
};
