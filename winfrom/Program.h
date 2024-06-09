#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <vector>


// Liczba maksymalnych wierzcho�k�w w grafie
const int N = 10;

// Specjalna warto�� oznaczaj�ca brak po��czenia/du�� odleg�o��
const int INF = 99;

// Funkcja realizuj�ca algorytm Floyda-Warshalla
std::vector<std::vector<int>> floydWarshall(std::vector<std::vector<int>>& graph, int n) {
    // Inicjalizacja macierzy odleg�o�ci wynik�w
    std::vector<std::vector<int>> dist = graph;

    // Trzy zagnie�d�one p�tle wykonuj�ce algorytm Floyda-Warshalla
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
                // Waga kraw�dzi od wierzcho�ka do samego siebie wynosi 0
                graph[i][j] = 0;
            }
            else {
                // Losowanie wagi kraw�dzi
                int weight = rand() % (maxWeight + 1);
                graph[i][j] = weight;
            }
        }
    }

    return graph;
}
