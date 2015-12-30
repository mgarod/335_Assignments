/******************************************************
Title:			matrix.h
Author:			Michael Garod
Date Created:	9/10/15
Class:			Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:		Ioannis Stamos
Purpose:		Assignment #1
Description:	Header file for Matrix class, as well as functions which
				work with the Matrix class (operator<< and PrintVec() )
******************************************************/

#ifndef MATRIX_H
#define	MATRIX_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<class Comparable>
class Matrix
{
public:
	Matrix();	// Default constructor
	~Matrix();	// Destructor
	Matrix(const Matrix<Comparable>& other); // Copy Constructor
	Matrix<Comparable>& operator=(const Matrix<Comparable>& rhs); //Copy Assign
	Matrix(Matrix<Comparable>&& other); // Move Constructor
	Matrix <Comparable>& operator=(Matrix<Comparable>&& rhs); // Move Assignment
	void ReadMatrix();

	// Simple Getters for rows, cols, and cells
	const size_t NumRows() const {return num_rows_;};
	const size_t NumCols() const {return num_cols_;};
	const Comparable& GetElement(int row, int col) const
		{return array_[row][col];};

	// Operator[]
	vector<Comparable> operator[](unsigned row);

	// Operator+
	Matrix<Comparable> operator+(const Matrix<Comparable>& rhs) const;
	Matrix<Comparable> operator+(const char* rhs) const;

	// Swap
	void Swap(Matrix<Comparable>& other);

private:
	size_t num_rows_, num_cols_;
	Comparable** array_;

	// Helper Functions
	void ClearMatrix(); // Called by Destructor
};

#include "matrix.cpp"

// Functions that work with Matrices
template<class Comparable>
ostream& operator<<(ostream& os, const Matrix<Comparable>& rhs);

template<class Comparable>
void PrintVec(const vector<Comparable>& vec);

#endif
