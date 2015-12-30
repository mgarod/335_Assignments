/***************************************************************
Title:			README.txt
Author:			Michael Garod
Date Created:	11/15/2015
Class:			Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:		Ioannis Stamos
Purpose:		Assignment #4
Description:	Brief description containing which parts of the assignment were
				completed, bugs encountered, instructions on how to run
				the program, and input/output files necessary or created.
Contents:		The .zip file should contain 20 files:
			1.	5_numbers.txt
			2.	20_numbers.txt
			3.	100_numbers.txt
			4.	100_test_deletion.txt
			5.	100_test_search.txt
			6.	1000_numbers.txt
			7.	1000_test_deletion.txt
			8.	1000_test_search.txt
			9.	10000_numbers.txt
			10.	dsexceptions.h
			11.	LeftistNode.h
			12.	Makefile
			13.	MutablePQ.h
			14.	PQPair.h
			15.	QuadraticProbing.cpp
			16.	QuadraticProbing.h
			17.	README.inputfiles.txt
			18.	README.txt
			19.	TestDelete.cpp
			20.	TestSearch.cpp
				
***************************************************************/

I. Parts Completed
	- All parts of this assignments were completed

II. Bugs Encountered
	- In-Place deletion destroys leftist heap property. Bug was resolved. See Notes for solution.

III. Run Instructions
	- Makefile
		- make all
		- make runsearch100
		- make runsearch1000
		- make rundelete100
		- make rundelete1000
		- make clean

IV. Input/Output Files
	- Input: 100_numbers.txt, 100_test_search.txt, 100_test_deletion.txt, 1000_numbers.txt, 1000_test_search.txt, 1000_test_deletion.txt

	- Output: N/A

V. Notes
	- Struct LeftistNode was removed from within the LeftistHeap/MutablePQ class in order to to allow the Hash Table access to nodes.

	- A new struct called PQPair was used to hash <key, node*> (see PQPair.h)

	- A new std::hash was defined to handle PQPair<key, node*> (see PQPair.h)
		- No alteration was made to private functions of QuadraticProbing.h

	- Removal of any node in the heap is done by deletion in place (hereafter called "in-place removal"), instead of swapping the item to the root and using delete min.
		- The item to be removed, hereafter called N, is replaced by the merge of N's left and right children.
		- In-place removal of N implies that the leftist heap property(where we require the left child's NPL >= right child's NPL) can be destroyed in ancestors of N.
		- We restore the heap property of N by traversing the ancestral path to the root using parent pointers. If there is a violation of the leftist heap property in any parent, we swap children, and reassign NPL of the parent to be one plus the NPL of the right child.

