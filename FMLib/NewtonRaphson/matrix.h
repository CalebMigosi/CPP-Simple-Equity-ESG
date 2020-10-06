#pragma once
#include "stdafx.h"

class Matrix{
public:	
	// Constructor
	Matrix(int nrow, int ncol, bool zeroBool = 1);
	
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
	
	
private:
	int nrow;
	int ncol;
	
	// Pointer to the first element in the data
	double* data;
	
	// Pointer to the last element in the data
	double* endPointer;
	
};
