/***************************************************************
Title:        PQPair.h
Author:       Michael Garod
Date Created: 11/15/2015
Class:        Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:    Ioannis Stamos
Purpose:      Assignment #4
Description:  A user created pair class to be used for the Mutable Priority
			  Queue. In MPQ, this is the HashedObj in HashEntry.
			  Definition includes method for std::hash() to hash on key.
***************************************************************/
#ifndef PQPAIR_H
#define PQPAIR_H

#include "LeftistNode.h"

/**
* Struct to be inserted into the hash table to allow for random access
* of the priority queue.
*/
template<typename Comparable, typename Pointer>
struct PQPair
{
	Comparable key;
	Pointer ptr;

	PQPair(const Comparable& k = 0, const Pointer p = nullptr) :
		key { k }, ptr { p } { }

	const bool operator!=(const PQPair& rhs) const {
		return key != rhs.key;
	}
};

/**
* Overloading std::hash so that no modification need be made to the way
* the Quadratic Probing hash table performs its hash.
*/
namespace std{
	template<>
	struct hash<PQPair<int, LeftistNode<int>*>>
	{
		size_t operator()(const PQPair<int, LeftistNode<int>*>& pqp) const{
			hash<int> hf;
			return hf(pqp.key);
		};
	};
}

#endif
