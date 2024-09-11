#include <bits/stdc++.h>
#include <vector>
#include <stdio.h>
using namespace std;

/**
 * @brief Ordena un vector de enteros utilizando el algoritmo de ordenación por selección.
 * 
 * @param arr El vector de enteros a ordenar.
 * @param n El tamaño del vector.
 */
void selectionSort(vector<int>& arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        // Encuentra el mínimo elemento en el array no ordenado
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // Intercambia el mínimo elemento encontrado con el primer elemento
        swap(arr[i], arr[minIdx]);
    }
}