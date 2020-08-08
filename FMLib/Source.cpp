#include "matlib.h"
#include "stdafx.h"

using namespace std;

// Random Generator for uniform random variables
vector<double> randuniform(int n) {
	vector <double> uniformVector(n);

	for (int i = 0; i < n; i++) {
		// Prevents getting 0 values
		uniformVector[i] = 1.0 - (double)(rand()) / ((double)RAND_MAX + 1.0);
	}

	return uniformVector;
}

// Gaussian Random Variable Generator
vector<double> randgaussianBoxMuller(int n) {
	vector <double> uniform1 = randuniform(n);
	vector <double> uniform2 = randuniform(n);

	vector<double> gaussian(n);
	for (int i = 0; i < n; i++) {
		gaussian[i] = sqrt(-2.0 * log(uniform1[i])) * cos(2.0 * PI * uniform2[i]);
	}
	return gaussian;
}

// Generating the CDF of a Gaussian random variable
double normCDF(double x) {
	if (x >= 0) {
		double k = 1 / (1 + 0.2316419 * x);
		double firstPart = pow((2 * PI), 0.5);
		double secondPart = exp(-0.5 * pow(x, 2));
		double thirdPart = k * (0.319381530 + k * (-0.356563782 +
			k * (1.781477937 +
				k * (-1.821255978 + 1.330274429 * k))));

		return 1.0 - ((secondPart * thirdPart) / firstPart);
	}
	else {
		return 1 - normCDF(-x);
	}
}