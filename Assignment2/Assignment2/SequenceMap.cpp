/******************************************************
Title:			SequenceMap.cpp
Author:			Michael Garod
Date Created:	9/24/15
Class:			Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:		Ioannis Stamos
Purpose:		Assignment #2
Description:	Implementation file to simulate a biological structure.
******************************************************/

#include "SequenceMap.h"

SequenceMap::SequenceMap(const string& a_rec_seq, const string& an_enz_acro)
	: recognition_sequence_{}, enzyme_acronyms_{}
{
	recognition_sequence_ = a_rec_seq;
	enzyme_acronyms_.push_back(an_enz_acro);
}

bool SequenceMap::operator<(const SequenceMap& rhs) const
{
	if (recognition_sequence_ < rhs.recognition_sequence_)
		return true;
	else // if (recognition_sequence_ > rhs.recognition_sequence_)
		return false;
}

/** Precondition1: recognition_sequencess are equal
*	Precondition2: other_sequence has only one acronym to merge into *this
*/
void SequenceMap::Merge(const SequenceMap& other_sequence)
{
	// If Precondition 1 is violated, then don't merge.
	if (recognition_sequence_ != other_sequence.recognition_sequence_)
	{
		//cout << "Recognition Sequences are not equal!\n";
		//cout << "Terminating Merge with no results\n";
		return;
	}

	// If the 1 acronym in other_sequence exists in *this, then don't merge.
	for (const auto& acro : enzyme_acronyms_)
	{
		if (acro == other_sequence.enzyme_acronyms_[0])
		{
			//cout << "For Rec.Seq.: " << recognition_sequence_ << endl;
			//cout << "Duplicate acronym! No action necessary.\n";
			return;
		}
	}

	// else { add the acronym to the vector }
	enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[0]);
}

/*** FUNCTIONS ***/

/** Part 1
* c) operator<<
*/
ostream& operator<<(ostream& os, const SequenceMap& rhs)
{
	os << "Rec. Seq.: " << rhs.recognition_sequence_ << " <--> ";
	os << "Enzyme Acronyms(" << rhs.enzyme_acronyms_.size() << "):";

	for (string element : rhs.enzyme_acronyms_)
	{
		os << " \"" << element << "\"";
	}
	return os;
}
