/*****************************************************************************
Title:      	Graph.h
Author:     	Michael Garod
Date Created:	12/8/2015
Class:      	Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:  	Ioannis Stamos
Purpose:    	Assignment #5
Description:	Header file for the Graph class which is capable of
				calculating Dijkstra's Algorithm and printing results.
				Copy Constructor and Copy Assignment Operator is provided.
*****************************************************************************/
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <list>
#include <cmath>
#include <functional>
using namespace std;

struct Vertex{
	struct Neighbor{
		Vertex* neighbor;
		int neighbor_name;
		float edge_cost;

		Neighbor() : neighbor{nullptr}, neighbor_name{}, edge_cost{} {};
	};

	list<Neighbor> AdjList;
	int name;
	bool visited;// = false;
	int came_from;// who did I just come from to get the shortest path?
	float shortest_path;// = numeric_limits<int>::max();

	Vertex() : AdjList{}, name{}, visited{}, came_from{}, shortest_path{} {};
};

// Allows stl::priority_queue to minheap on Vertex::Neighbors min edge_cost
struct NCompare{
	bool operator()(const Vertex::Neighbor& lhs, const Vertex::Neighbor& rhs){
		return lhs.edge_cost > rhs.edge_cost;
	}
};

class Graph{
	public:
		Graph();
		Graph(ifstream& inputfile);
		~Graph();
		// If I have the time I will come back to flesh these out
		Graph(const Graph& rhs);
		Graph& operator=(const Graph& rhs);
		//Graph(Graph&& rhs);
		//Graph& operator=(Graph&& rhs);
		
		void PrintAll();
		void Dijkstra(int start);
		void PrintAllPaths(int start);

	private:
		vector<Vertex*> vertex_array_;
		int v_accessed_;
		int e_accessed_;

		void PAPhelper(Vertex* & v);

};

#endif