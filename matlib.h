#pragma once
#include "stdafx.h"

const double  PI = 3.141592653589793;

// Random Number Generators
std::vector<double> randgaussianBoxMuller(int n);
double normCDF(double x);

// Vector operations 
std::vector<double> linspace(double a, double b, int steps);
double mean(const std::vector<double>& inputVector);
double sdev(const std:: vector<double>& inputVector, bool sampleSDev = false);
double maximum(const std::vector<double>& inputVector); 
double minimum(const std::vector<double>& inputVector);

// Set Seed function
void  rng(const std::string& description);