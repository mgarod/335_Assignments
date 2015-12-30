/*****************************************************************************
Title:      	Graph.cpp
Author:     	Michael Garod
Date Created:	12/8/2015
Class:      	Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:  	Ioannis Stamos
Purpose:    	Assignment #5
Description:	Implementation file for the Graph class which is capable of
				calculating Dijkstra's Algorithm and printing results.
				Copy Constructor and Copy Assignment Operator is provided.
*****************************************************************************/
#include "Graph.h"

// Trivial Default Constructor
Graph::Graph() : v_accessed_{0}, e_accessed_{0} {}

// Constructor when given an input file stream
Graph::Graph(ifstream& ifs) : v_accessed_{0}, e_accessed_{0}{
	// Temporaries for handling the filestreams
	string str;
	int num_vertices;

	getline(ifs, str);
	num_vertices = stoi(str);

	// Make vector of all vertices
	vertex_array_.resize(num_vertices);

	for (auto& entry : vertex_array_){
		entry = new Vertex;
	}

	while (getline(ifs, str)){
		stringstream ss(str);

		// Which vertex are we handling? (First entry in a line)
		int vertexname;
		ss >> vertexname;
		vertex_array_[vertexname]->name = vertexname;

		// Temporaries to extract neighborname and edgecost
		int neighborname;
		float edgecost;
		while (ss >> neighborname){
			if (neighborname == -1){
				break;
			}

			ss >> edgecost;

			// Build neighbor
			Vertex::Neighbor n;
			n.neighbor = vertex_array_[neighborname];
			n.neighbor_name = neighborname;
			n.edge_cost = edgecost;

			// Store neighbor in AdjList
			vertex_array_[vertexname]->AdjList.push_back(n);
		}
	}
}

// Destructor
Graph::~Graph(){
	for (auto& entry : vertex_array_){
		delete entry;
		entry = nullptr;
	}
}

// Copy Constructor
Graph::Graph(const Graph& rhs){
	*this = rhs;
}

// Copy Assignment Operator
Graph& Graph::operator=(const Graph& rhs){
	vertex_array_.resize(rhs.vertex_array_.size());

	for (int i = 0; i < rhs.vertex_array_.size(); i++){
		// Make a duplicate vertex
		vertex_array_[i] = new Vertex;
		vertex_array_[i]->name = rhs.vertex_array_[i]->name;
		vertex_array_[i]->visited = rhs.vertex_array_[i]->visited;
		vertex_array_[i]->came_from = rhs.vertex_array_[i]->came_from;
		vertex_array_[i]->shortest_path = rhs.vertex_array_[i]->shortest_path;

		// Make duplicate AdjList for each vertex
		const auto& rhslist = rhs.vertex_array_[i]->AdjList;
		auto& list = vertex_array_[i]->AdjList;
		for (auto it = rhslist.begin(); it != rhslist.end(); ++it){
			Vertex::Neighbor n;
			n.neighbor_name = it->neighbor_name;
			n.edge_cost = it->edge_cost;
			n.neighbor = vertex_array_[it->neighbor_name];
			list.push_back(n);
		}
	}
	return *this;
}

// Debugging Method
void Graph::PrintAll(){
	cout << "Number of Vertices: " << vertex_array_.size() << endl;

	for (int i = 0; i < vertex_array_.size(); ++i){
		const auto& v = vertex_array_[i];
		cout << "vertex: " << i << endl;
		cout << " @visited: " << v->visited << endl;
		cout << " @came_from: " << v->came_from << endl;
		cout << " @shortest_path: " << v->shortest_path << endl;

		const auto& list = vertex_array_[i]->AdjList;

		if (list.size() > 0){
			//cout << "   vertex: " << i << " has the following neighbors\n";
			for (auto it = list.begin(); it != list.end(); ++it){
				cout << "  - Neighbor: " << it->neighbor_name;
				cout << "  * EdgeCost: " << it->edge_cost << endl;
			}
		}
		else{
			cout << "   - vertex: " << i << " has no neighbors\n";
		}
	}
}

// Print all paths 
void Graph::PrintAllPaths(int start){
	cout << "Total Vertex Access: " << v_accessed_ << endl;
	cout << "Total Edge Access: " << e_accessed_ << endl;

	for (int i = 0; i < vertex_array_.size(); ++i){
		cout << "Cost[" << start << "," << i;
		cout << "] = " << vertex_array_[i]->shortest_path << endl;
		
		// If the target vertex has a path
		if(vertex_array_[i]->came_from > -1){
			cout << "  - path from " << start << " to " << i << " = (";

			if(start != i){
				PAPhelper(vertex_array_[vertex_array_[i]->came_from]);
				cout << vertex_array_[i]->name << ")\n";
			}
			else{
				cout << i << ")\n";
			}	
		}
		else{ // Error: This vertex cannot reach the start point
			cout << "  - No path exists" << endl;	
		}
	}
	cout << endl;
}

void Graph::PAPhelper(Vertex* & v){
	if(v->came_from == -1){ 
		// Error: This vertex cannot reach the start point
		cout << "unreachable vertex";
		return;
	}
	else if(v->name == v->came_from){ // Base Case, reached starting point
		cout << v->name << ",";
	}
	else{ // Vertex along path to starting point
		PAPhelper(vertex_array_[v->came_from]);
		cout << v->name << ",";
	}
}

void Graph::Dijkstra(int start){
	// Set V and E accessed_ to zero
	v_accessed_ = 0;
	e_accessed_ = 0;

	// Set all unvisited, infinity shortest path, and no predecessor
	for (auto& v : vertex_array_){
		v->shortest_path = INFINITY;
		v->visited = false;
		v->came_from = -1;	// -1 is place holder when not yet visited
		v_accessed_++;
	}

	// Make the trivial calculations for the starting point
	// 1 access for the start point
	auto& startvertex = vertex_array_[start];
	startvertex->shortest_path = 0;
	startvertex->came_from = start;
	
	// Count the intial vertex
	v_accessed_++;

	priority_queue<Vertex::Neighbor, vector<Vertex::Neighbor>, NCompare> pq;

	// Process the first vertex manually
	const auto& startlist = startvertex->AdjList;
	for(auto it = startlist.begin(); it != startlist.end(); ++it){
		// For every neighbor of the start vertex
		e_accessed_++;

		// Consider every neighbor of the start vertex
		if(startvertex->shortest_path + it->edge_cost <
				it->neighbor->shortest_path){
			it->neighbor->shortest_path =
				startvertex->shortest_path + it->edge_cost; 
			pq.push(*it);
			it->neighbor->visited = true;
			it->neighbor->came_from = start;
		}
	}
	startvertex->visited = true;

	// Continue the algorithm until all possibilities are exhausted
	while(!pq.empty()){
		Vertex* v = (pq.top()).neighbor;
		pq.pop();

		// Get neighbors of the current vertex
		const auto& list = v->AdjList;
		for(auto it = list.begin(); it != list.end(); ++it){
			// For every neighbor, we access the vertex
			// For every neighbor, we access the edge to that vertex
			v_accessed_++;
			e_accessed_++;
			
			// If current path to neighbor is shorter, then update it
			if(v->shortest_path + it->edge_cost <
				it->neighbor->shortest_path){
				it->neighbor->shortest_path = v->shortest_path + it->edge_cost;
				it->neighbor->came_from = v->name;
			}
			// If the neighbor of v has not been observed, enqueue
			if(it->neighbor->visited == false){
				pq.push(*it);
				it->neighbor->visited = true;
			}
		}
	}

	PrintAllPaths(start);
}
