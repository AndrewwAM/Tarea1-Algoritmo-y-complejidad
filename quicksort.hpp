#include <bits/stdc++.h>
#include <vector>
#include <stdio.h>
using namespace std;


/**
 * @brief Función de partición optimizada para Quicksort.
 * 
 * @param arr El vector de enteros a ordenar.
 * @param start El índice inicial del subvector a particionar.
 * @param end El índice final del subvector a particionar.
 * @return int La posición final del pivote.
 */
int partition(vector<int>& arr, int start, int end) {
    int pivot = arr[start];  // El primer elemento es el pivote
    int i = start;           // Índice para los elementos menores que el pivote

    for (int j = start + 1; j <= end; j++) {
        if (arr[j] < pivot) {
            i++;  // Incrementamos el índice para el próximo valor menor que el pivote
            swap(arr[i], arr[j]);  // Intercambiamos el elemento menor con el valor en i
        }
    }

    // Colocamos el pivote en su posición correcta (entre los menores y mayores)
    swap(arr[start], arr[i]);

    return i;  // Retornamos la posición final del pivote
}

/**
 * @brief Implementación de Quicksort optimizada con recursión de cola.
 * 
 * @param arr El vector de enteros a ordenar.
 * @param start El índice inicial del subvector a ordenar.
 * @param end El índice final del subvector a ordenar.
 */
void quickSort(vector<int>& arr, int start, int end) {
    while (start < end) {
        int pivotIndex = partition(arr, start, end);  // Realizamos la partición y obtenemos la posición del pivote

        // Recursión en la partición más pequeña
        if (pivotIndex - start < end - pivotIndex) {
            quickSort(arr, start, pivotIndex - 1);  // Recursión en el lado izquierdo
            start = pivotIndex + 1;                // Procesamos el lado derecho iterativamente
        } else {
            quickSort(arr, pivotIndex + 1, end);   // Recursión en el lado derecho
            end = pivotIndex - 1;                  // Procesamos el lado izquierdo iterativamente
        }
    }
}