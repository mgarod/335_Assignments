/***************************************************************
Title:        QuadraticProbing.h
Author:       Michael Garod
Date Created: 11/15/2015
Class:        Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:    Ioannis Stamos
Purpose:      Assignment #4
Description:  A Hash Table using Quadratic Probing with added definitions such
              as printall(), isEmpty(), isDeleted(), and Find(). These new
              method are for testing and specific to the use of MutablePQ.
Note:         This code was primarily taken from Data Structures and
              Algorithm Analysis in C++ (Fourth Edition), by Mark Allen Weiss
              http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/
***************************************************************/
#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
#include "dsexceptions.h"
using namespace std;

int nextPrime( int n );

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
  public:

    /**
    * A simple testing method to print every active entry in the table
    */
    void printall(){
        for (unsigned i =0; i < array.size(); i++)
        {
            if(array[i].info == ACTIVE)
            {
                // Reference for leftistnode pointer in the PQPair
                // Type is LeftistNode<Comparable>*
                auto &x = (array[i].element).ptr;
                
                // Print all relations of the node
                cout << "key: " << x->element << endl;
                cout << "\tnpl: " << x->npl << endl;
                if(x->left != nullptr)
                    cout << "\tleft value: " << x->left->element << endl;
                else
                    cout << "\tleft value: -" << endl;

                if(x->right != nullptr)
                    cout << "\tright value: " << x->right->element << endl;
                else
                    cout << "\tright value: -" << endl;

                if(x->parent != nullptr)
                    cout << "\tparent value: " << x->parent->element << endl;
                else
                    cout << "\tparent value: -" << endl;
            }
        }
    }


    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
      { makeEmpty( ); }

    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }

    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }

    bool insert( const HashedObj & x )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        array[ currentPos ].element = x;
        array[ currentPos ].info = ACTIVE;

            // Rehash; see Section 5.5
        if( ++currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }
    
    bool insert( HashedObj && x )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        array[ currentPos ] = std::move( x );
        array[ currentPos ].info = ACTIVE;

            // Rehash; see Section 5.5
        if( ++currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

    /**
    * Returns the HashedObj requested
    */
    HashedObj& Find( const HashedObj& x ){
        if (!contains(x)){
            cout << "Trying to find something not in the hash\n";
            throw IllegalArgumentException{ };
        }

        int currentPos = findPos( x );
        return array[currentPos].element;
    }

    // 
    const bool isEmpty( const HashedObj& x ){
        int currentPos = findPos( x );
        return array[ currentPos ].info == EMPTY;
    }

    const bool isDeleted( const HashedObj& x ){
        int currentPos = findPos( x );
        return array[ currentPos ].info == DELETED;
    }

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
          : element{ e }, info{ i } { }
        
        HashEntry( HashedObj && e, EntryType i = EMPTY )
          : element{ std::move( e ) }, info{ i } { }
    };
    
    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    int findPos( const HashedObj & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x );

        while( array[ currentPos ].info != EMPTY &&
               array[ currentPos ].element != x )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }

        return currentPos;
    }

    void rehash( )
    {
        vector<HashEntry> oldArray = array;

            // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.info = EMPTY;

            // Copy table over
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE )
                insert( std::move( entry.element ) );
    }

    /**
    * See PQPair.h for the definition of the hash overload of PQPair
    */
    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }
};

#endif
