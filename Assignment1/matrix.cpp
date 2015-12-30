/******************************************************
Title:			matrix.cpp
Author:			Michael Garod
Date Created:	9/10/15
Class:			Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:		Ioannis Stamos
Purpose:		Assignment #1
Description:	Implementation file for the Matrix Class
******************************************************/

#ifndef MATRIX_CPP
#define MATRIX_CPP
#include "matrix.h"

/********************Methods of Matrix**********************/

// Default Constructor
template<class Comparable>
Matrix<Comparable>::Matrix()
{
	num_rows_ = 0;
	num_cols_ = 0;
	array_ = nullptr;
}

// Destructor
template<class Comparable>
Matrix<Comparable>::~Matrix()
{
	if (array_ != nullptr)
	{
		ClearMatrix();
	}
}

// Copy Constructor (calls the Copy Assignment operator=)
// Parameters: Accepts any Matrix
// Pre: n/a
// Post: This new matrix is a deep copy of other
template<class Comparable>
Matrix<Comparable>::Matrix(const Matrix<Comparable>& other)
{	
	// Initialize the new *this
	num_rows_ = 0;
	num_cols_ = 0;
	array_ = nullptr;

	// Deep copy of other
	*this = other;
}

// Copy Assignment
// Parameters: Accepts any Matrix
// Pre: n/a
// Post: *this becomes a deep copy of rhs
template<class Comparable>
Matrix<Comparable>& Matrix<Comparable>::operator=
	(const Matrix<Comparable>& rhs)
{	
	if (num_rows_ > 0)
	{
		ClearMatrix();
	}

	// Get dimensions
	num_rows_ = rhs.num_rows_;
	num_cols_ = rhs.num_cols_;

	// (Re)Initialize Array
	array_ = new Comparable*[num_rows_];
	for (unsigned int i=0; i < num_rows_; i++)
	{
		array_[i] = new Comparable[num_cols_];
	}

	// Fill Array
	for (unsigned int i=0; i < num_rows_; i++)
	{
		for (unsigned int j=0; j < num_cols_; j++)
		{
			array_[i][j] = rhs.array_[i][j];
		}
	}

	return *this;
}

// Move Constructor
// Parameters: An rvalue Matrix
// Pre: other is no longer needed
// Post: This new matrix takes other's data, and other is emptied
template<class Comparable>
Matrix<Comparable>::Matrix(Matrix<Comparable>&& other)
{
	// Initialize the new *this
	num_rows_ = 0;
	num_cols_ = 0;
	array_ = nullptr;

	// Shallow copy of other
	*this = std::move(other);
}

// Move Assignment
// Parameters: An rvalue Matrix
// Pre: rhs is no longer needed
// Post: This new matrix takes rhs's data, and rhs is emptied
template<class Comparable>
Matrix<Comparable>& Matrix<Comparable>::operator=(Matrix<Comparable>&& rhs)
{
	if (num_rows_ > 0)
	{	// Deallocate existing memmory, if any
		ClearMatrix();
	}
	
	// Shallow copy of rhs
	num_rows_ = rhs.num_rows_;
	num_cols_ = rhs.num_cols_;
	array_ = rhs.array_;

	// Disconnect rhs's ownership to the data
	rhs.num_rows_ = 0;
	rhs.num_cols_ = 0;
	rhs.array_ = nullptr;
	
	return *this;
}

// Matrix.ReadMatrix()
// Description: Resets a Matrix and asks the user for size and contents
// Precondition: The user will only only input valid entries. Inputing improper
//	values will cause the program to crash.
// Post: The Matrix is filled.
template<class Comparable>
void Matrix<Comparable>::ReadMatrix()
{
	ClearMatrix();

	// Get dimensions
	size_t rows, cols;
	do
	{
		cout << "Enter rows (integer > 0): ";
		cin >> rows;
	} while (rows < 1);

	do
	{
		cout << "Enter columns (integer > 0): ";
		cin >> cols;
		cout << endl;
	} while (cols < 1);

	num_rows_ = rows;
	num_cols_ = cols;

	// Initialize Array
	array_ = new Comparable*[num_rows_];
	for (unsigned int i=0; i < rows; i++)
	{
		array_[i] = new Comparable[num_cols_];
	}

	// Fill Array - Has no input validation
	Comparable value;
	for (unsigned int i=0; i < num_rows_; i++)
	{
		for (unsigned int j=0; j < num_cols_; j++)
		{
			printf("Insert value for cell (%d,%d): ", i, j);
			cin >> value;
			array_[i][j] = value;
		}
	}
}

// Matrix.ClearMatrix() called by the destructor
// Description: Sets the Matrix to size 0x0 and point the array_ to nullptr;
// Precondition: Matrix must be non-empty. This is checked by the functions
//	that call ClearMatrix()
// Post:
template<class Comparable>
void Matrix<Comparable>::ClearMatrix()
{
	for (unsigned int i = 0; i < num_rows_; i++)
	{
		delete[] array_[i];
		// This destroys: new Comparable[num_cols_]
	}

	delete[] array_;
	array_ = nullptr;
	num_rows_ = 0;
	num_cols_ = 0;	
	// This destroys: new Comparable*[num_rows_]

	return;
}


// Operator[] for use of PrintVec(). Doesn't work with lhs assignment because
//	this returns a copy of the row vector, not the row itself.
// Precondition: Parameter must be in range 0 < unsigned row < num_rows_
// Postcondition: The returned vector is a copy, not a reference.
// Note: This operator[] returns the Nth row, NOT the Nth index of array_
template<class Comparable>
vector<Comparable> Matrix<Comparable>::operator[](unsigned row)
{
	if (row > num_rows_ || row <= 0)
	{	// Precondition violated
		cout << "Invalid selection of row\n";
		return vector<Comparable>();
	}
	
	vector<Comparable> out;
	for (unsigned int j=0; j < NumCols(); j++)
	{
		out.push_back(array_[row-1][j]);
	}
	return out;
}

// Operator+ for two Matricies
// Precondition: Both Matricies must be of equal row and column
// Post: If precondition violated, operator+ returns an empty matrix
template<class Comparable>
Matrix<Comparable> Matrix<Comparable>::operator+
	(const Matrix<Comparable>& rhs) const
{
	if ((num_rows_ != rhs.num_rows_) || (num_cols_ != rhs.num_cols_))
	{	// Precondition violated
		cout << "Both matricies must be of equal size";
		return std::move(Matrix());
	}

	Matrix<Comparable> result(*this);

	for (unsigned int i = 0; i < num_rows_; i++)
	{
		for (unsigned int j = 0; j < num_cols_; j++)
		{
			result.array_[i][j] += rhs.array_[i][j];
		}
	}

	return result;
}

// Operator+ for a Matrix + string literal
// Description: Concatenates the string into every cell of the matrix
// Precondition: Comparable must be std::string
// Post: n/a
template<class Comparable>
Matrix<Comparable> Matrix<Comparable>::operator+(const char* rhs) const
{
	string str(rhs);
	Matrix<Comparable> result(*this);

	for (unsigned int i = 0; i < num_rows_; i++)
	{
		for (unsigned int j = 0; j < num_cols_; j++)
		{
			result.array_[i][j] += str;
		}
	}

	return result;
}

// Swap
// Description: Trade *this's data members with other
// Precondition:
// Post: 
template<class Comparable>
void Matrix<Comparable>::Swap(Matrix<Comparable>& other)
{
	std::swap(*this, other);
}

/******************Functions********************/

// Description: Overloads the insertion operator to handle Matrices
// Precondition: n/a
// Postcondition: If rhs is an empty matrix of size 0x0, then "empty matrix"
//	is printed instead
template<class Comparable>
ostream& operator<<(ostream& os, const Matrix<Comparable>& rhs)
{
	if (rhs.NumRows() < 1)
	{
		os << "empty matrix";
		return os;
	}

	for (unsigned int i=0; i < rhs.NumRows(); i++)
	{
		for (unsigned int j=0; j < rhs.NumCols(); j++)
		{
			os << rhs.GetElement(i,j) << " ";
		}
		os << endl;
	}
	return os;
}

// Description: cout every element of a given vector
// Precondition: n/a
// Postcondition: n/a
template<class Comparable>
void PrintVec(const vector<Comparable>& vec)
{
	for (const auto& element : vec)
	{
		cout << element << " ";
	}
	
	cout << endl;
}

#endif
