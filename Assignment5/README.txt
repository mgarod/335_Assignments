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
Contents:		The .zip file should contain 7 files:
			1.	main.cpp
			2.	Makefile
			3.	Graph1.txt
			4.	Graph2.txt
			5.	Graph.cpp
			6.	Graph.h
			7.	README.txt
***************************************************************/

I. Parts Completed
	- All parts of this assignments were completed

II. Bugs Encountered
	- None

III. Run Instructions
	- make all
		- make RunSearchGraph1
		- make RunSearchGraph2

IV. Input/Output Files
	- Input: Graph1.txt, Graph2.txt
	- Output:  n/a

V. Notes
	- The included makefile is only programmed to run on Graph1.txt
		and Graph2.txt

	- Here is a brief sketch of the class structure:

		struct Vertex{
			struct Neighbor{
				float edgecosts;
			}
			list<Neighbor>;
		}

		class Graph{
			vector<Vertex>;
		}

	- I used std::priority_queue<Neighbor> from the <queue> Library. By
		default, this is a max heap
	- I implemented a comparator class NCompare, in order to manipulate the
		std::priority_queue to become a min heap, which specifically heapifies
		on Neighbor::edge_cost.
	- Included in this directory is a set of additional test graphs that have
		more nodes, and vary from 100%, 50% and 25% connectivity. These varied
		graphs provided for greatest testing of cases of loops and disconnected
		nodes in the graph, as well as sinks and sources.