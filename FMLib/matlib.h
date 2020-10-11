#pragma once
#include "stdafx.h"

//INLINES
// Square function
inline double square(double x) {return x * x;}

// GAUSSIAN RANDOM VARIABLES
Eigen::VectorXd randGaussianVector(int length);

double normCDF(double x);

// STATISTICS
double mean(const Eigen::VectorXd& inputVector);

double sdev(const Eigen::VectorXd& inputVector);


// VectorXd operations
Eigen::VectorXd transpose(const Eigen::VectorXd& VectorXd);
