#pragma once
#include <string>
#include <vector>

public ref class Graph {
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

	std::vector<signed> Graph::loadGraph(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<signed> holder;
    int n, n2;
    if (file.is_open()) {
        try {
            getline(file, line);
            std::istringstream dist_stream(line);
            signed current_int;
            while (dist_stream >> current_int) {
                if (current_int > 999) {
                    throw std::invalid_argument("Too big weight.");
                }
                holder.push_back(current_int);
            }
            n2 = holder.size();
            n = std::sqrt(n2);
            if (std::floor(n) != n) {
                throw std::invalid_argument("Graph is not symmetrical.");
            }
        }
        catch (const std::exception& err) {
            std::cerr << "Something went wrong\n";
        }
    }
    file.close();

    return holder;

}

void Graph::generateGraph(const int size, int min_weight, int max_weight) {
    std::vector<int> graph(size * size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min_weight, max_weight);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) {
                graph[i * size + j] = 0;
            }
            else {
                bool no_connection = dis(gen) % 3 == 0;
                graph[i * size + j] = no_connection ? max_weight + max_weight + 1 : dis(gen);
            }
        }
    }
}

void Graph::setGraphFromVector(std::vector<signed>& g) {
    if (graph != nullptr) {
        delete[] graph;
    }

    // Alokuj pamiêæ i przypisz zawartoœæ wektora 'g' do zmiennej 'graph'
    graph = new signed[g.size()];
    for (int i = 0; i < g.size(); i++) {
        graph[i] = g[i];
    }
}

signed* Graph::getGraph() { return graph; };
void Graph::setGraph(signed graph[]) {};
Graph::~Graph() {};
void Graph::saveGraph() {};
};