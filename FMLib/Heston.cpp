#include "Heston.h"

using namespace std;
using namespace Eigen;

complex<double> Heston::hestonf(complex<double> u, double K, double T) const{
	// To be used frequently
	complex<double> prod =  rho * sigma * i * u;
	
    // calculate d 
    complex<double> d = sqrt(pow(prod - kappa, 2) + (sigma* sigma) * (i * u + u*u));
    
    // calculate g
    complex<double> g = (kappa - prod - d)/(kappa - prod + d);

    // Calculate first exponential
    complex<double> exp1 = exp((log(S0) + r * T) * i * u); 
    complex<double> exp2 = (1.0 - g * exp(- d * T))/(1.0 - g);
    complex<double> mainExp1 = exp1 * pow(exp2, - 2.0 * theta * kappa/(sigma * sigma));
    
    // Calculate second exponential
    complex<double> exp4 = theta * kappa * T/(sigma * sigma);
    complex<double> exp5 = v0 * (kappa  - prod - d)/(sigma * sigma) ; 
    complex<double> exp6 = (1.0 - exp(-d * T))/(1.0 - g * exp(- d * T));
    complex<double> mainExp2 = exp((exp4 * (kappa  - prod - d)) + (exp5 * exp6));
 	
 	return mainExp1 * mainExp2;
}

double Heston::putPrice(double K, double T) const{
	// Simply use put call parity
	double P = callPrice(K, T) + K * exp(- r * T) - S0;
	return P;
} 

double Heston::callPrice(double K, double T) const{
	complex<double> P(0.0, 0.0);
	double P0 = 0.5 * (S0 * exp( - q * T) - K * exp( - r * T));
	double du = (double) numMax / (double) iterations;
	
	
	for(int j = 1; j < iterations; j++){
		double u = du * (double) j;
		complex<double> u1(u, 0);	
		complex<double> u2(u, -1);
		
		P += du * (hestonf(u2, K, T) - K * hestonf(u1, K, T))/ (exp(log(K) * i * u) * u * i);
	}
	return P0 + P.real()/PI;
} 

VectorXd Heston::RNPricePathGenerator(double T,int timeStepsPerYear) const{
	VectorXd test(1);
	return test;
}
