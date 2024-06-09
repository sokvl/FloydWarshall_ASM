#pragma once
#include <string>
#include <vector>

class Graph {
public:
	/*
	* Variable containing flattened 2-dim array to 1-dim representation
	* @type signed int
	*/
	signed* graph;

public:
	/*
	* Graph constructor method;
	*/
	Graph();
	/*
	* Graph destructor method;
	*/
	~Graph();

	/*
	* Getter method for graph representation
	* @return signed int[]
	*/
	signed* getGraph();
	/*
	* Setter method for graph representation
	* @param graph[] - 1-dim graph representation
	*/
	void setGraph(signed graph[]);
	/*
	* Method responsible for loading the graph from file
	*/
	std::vector<signed> loadGraph(const std::string& filename);
	/*
	* Method responsible for saving the graph to file
	*/
	void saveGraph();
	/*
	* Method responsible for generating 1-dim represenation of grapharray
	*/
	void generateGraph(int size, int min_weight, int max_weight);
	/*
	* Method responsible for setting graph from vector
	*/
	void setGraphFromVector(std::vector<signed>& g);
};