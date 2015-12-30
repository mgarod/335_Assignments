/***************************************************************
Title:        TestDelete.cpp
Author:       Michael Garod
Date Created: 11/15/2015
Class:        Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:    Ioannis Stamos
Purpose:      Assignment #4
Description:  This program will fill a Mutable Priority Queue with entries
              from an input file, then delete all entries from a delete file.
***************************************************************/
#include <iostream>
#include <fstream>
#include "QuadraticProbing.h"
#include "MutablePQ.h"
#include "PQPair.h"
using namespace std;

int main(int argc, char** argv){
	if(argc != 3){
		cout << "Usage: " << argv[0] << " <input_file_to_create_queue> <input_file_to_check_search>\n";
		return 1;
	}	

	// Open input file. Exit if it fails.
	ifstream inputfile(argv[1]);
	if(!inputfile.good()){
		cout << "Error opening: " << argv[1] << endl;
		return 2;
	}

	// Open deletion file. Exit if it fails.
	ifstream deletefile(argv[2]);
	if(!deletefile.good()){
		cout << "Error opening: " << argv[2] << endl;
		return 3;
	}

	MutablePQ<int> my_mpq;

	int counter = 0;
	int input;
	while (inputfile >> input) {
		cout << "inserting: " << input << endl;
		my_mpq.insert(input);
		++counter;
	}

	cout << "\nSuccess inserting " << counter << " elements into the queue.\n";
	cout << "The minimum element is " << my_mpq.findMin() << ".\n";

	// Test deleteMin()
	int del=0;
	cout << "\nTesting DeleteMin()\n";
	my_mpq.deleteMin(del);
	cout << del << " - DeleteMin Successful\n\n";

	// Testing Remove(Comparable)
	while (deletefile >> del){
		if (my_mpq.Remove(del))
			cout << del << " Deletion Successful\n";
		else
			cout << del << " Was never in the heap; Cannot delete\n";

		if(my_mpq.Find(del))
			cout << del << " Serious problem with deletion\n";
	}
	
	return 0;
}

/*
*/