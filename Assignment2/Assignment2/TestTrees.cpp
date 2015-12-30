/******************************************************
Title:			TestTrees.cpp
Author:			Michael Garod
Date Created:	9/24/15
Class:			Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:		Ioannis Stamos
Purpose:		Assignment #2
Description:	Tests that a tree can insert and remove items. Compute Tree
				related statistics.
******************************************************/

#include "SequenceMap.h"
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>
#include <iomanip>
using namespace std;

template<class Tree>
void TestTrees(string db_filename, string query_filename, Tree my_tree)
{
	cout << "Part 2(b) 1\n\n";
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

	/**	Part 2(b)
	*	1. Construct and fill the tree from rebase210.txt. Log the time.
	*/
	cout << "Filling the tree...\n\n";
	const auto begin_fill = chrono::high_resolution_clock::now();

	while (getline(db_file, current_line) && current_line.length() > 1)
	{
		// length > 1 check is to see if you pulled an empty/bad line from the db_file

		stringstream ss_current_line(current_line);
		string acronym;
		getline(ss_current_line, acronym, '/');

		string rec_seq;
		// The length > 0 is the check to see if you hit "//"
		while (getline(ss_current_line, rec_seq, '/')
			&& rec_seq.length() > 0)
		{
			SequenceMap input_map(rec_seq, acronym);
			my_tree.insert(input_map);
		}
	}
	const auto end_fill = chrono::high_resolution_clock::now();
	cout << "Time Log:\n";
	cout << chrono::duration_cast<chrono::nanoseconds>(end_fill - begin_fill).count() << " ns" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end_fill - begin_fill).count() << " ms" << endl;
	cout << setw(50) << setfill('-') << "\n";

	/**	Part 2(b)
	*	2. Print number of nodes, and average depth.
	*/
	cout << "Part 2(b) 2\n\n";
	double num_nodes = my_tree.CountNodes();
	double internal_path_length = my_tree.SumOfDepths();
	double avg_depth = internal_path_length/num_nodes;
	double avg_depth_to_log_nodes = avg_depth / log2(num_nodes);
	cout << "Number of nodes in the tree: " << num_nodes << endl;
	cout << "Internal Path Length: " << internal_path_length << endl;
	cout << "Average Depth: " << avg_depth << endl;
	cout << "Average Depth Ratio (Avg / log2(nodes)): " << avg_depth_to_log_nodes << endl;
	cout << setw(50) << setfill('-') << "\n" ;

	/**	Part 2(b)
	*	3. Use sequences.txt to count number of successful queries. Log the time.
	*/
	cout << "Part 2(b) 3\n\n";

	int num_successful_queries = 0;
	ifstream q_file(query_filename);
	current_line.clear();

	cout << "Querying against sequences.txt...\n\n";
	const auto begin_query = chrono::high_resolution_clock::now();

	while (getline(q_file, current_line) && current_line.length() > 1)
	{
		SequenceMap input_sqmap{ current_line, "" };

		if (my_tree.contains(input_sqmap))
		{
			//cout << "FOUND: " << my_tree.GetNode(input_sqmap) << endl;
			num_successful_queries++;
		}
		else
		{
			cout << "No Match Found" << endl;
		}
	}
	
	cout << "\n";
	const auto end_query = chrono::high_resolution_clock::now();
	cout << "Total number of successful queries: " << num_successful_queries << endl;
	cout << "Time Log:\n";
	cout << chrono::duration_cast<chrono::nanoseconds>(end_query - begin_query).count() << " ns" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end_query - begin_query).count() << " ms" << endl;
	cout << setw(50) << setfill('-') << "\n";

	/**	Part 2(b)
	*	4. Remove every other sequence in sequences.txt from the tree.
	*/
	// Reset q_file and return the internal pointer of q_file to the beginning
	cout << "Part 2(b) 4\n\n";

	q_file.clear();
	q_file.seekg(0, ios::beg);
	int counter = 0;

	cout << "Beginning to remove...\n";
	const auto begin_remove = chrono::high_resolution_clock::now();

	while (getline(q_file, current_line))
	{
		// Remove only every other sequence found in sequences.txt
		if (counter % 2 == 0)
		{
			//cout << "Removing: " << current_line << endl;
			SequenceMap input_sqmap{ current_line, "" };
			my_tree.remove(input_sqmap);
		}

		counter++;
	}

	const auto end_remove = chrono::high_resolution_clock::now();
	cout << "\nTime Log:\n";
	cout << chrono::duration_cast<chrono::nanoseconds>(end_remove - begin_remove).count() << " ns" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end_remove - begin_remove).count() << " ms" << endl;
	cout << setw(50) << setfill('-') << "\n";

	/**	Part 2(b)
	*	5. Recompute and print number of nodes, and average depth.
	*/
	cout << "Part 2(b) 5\n\n";

	num_nodes = my_tree.CountNodes();
	internal_path_length = my_tree.SumOfDepths();
	avg_depth = internal_path_length/num_nodes;
	avg_depth_to_log_nodes = avg_depth / log2(num_nodes);
	cout << "Number of nodes in the tree: " << num_nodes << endl;
	cout << "Internal Path Length: " << internal_path_length << endl;
	cout << "Average Depth: " << avg_depth << endl;
	cout << "Average Depth Ratio (Avg / log2(nodes)): " << avg_depth_to_log_nodes << endl;
	cout << setw(50) << setfill('-') << "\n";
};


int main(int argc, char** argv)
{
	if (argc != 4)
	{
		cout << "Usage: " << argv[0];
		cout << " <databasefilename> <queryfilename> <tree-type>\n";
		return 0;
	}

	string db_filename(argv[1]);
	string query_filename(argv[2]);
	string param_tree(argv[3]);

	if (param_tree == "BST")
	{
		BinarySearchTree<SequenceMap> my_BST;
		TestTrees(db_filename, query_filename, my_BST);
	}
	else if (param_tree == "AVL")
	{
		AvlTree<SequenceMap> my_AVL;
		TestTrees(db_filename, query_filename, my_AVL);
	}
	else // Bad Tree Flag
	{
		cout << "Unknown tree type " << param_tree;
		cout << " (User should provide BST, or AVL)" << endl;
	}

	return 0;
}
