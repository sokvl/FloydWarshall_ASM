#include "Controller.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <random>
#include <thread>
#include <vector>

#include <Windows.h>


extern "C" {
    __declspec(dllimport) void FloydWarshallASM(signed a[], int size);
}

extern "C" {
	__declspec(dllimport) void floydWarshall(signed tab[], int n, int inf);
    __declspec(dllimport) void floydWarshallPart(signed graph[], int n, int k_start, int k_end, int inf);
}

Controller::Controller() {};

Controller::~Controller() {};

void measureFloyd(signed* tab, int size, std::chrono::microseconds& duration, int index) {

    signed* tabCopy = new signed[size * size];
    if (index == 0)
        std::copy(tab, tab + size * size, tabCopy);

    auto start = std::chrono::high_resolution_clock::now();
    FloydWarshallASM(index == 0 ? tab : tabCopy, size);
    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    delete[] tabCopy;
}

void Controller::setMode(bool newMode) {
	mode = newMode;
}

std::chrono::microseconds Controller::runFloydWarshall(bool flag, int threads) {

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    signed* tab = getGraph();
    int inf = getInf();
    int n = getN();
    std::vector<std::thread> thr;
    int k_per_thread = n / threads;

    if (flag) {
        if (threads == 1) {
            start = std::chrono::high_resolution_clock::now();
            floydWarshall(tab, n, inf);
            end = std::chrono::high_resolution_clock::now();
        } else {
            start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < threads; ++i) {
                int k_start = i * k_per_thread;
                int k_end = (i == threads - 1) ? n : k_start + k_per_thread;
                thr.emplace_back(floydWarshallPart, tab, n, k_start, k_end, inf); // Use 'tab', not 'graph'
            }

            for (auto& t : thr) {
                t.join();
            }
            end = std::chrono::high_resolution_clock::now();
        }
    } else {

        if (threads == 1) {
            start = std::chrono::high_resolution_clock::now();
            FloydWarshallASM(tab, n);
            end = std::chrono::high_resolution_clock::now();

            return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        }

       
        std::vector<std::chrono::microseconds>durations(threads);
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < threads; ++i) {            
           thr.emplace_back(measureFloyd, tab, n, std::ref(durations[i]), i);
        }
        for (auto& t : thr) {
            t.join();
        }
        end = std::chrono::high_resolution_clock::now();

        std::chrono::nanoseconds totalDuration(0);
        for (const auto& duration : durations) {
            totalDuration += duration;
        }
        return std::chrono::duration_cast<std::chrono::microseconds>(totalDuration/threads);
    }

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

std::vector<signed> Controller::loadGraph(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<signed> holder;
    int n;
    int n2;
    if (file.is_open()) {
        try {
            getline(file, line);
            std::istringstream dist_stream(line);
            signed current_int;
            while (dist_stream >> current_int) {
                if (current_int > 1999) { 
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

    setInf(1999);
    setN(n);

    return holder;

}

void Controller::generateGraph(const int size, int min_weight, int max_weight) {
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

void Controller::setGraphFromVector(std::vector<signed>& g) {
    if (graph != nullptr) {
        delete[] graph;
    }

    // Alokuj pamiêæ i przypisz zawartoœæ wektora 'g' do zmiennej 'graph'
    graph = new signed[g.size()];
    for (int i = 0; i < g.size(); i++) {
        graph[i] = g[i];
    }
}

signed* Controller::getGraph() { return graph; };
void Controller::setGraph(signed graph[]) {};
void Controller::saveGraph() {};

void Controller::setInf(int newInf) {
    inf = newInf;
}

void Controller::setN(int g_size) {
    size = g_size;
}

int Controller::getN() {
    return size;
}

int Controller::getInf() {
    return inf;
}

bool Controller::getMode() {
    return mode;
};

int Controller::getThreads() {
    return sliderValue;
}