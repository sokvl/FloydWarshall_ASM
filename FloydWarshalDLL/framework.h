#pragma once

#define WIN32_LEAN_AND_MEAN             // Wyklucz rzadko używane rzeczy z nagłówków systemu Windows
// Pliki nagłówkowe systemu Windows
#include <windows.h>

extern "C" { 
	__declspec(dllexport) void floydWarshall(signed tab[], int n, int inf);
	__declspec(dllexport) void floydWarshallPart(signed graph[], int n, int k_start, int k_end, int inf);
}