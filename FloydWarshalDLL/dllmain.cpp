// dllmain.cpp : Definiuje punkt wejścia dla aplikacji DLL.
#include "pch.h"

void floydWarshall(signed tab[], int n, int inf) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (tab[i * n + k] == inf || tab[k * n + j] == inf) {
                    continue;
                }
                signed int newWeight = tab[i * n + k] + tab[k * n + j];
                if (tab[i * n + j] > newWeight) {
                    tab[i * n + j] = newWeight;
                }
            }
        }
    }
}

void floydWarshallPart(signed graph[], int n, int k_start, int k_end, int inf) {
    for (int k = k_start; k < k_end; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (graph[i * n + k] != inf && graph[k * n + j] != inf) {
                    int newDist = graph[i * n + k] + graph[k * n + j];
                    if (graph[i * n + j] > newDist) {
                        graph[i * n + j] = newDist;
                    }
                }
            }
        }
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

