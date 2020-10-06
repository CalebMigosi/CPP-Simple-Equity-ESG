/* DEFINING A MATRIX CLASS
=================================
*/
#include "stdafx.h"
#include "matrix.h"

using namespace std;

//Matrix Constructor
Matrix::Matrix(int nrow, int ncol, bool zeroBool): nrow(nrow), ncol(ncol) {

// Number of elements in the matrix
int size = nrow * ncol;

// Allocate memory for the matrix
data = new double[size];
double* endPointer = data + size;

if(zeroBool){
	// Fill the matrix with 0s
	memset(data, 0, sizeof(double)*size);
}

}




