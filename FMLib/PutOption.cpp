#include "stdafx.h"
#include "PutOption.h"

using namespace std;

double PutOption::price(shared_ptr<Model> model){
	double modelPrice = model -> putPrice(strike, expiry);
	return modelPrice;
}

