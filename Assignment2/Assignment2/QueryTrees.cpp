/******************************************************
Title:			QueryTrees.cpp
Author:			Michael Garod
Date Created:	9/24/15
Class:			Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:		Ioannis Stamos
Purpose:		Assignment #2
Description:	Tests that both the AVL Tree and BST are functional
******************************************************/

#include "SequenceMap.h"
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include <fstream>
#include <sstream>
using namespace std;

template<class Tree>
void QueryTrees(string db_filename, Tree my_tree)
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

	string user_input;
	do
	{
		cout << "\nEnter a recognition sequence to query: \n";
		cout << "To Quit, type: \"exit\"\n";
		getline(cin, user_input);
		cout << "You have entered: " << user_input << endl;
		if (user_input == "exit")
		{
			break;
		}

		SequenceMap query{ user_input, "" };
		if (my_tree.contains(query))
		{
			cout << "FOUND: " << my_tree.GetNode(query) << endl;
		}
		else
		{
			cout << "No Match Found" << endl;
		}
	} while (user_input != "exit");
};

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << "Usage: " << argv[0];
		cout << " <databasefilename> <tree-type>\n";
		return 0;
	}

	string db_filename(argv[1]);
	string param_tree(argv[2]);

	if (param_tree == "BST")
	{
		BinarySearchTree<SequenceMap> my_BST;
		QueryTrees(db_filename, my_BST);
	}
	else if (param_tree == "AVL")
	{
		AvlTree<SequenceMap> my_AVL;
		QueryTrees(db_filename, my_AVL);
	}
	else // Bad Tree Flag
	{
		cout << "Unknown tree type " << param_tree;
		cout << " (User should provide BST, or AVL)" << endl;
	}

	return 0;
}
