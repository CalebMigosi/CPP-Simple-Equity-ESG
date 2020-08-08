#include "UpAndOutOption.h"
#include "stdafx.h"
#include "BlackScholes.h"
#include "matlib.h"

using namespace std;

UpAndOutOption::UpAndOutOption():strike(100.0), expiry(2020.0), barrier(120.0){}

double UpAndOutOption::payoff(vector<double>& pricePath) const{
	bool barrierBreached = false;

	int n = pricePath.size();
	int i = 0;
	
	while (i < n) {
		if (pricePath[i] > barrier){
			barrierBreached = true;
			break;
		} 
		i++;
	}

	if (barrierBreached) {
		return 0;
	}

	else {
		return max(pricePath.back() - strike, 0.0);
	}
}

