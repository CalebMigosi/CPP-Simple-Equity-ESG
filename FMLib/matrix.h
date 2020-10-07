#pragma once
#include "stdafx.h"

// 		DEFINE A MATRIX CLASS
//------------------------------------- 
class Matrix{
public:	
	// Constructor
	Matrix(int nrow, int ncol = 1, bool zeroBool = 1);
	
	// Get the number of colums and rows
	int nRow() const{return nrow;}
	int nCol() const{return ncol;}
	
	// HELPER FUNCTIONS (All inlined because of heavy use)
	// -------------------------------------------------------
	// 1) Offset function
	int offset(int i, int j) const{
		assert( i >= 0 && j >=0 && i < nrow && j < ncol );

		// Data is stored rowwise
		return j*nrow+i;
	}
	
	// 2) get and set functions
	// Get
	double get(int i, int j ) const {
			return data[ offset(i, j) ] ;
	}
	
	// Set
	void set(int i, int j , double value){
		data[offset(i, j)] = value;
	} 
	
	// 3) begin functions to obtain a pointer to the first element
	double* begin(){
		return data;
	}
	
	const double* begin() const{
		return data;
	}
	
	// 4) end functions to obtain a pointer to the last element
	double* end(){
		return endPointer;
	}

	const double* end() const{
		return endPointer;
	}
	
	// 5) Indexing
	double& operator ()(int i, int j = 0){
		return data[offset(i, j)];
	};

	const double& operator ()(int i, int j=0) const{
		return data[offset(i, j)];
	};
	
	
	// MEMORY MANAGEMENT
	//--------------------------
	
	//--------------------
	// 1) DESTRUCTOR
	//------------------
	~Matrix(){delete[] data;}
	
	
	// 2) Override the assign operator
	//----------------------------------
	// Assign function copies data from the "other" matrix to the declared matrix 
	void assign(const Matrix& other);
	
	Matrix& operator = (const Matrix& other){
		// Delete current data
		delete[] data;
	
		// Assign the other matrix to the variable on the left
		assign(other);
	
		// Return the newly created data pointer containing "other" data
		return *this;}
	
	// 4) Copy constructor
	//----------------------------------
	Matrix(const Matrix& other){
		assign(other);
	}
		
private:
	int nrow;
	int ncol;
	
	// Pointer to the first element in the data
	double* data;
	
	// Pointer to the last element in the data
	double* endPointer;
	
};

//--------------------------------------------------------
// OVERLOADED MATHEMATICAL OPERATORS
//--------------------------------------------------------
Matrix operator +(const Matrix& x, const Matrix& y);
Matrix operator -(const Matrix& x, const Matrix& y);
Matrix operator *(const Matrix& x, const Matrix& y);
Matrix operator /(const Matrix& x, const Matrix& y);

// Operations with single values
Matrix operator +(const Matrix& x, double val);
Matrix operator -(const Matrix& x, double val);
Matrix operator *(const Matrix& x, double val);
Matrix operator /(const Matrix& x, double val);


//--------------------------------------------------------
// OVERLOAD GENERAL OPERATORS
//--------------------------------------------------------
std::ostream& operator <<(std::ostream& out, 
							const Matrix& m);

//--------------------------------------------------------
//			MEMORY MANAGEMENT
//--------------------------------------------------------


