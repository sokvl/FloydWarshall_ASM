#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <vector>


// Liczba maksymalnych wierzcho³ków w grafie
const int N = 10;

// Specjalna wartoœæ oznaczaj¹ca brak po³¹czenia/du¿¹ odleg³oœæ
const int INF = 99;

// Funkcja realizuj¹ca algorytm Floyda-Warshalla
std::vector<std::vector<int>> floydWarshall(std::vector<std::vector<int>>& graph, int n) {
    // Inicjalizacja macierzy odleg³oœci wyników
    std::vector<std::vector<int>> dist = graph;

    // Trzy zagnie¿d¿one pêtle wykonuj¹ce algorytm Floyda-Warshalla
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    return dist;
}

std::vector<std::vector<int>> generateRandomGraph(int n, int maxWeight) {
    std::vector<std::vector<int>> graph(n, std::vector<int>(n));

    // Inicjalizacja generatora liczb losowych
    srand(time(0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                // Waga krawêdzi od wierzcho³ka do samego siebie wynosi 0
                graph[i][j] = 0;
            }
            else {
                // Losowanie wagi krawêdzi
                int weight = rand() % (maxWeight + 1);
                graph[i][j] = weight;
            }
        }
    }

    return graph;
}
