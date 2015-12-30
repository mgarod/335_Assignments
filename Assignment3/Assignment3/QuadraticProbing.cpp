/***************************************************************
Title:          QuadraticProbing.cpp
Author:         Michael Garod
Date Created:   10/24/2015
Class:          Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:      Ioannis Stamos
Purpose:        Assignment #3
Description:    Functions dealing with prime numbers necessary for rehashing.
Note:           This code was primarily taken from Data Structures and
                Algorithm Analysis in C++ (Fourth Edition), by Mark Allen Weiss
                http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/
***************************************************************/
#include "QuadraticProbing.h"
#include <iostream>
using namespace std;

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
int nextPrime( int n )
{
    if( n % 2 == 0 )
        ++n;

    for( ; !isPrime( n ); n += 2 )
        ;

    return n;
}
