#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <thread>

using namespace System::Collections::Generic;

public ref class Controller {
private:
	/*
	* Representation of current program mode (C++ - true/ASM - false)
	* @type bool
	*/
	bool mode = false;
	signed* graph;
	int size;
	int inf;
	int sliderValue = std::thread::hardware_concurrency();


public:
	/*
	* Controller constructor method
	*/
	Controller();
	/*
	* Controller destructor method
	*/
	~Controller();

	/*
	* Setter method for program mode
	* @param bool - mode parameter to set
	*/
	void setMode(bool newMode);
	bool getMode();

	int getThreads();

	std::chrono::microseconds runFloydWarshall(bool flag, int threads);
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

	void setInf(int newInf);

	void setN(int g_size);

	int getN();
	int getInf();

	void setSliderValue(int newValue) {
		sliderValue = newValue;
	}

	int getSliderValue() {
		return sliderValue;
	}
};