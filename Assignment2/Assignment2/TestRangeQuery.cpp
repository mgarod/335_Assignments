/******************************************************
Title:			TestRangeQuery.cpp
Author:			Michael Garod
Date Created:	9/24/15
Class:			Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:		Ioannis Stamos
Purpose:		Assignment #2
Description:	Tests AvlTree::printTreeRange method functions properly.
Note:			BST does not have such a printTreeRange function.
******************************************************/

#include "SequenceMap.h"
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include <fstream>
#include <sstream>
using namespace std;

template<class Tree>
void TestRangeQuery(string db_filename, Tree my_tree, string k1, string k2)
{
	ifstream db_file(db_filename);
	string current_line;

	// Skip rebase210.txt header; merely skips 11 lines
	int header_counter = 10;
	while (header_counter > 0)
	{
		getline(db_file, current_line);
		header_counter--;
	}
	// Internal pointer is now right before "AanI/TTA'TAA//" on line 11
	//                                      ^

	while (getline(db_file, current_line))
	{
		// Check if you you pulled an empty/bad line from the db_file
		if (current_line.length() < 1)
		{
			continue;
		}

		stringstream ss_current_line(current_line);
		string acronym;
		getline(ss_current_line, acronym, '/');

		string rec_seq;
		// The length > 0 is the check to see if you hit "//"
		while (getline(ss_current_line, rec_seq, '/')
			&& rec_seq.length() > 0)
		{
			SequenceMap input_sqmap{ rec_seq, acronym };
			my_tree.insert(input_sqmap);
		}
	}
	
	//cout << "\nTesting Range between: " << k1 << " and " << k2 << endl;
	SequenceMap min{k1, ""};
	SequenceMap max{k2, ""};
	my_tree.printTreeRange(min, max);
};

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		cout << "Usage: " << argv[0];
		cout << " <databasefilename> <rec seq1> <rec seq2>\n";
		return 0;
	}

	string db_filename(argv[1]);
	string key1 = argv[2];
	string key2 = argv[3];
	AvlTree<SequenceMap> my_AVL;

	TestRangeQuery(db_filename, my_AVL, key1, key2);

	return 0;
}
