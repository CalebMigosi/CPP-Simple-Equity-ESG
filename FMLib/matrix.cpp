#include "matrix.h"

using namespace std;

//			MATRIX CONSTRUCTOR
//-------------------------------------------

//			Matrix Constructor
Matrix::Matrix(int nrow, int ncol, bool zeroBool): nrow(nrow), ncol(ncol) {

// Number of elements in the matrix
int size = nrow * ncol;

// Allocate memory for the matrix
data = new double[size];
endPointer = data + size;

if(zeroBool){
	// Fill the matrix with 0s
	memset(data, 0, sizeof(double)*size);
}}


// HELPER FUNCTION
//----------------------------
// 1) Define the assign function
//----------------------------------
void Matrix::assign(const Matrix& other){
	
	// Assign new nrow and ncol to our matrix
	nrow = other.nRow();
	ncol = other.nCol();
	
	// size of "other" matrix
	int size = nrow * ncol;
	data = new double[size];
	endPointer = data+size;
	
	// Make a copy of "other" data into the new data pointer
	memcpy(data, other.data, sizeof(double)*size);
}


//-------------------------------------------
// 				OPERATORS
//-------------------------------------------

// ADDITION
//=================
Matrix operator+(const Matrix& x,const Matrix& y){
	// Confirm that the matrices are of the same size
	assert((x.nCol() == y.nCol()) &&
			(x.nRow() == y.nRow())&& 
	"ERROR in Matrix addition: Dimensions of matrices are not compatible.");
	int rows =  x.nRow();
	int cols =  x.nCol();
	int size = rows * cols;
	
	// Result matrix
	Matrix result(rows, cols);
	
	// Assign the pointers to the first element in each vector
	double* resPointer = result.begin();
	double* resEnd = result.end();
	const double* xBegin = x.begin();
	const double* yBegin = y.begin();
	
	// Fill the result matrix
	while(resPointer != resEnd){
	 *(resPointer++) = *(xBegin++) + *(yBegin++);		
	}
	
	return result;
}


// Addition to a unit value
Matrix operator +(const Matrix& x, double val){
	int rows =  x.nRow();
	int cols =  x.nCol();
	int size = rows * cols;
	
	// Result matrix
	Matrix result(rows, cols);
	
	// Assign the pointers to the first element in each vector
	double* resPointer = result.begin();
	double* resEnd = result.end();
	const double* xBegin = x.begin();
	
	// Fill the result matrix
	while(resPointer != resEnd){
	 *(resPointer++) = *(xBegin++) + val;		
	}
	
	return result;	
}



// SUBTRACTION
//=================
Matrix operator-(const Matrix& x,const Matrix& y){
	// Confirm that the matrices are of the same size
	assert((x.nCol() == y.nCol()) &&
			(x.nRow() == y.nRow())&& 
	"ERROR in Matrix subtration: Dimensions of matrices are not compatible.");
	int rows =  x.nRow();
	int cols =  x.nCol();
	int size = rows * cols;
	
	// Result matrix
	Matrix result(rows, cols);
	
	// Assign the pointers to the first element in each vector
	double* resPointer = result.begin();
	double* resEnd = result.end();
	const double* xBegin = x.begin();
	const double* yBegin = y.begin();
	
	// Fill the result matrix
	while(resPointer != resEnd){
	 *(resPointer++) = *(xBegin++) - *(yBegin++);		
	}
	
	return result;
}



// Subtraction to a unit value
Matrix operator -(const Matrix& x, double val){
	int rows =  x.nRow();
	int cols =  x.nCol();
	int size = rows * cols;
	
	// Result matrix
	Matrix result(rows, cols);
	
	// Assign the pointers to the first element in each vector
	double* resPointer = result.begin();
	double* resEnd = result.end();
	const double* xBegin = x.begin();
	
	// Fill the result matrix
	while(resPointer != resEnd){
	 *(resPointer++) = *(xBegin++) - val;		
	}
	
	return result;	
}


// MULTIPLICATION
//=================

// Matrix multiplication
Matrix operator*(const Matrix& x,const Matrix& y){
	assert((x.nCol() == y.nRow()) && 
	"ERROR in Matrix multiplication: Dimensions of matrices are not compatible.");
	int xRow = x.nRow();
	int xCol = x.nCol();
	int yRow = y.nRow();
	int yCol = y.nCol();
	
	// Result matrix
	Matrix result(xRow, yCol);
	
	// Compute matrix multiplication
	for (int i = 0; i < xRow; i++){
		for (int j = 0; j < yCol; j++){
			for(int k = 0; k < yRow; k++)
				result(i, j) += x(i, k) * y(k, j);
		}
	}
	return result;
}


// Multiplication by a unit value
Matrix operator *(const Matrix& x, double val){
	int rows =  x.nRow();
	int cols =  x.nCol();
	int size = rows * cols;
	
	// Result matrix
	Matrix result(rows, cols);
	
	// Assign the pointers to the first element in each vector
	double* resPointer = result.begin();
	double* resEnd = result.end();
	const double* xBegin = x.begin();
	
	// Fill the result matrix
	while(resPointer != resEnd){
	 *(resPointer++) = *(xBegin++) * val;		
	}
	
	return result;	
}


// DIVISION
//=================
Matrix operator/(const Matrix& x,const Matrix& y){
	// Confirm that the matrices are of the same size
	assert((x.nCol() == y.nCol()) &&
			(x.nRow() == y.nRow()) &&
			"ERROR in Matrix division: Dimensions of matrices are not the same.");
	int rows =  x.nRow();
	int cols =  x.nCol();
	int size = rows * cols;
	
	// Result matrix
	Matrix result(rows, cols);
	
	// Assign the pointers to the first element in each vector
	double* resPointer = result.begin();
	double* resEnd = result.end();
	const double* xBegin = x.begin();
	const double* yBegin = y.begin();
	
	// Fill the result matrix
	while(resPointer != resEnd){
		
		// Make sure the divisor is not 0
		assert((*(yBegin++) == 0) && "ERROR: Division by 0");
		
		//Divide
	 	*(resPointer++) = *(xBegin++) / *(yBegin++);		
	}
	
	return result;
}


// Division by a unit value
Matrix operator /(const Matrix& x, double val){
	int rows =  x.nRow();
	int cols =  x.nCol();
	int size = rows * cols;
	
	// Result matrix
	Matrix result(rows, cols);
	
	// Assign the pointers to the first element in each vector
	double* resPointer = result.begin();
	double* resEnd = result.end();
	const double* xBegin = x.begin();
	
	// Fill the result matrix
	while(resPointer != resEnd){
	 *(resPointer++) = *(xBegin++) / val;		
	}
	
	return result;	
}



//-----------------------------------------------
// 					PRINT OPERATOR
//-----------------------------------------------
std::ostream& operator <<(std::ostream& out, const Matrix& m){
	int rows =  m.nRow();
	int cols =  m.nCol();
	out << "[";
	
	for(int i = 0; i<rows; i++){
		for(int j = 0; j < cols; j++){
			if(j == cols-1){
				if(i == rows-1){
					out << m(i, j) << "]] \n\n";	
				}else{
					out << m(i, j) << "], \n";	
				}
			}else{
				if(j ==0){
					out << "[" << m(i, j) << ", ";	
				}else{
					out << m(i, j) << ", ";	
				}
			}
		}
	}		
}
