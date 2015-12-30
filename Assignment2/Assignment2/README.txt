/***************************************************************
Title:			README.txt
Author:			Michael Garod
Date Created:	10/1/2015
Class:			Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:		Ioannis Stamos
Purpose:		Assignment #2
Description:	Brief description containing which parts of the assignment were
				completed, bugs encountered, instructions on how to run
				the program, and input/output files necessary or created.
Contents:		The .zip file should contain 12 files: AvlTree.h,
				BinarySearchTree.h, dsexceptions.h, Makefile, QueryTrees.cpp,
				README.txt, rebase210.txt, SequenceMap.cpp, SequenceMap.h,
				sequences.txt, TestRangeQuery.cpp, TestTrees.cpp
***************************************************************/

I. Parts Completed
	- All parts of this assignments were completed

II. Bugs Encountered
	- None

III. Run Instructions
	- makeall
		- make run1bst
		- make run1avl
		- make run2bst
		- make run2avl
		- make run3
	- make clean

IV. Input/Output Files
	- Input: rebase210.txt, sequences.txt
	- Output: n/a

V. Notes
	- My printTreeRange(min, max) function is exactly an inorder traversal. The only difference here is that the print condition is if the element observed is in the inclusive range of min and max (min <= element <= max). This implementation may be considered naive. A better approach may be found.