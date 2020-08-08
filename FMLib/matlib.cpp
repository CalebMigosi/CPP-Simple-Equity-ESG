#include "matlib.h"
#include "stdafx.h"

using namespace std;

// Mersenne Twister Uniform Generator
static mt19937 mersenneTwister;

// HELPER FUNCTION: Random Generator for uniform random variables
static const vector<double> randuniform(int n) {
	vector <double> uniformVector(n);

	for (int i = 0; i < n; i++) {
		// Prevents getting 0 values
		uniformVector[i] = 1.0 - (double)(mersenneTwister()) / ((double)mersenneTwister.max() + 1.0);
	}

	return uniformVector;
}

// HEADER FUNCTION: Set seed function
// HEADER FUNCTION: Set seed function
void  rng(const   string& description) {
	assert(description == "default");
	mersenneTwister.seed(mt19937::default_seed);
}


// HEADER FUNCCTION: Gaussian Random Variable Generator
vector<double> randgaussianBoxMuller(int n) {
	vector <double> uniform1 = randuniform(n);
	vector <double> uniform2 = randuniform(n);

	vector<double> gaussian(n);
	for (int i = 0; i < n; i++) {
		gaussian[i] = sqrt(-2.0 * log(uniform1[i])) * cos(2.0 * PI * uniform2[i]);
	}
	return gaussian;
}

// HEADER FUNCCTION: Generating the CDF of a Gaussian random variable
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


//====================================
//       VECTOR OPERATIONS
//====================================
// 1) Vector Mean
double mean(const vector<double>& inputVector) {
	double valueSum = 0.0;
	int n = inputVector.size();

	for (long int i = 0; i < n; i++) {
		valueSum += inputVector[i];
	}

	double meanValue = valueSum / double(n);
	return meanValue;
}

// 2) Vector Standard Deviation
double sdev(const vector<double>& inputVector, bool sampleSDev) {
	double vectorMean = mean(inputVector);
	double sumSquareDeviations = 0.0;
	int n = inputVector.size();

	// Calculate the square deviations
	for (int i = 0; i < n; i++) {
		sumSquareDeviations += pow(inputVector[i] - vectorMean, 2);
	}
	double variance;

	if (sampleSDev) {
		variance = sumSquareDeviations / max(double(n) - 1.0, 1.0);
	}
	else {
		variance = sumSquareDeviations / (double)n;
	}

	return sqrt(variance);
}

// 3) Linspace: Returns evenly distributed double values
vector<double> linspace(double from, double to, int steps) {
	double delta = (to - from) / (double) (steps - 1);

	vector <double> outputVector(steps, 0); 
	for (int i = 0; i < steps; i++) {
		outputVector[i] = from + delta * (double)i;
	}

	return outputVector;
}

// 4) Vector Maximum
double maximum(const vector<double>& inputVector) {
	double vectorMax = inputVector.back();

	for (int i = 0; i < (int)inputVector.size(); i++) {
		vectorMax = max(inputVector[i], vectorMax);
	}

	return vectorMax;
}

// 5) Vector Minimum
double minimum(const vector<double>& inputVector) {
	double vectorMax = inputVector.back();

	for (int i = 0; i < (int)inputVector.size(); i++) {
		vectorMax = min(inputVector[i], vectorMax);
	}

	return vectorMax;
}