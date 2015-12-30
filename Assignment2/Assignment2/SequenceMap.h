/******************************************************
Title:			SequenceMap.h
Author:			Michael Garod
Date Created:	9/24/15
Class:			Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:		Ioannis Stamos
Purpose:		Assignment #2
Description:	Header/Declaration file to simulate a biological structure.
******************************************************/

#ifndef SEQUENCEMAP_H
#define SEQUENCEMAP_H

#include <iostream>
#include <string>
#include <vector>
#include "dsexceptions.h"
using namespace std;

class SequenceMap
{
	public:
		/**
		* Destructor
		* Empty Constructor
		* Copy Constructor
		* Copy Assignment
		* Move Constructor
		* Move Assignment
		*/
		~SequenceMap() = default;
		SequenceMap() = default;
		SequenceMap(const SequenceMap&) = default;
		SequenceMap& operator=(const SequenceMap&) = default;
		SequenceMap(SequenceMap&&) = default;
		SequenceMap& operator=(SequenceMap&&) = default;

		/** Part 1
		* a) 2 parameter constructor
		* b) operator<
		* c) operator<<
		* d) Merge
		*/
		SequenceMap(const string& a_rec_seq, const string& an_enz_acro);
		bool operator<(const SequenceMap& rhs) const;
		friend ostream& operator<<(ostream& os, const SequenceMap& rhs);
		void Merge(const SequenceMap& other_sequence);
		


	private:
		string recognition_sequence_;
		vector<string> enzyme_acronyms_;
};

#endif
