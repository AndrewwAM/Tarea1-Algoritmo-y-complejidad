#include <bits/stdc++.h>
#include <vector>
#include <stdio.h>
using namespace std;

/*
// Función para realizar la partición en QuickSort
int partition(vector<int>& vec, int low, int high) {
    int mid = low + (high - low) / 2;
    int pivot = vec[mid];
    swap(vec[mid], vec[high]);
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return i + 1;
}

// Función para QuickSort
void quickSort(vector<int>& vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

*/
// FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 

// Función de partición optimizada
int partition(vector<int>& arr, int start, int end) {
    
    
    // Mediana de tres como pivote
    /* Dejado fuera porque no es la implementacion estandar, 
       ademas dificulta probar el peor caso
       
    int mid = start + (end - start) / 2;
    if (arr[mid] < arr[start])
        swap(arr[mid], arr[start]);
    if (arr[end] < arr[start])
        swap(arr[end], arr[start]);
    if (arr[mid] < arr[end])
        swap(arr[mid], arr[end]);
    */
    
    int pivot = arr[end]; // El último elemento es el pivote
    int i = start - 1; // Índice para elementos más pequeños que el pivote

    for (int j = start; j <= end - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    // Colocar el pivote en su posición correcta
    swap(arr[i + 1], arr[end]);
    return i + 1;
}

// Implementación de Quicksort optimizada
void quickSort(vector<int>& arr, int start, int end) {
    if (start < end) {
        // Realizar la partición y obtener el índice del pivote
        int pivotIndex = partition(arr, start, end);

        // Llamadas recursivas en ambas particiones
        quickSort(arr, start, pivotIndex - 1); // Lado izquierdo
        quickSort(arr, pivotIndex + 1, end);   // Lado derecho
    }
}


