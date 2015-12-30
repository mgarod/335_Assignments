/***************************************************************
Title:        dsexceptions.h
Author:       Michael Garod
Date Created: 11/15/2015
Class:        Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:    Ioannis Stamos
Purpose:      Assignment #4
Description:  Exceptions to be used by other classes.
Note:         This code was primarily taken from Data Structures and
              Algorithm Analysis in C++ (Fourth Edition), by Mark Allen Weiss
              http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/
***************************************************************/

#ifndef DS_EXCEPTIONS_H
#define DS_EXCEPTIONS_H

class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

#endif