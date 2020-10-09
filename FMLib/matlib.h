#pragma once
#include "stdafx.h"
#include "matrix.h"

//INLINES
// Square function
inline double square(double x) {return x * x;}

// GAUSSIAN RANDOM VARIABLES
Matrix randGaussianVector(int length);

double normCDF(double x);

// STATISTICS
double mean(const Matrix& inputVector);

double sdev(const Matrix& inputVector);

