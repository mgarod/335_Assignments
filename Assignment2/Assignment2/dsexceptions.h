/******************************************************
Title:			dsexceptions.h
Author:			Michael Garod
Date Created:	9/24/15
Class:			Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:		Ioannis Stamos
Purpose:		Assignment #2
Description:	Declaration and Implementation for several exceptions
Note:			This code was taken entirely from Data Structures and
				Algorithm Analysis in C++ (Fourth Edition), by Mark Allen Weiss
				http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/
******************************************************/
#ifndef DS_EXCEPTIONS_H
#define DS_EXCEPTIONS_H

#include <exception>

class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

#endif
