/*****************************************************************************
Title:      	main.cpp
Author:     	Michael Garod
Date Created:	12/8/2015
Class:      	Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:  	Ioannis Stamos
Purpose:    	Assignment #5
Description:	Main file to implement the Graph class and calculate
				Dijkstra's Algorithm
*****************************************************************************/
#include "Graph.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv){
	if (argc != 3){
		cout << "Usage: " << argv[0] << " <GRAPH_FILE> <STARTING_VERTEX>\n";
		return 1;
	}

	int start = atoi(argv[2]);
	
	ifstream inputfile(argv[1]);

	Graph mygraph(inputfile);

	mygraph.Dijkstra(start);

	inputfile.close();

	return 0;
}