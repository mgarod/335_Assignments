/******************************************************
Title:			main.cpp
Author:			Michael Garod
Date Created:	9/10/15
Class:			Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:		Ioannis Stamos
Purpose:		Assignment #1
Description:	Main/Tester file for the Matrix class.
******************************************************/

#include "matrix.h"

void TestPart1()
{
	cout << "TestPart1() tests Matrix<int>, and the big five\n";
	Matrix<int> a, b; //Two empty matrices are created
	
	cout << a.NumRows() << " " << a.NumCols() << endl; // yields 0 0

	a.ReadMatrix(); // User provides number of rows, columns and matrix values.

	cout << a << endl; // Output should be what user entered.
	b.ReadMatrix();
	cout << b << endl;

	cout << "Copy Assignment a=b, then cout a\n";
	a = b; // Should call the copy assignment operator for a.
	cout << a << endl;

	cout << "Copy Constructor Matrix c = b, then cout c\n";
	Matrix<int> c = b; // Should call the copy constructor for a.
	cout << c << endl;

	cout << "Testing Move Constructor, Matrix d=move(c), then cout d:\n";
	Matrix<int> d = std::move(c); // Move constructor for d.
	cout << d << endl;

	cout << "Move Assignment of a=move(d), then print a:\n";
	a = std::move(d); // Move assignment operator for a.

	cout << a << endl;
} // Destructors will be called.

void TestPart2()
{
	cout << "TestPart2() tests Matrix<string>, +, []\n";
	Matrix<string> a, b;

	a.ReadMatrix(); // User provides input for matrix a.
	cout << a << endl;

	b.ReadMatrix(); // User provides input for matrix b.
	cout << b << endl;

	cout << "a + b = " << endl;
	cout << a + b << endl;

	cout << "d = a+b, then cout d\n";

	Matrix<string> d = a + b;
	cout << d << endl;
	// Matrices should have same size.
	// The default + operator for strings
	// will be used.

	cout << "d + hi_there\n";
	cout << d + "hi_there";
	
	cout << "PrintVec(a[1]): "; PrintVec(a[1]);
	cout << "PrintVec(b[2]): "; PrintVec(b[2]);
	// Should print the first row of a.
	// Should be print the second row of b.
	// Note, that the [] operator should return
	// a vector object.
} // End of TestPart2.

void TestPart3()
{
	cout << "TestPart3() tests Matrix<double>, and swap\n";
	Matrix<double> a, b;

	a.ReadMatrix(); // User provides input for matrix a.
	cout << "a:\n" << a << endl;

	b.ReadMatrix(); // User provides input for matrix b.
	cout << "b:\n" << b << endl;

	a.Swap(b);
	
	cout << "After swap()\n";
	cout << "a:\n" << a << endl;
	cout << "b:\n" << b << endl;
} // End of TestPart3.


int main()
{
	TestPart1();
	TestPart2();
	TestPart3();

	return 0;	
}
