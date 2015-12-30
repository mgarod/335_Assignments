/***************************************************************
Title:          QuadraticProbing.h
Author:         Michael Garod
Date Created:   10/24/2015
Class:          Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:      Ioannis Stamos
Purpose:        Assignment #3
Description:    A hash table template that uses quadratic probing.
Note:           This code was primarily taken from Data Structures and
                Algorithm Analysis in C++ (Fourth Edition), by Mark Allen Weiss
                http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/
***************************************************************/
#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
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
    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
    {
        makeEmpty( );
    }

    bool contains( const HashedObj & x ) //const
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

    /* Getters for statistics of the table */
    // This will return the number of elements in the hash table
    int getNumElements(){return currentSize; };

    // This will return the size of the table
    int getTableSize(){return array.capacity(); };

    // This uses the previous two casted to floats to avoid integer division.
    float getLoadFactor()
    {
        return static_cast<float>(getNumElements()) / static_cast<float>(getTableSize());
    }

    /* This function works precisely as findPos() does, except it instead
    /   returns the number of probes required to find the object. Note that
    /   success on the first try is 1 probe, not 0.
    */
    int getNumProbes(const HashedObj &x) const
    {
        int offset = 1;
        int currentPos = myhash( x );
        int numProbes = 1;

        while( array[ currentPos ].info != EMPTY &&
               array[ currentPos ].element != x )
        {
            ++numProbes;
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }

        return numProbes;
    }

    int getCollisions(){return collisions;};

    /* END GETTERS */

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
    mutable int collisions = 0;

    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }


    /*  Modification: findPos() will now increment the mutable private data
            member 'collisions' for every iteration of this loop.
    */
    int findPos( const HashedObj & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x );

        while( array[ currentPos ].info != EMPTY &&
               array[ currentPos ].element != x )
        {
            ++collisions;
            currentPos += offset;  // Compute ith quadratic probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }

        return currentPos;
    }

    void rehash( )
    {
        vector<HashEntry> oldArray = array;\
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

    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }
};

#endif
