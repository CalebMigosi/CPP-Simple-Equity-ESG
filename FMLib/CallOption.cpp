#include "stdafx.h"
#include "CallOption.h"

using namespace std;

double CallOption::price(shared_ptr<Model> model) const{
	double modelPrice = model -> callPrice(strike, expiry);
	return modelPrice;
}

