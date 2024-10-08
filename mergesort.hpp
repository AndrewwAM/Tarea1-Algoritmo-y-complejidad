#include <bits/stdc++.h>
#include <vector>
#include <stdio.h>
using namespace std;


/**
 * @brief Fusiona dos vectores temporales de nuevo en el vector original.
 * 
 * @param arr El vector original.
 * @param left El índice inicial del subvector.
 * @param mid El índice medio del subvector.
 * @param right El índice final del subvector.
 */
void merge(vector<int>& arr, int left, int mid, int right)
{
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;

    // Vectores temporales
    vector<int> leftArr(sizeLeft), rightArr(sizeRight);

    // Copiar datos a los vectores temporales
    for (int i = 0; i < sizeLeft; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < sizeRight; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Fusionar los vectores temporales de nuevo en arr
    while (i < sizeLeft && j < sizeRight) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copiar elementos restantes de leftArr
    while (i < sizeLeft) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copiar elementos restantes de rightArr
    while (j < sizeRight) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}


/**
 * @brief Función principal de MergeSort.
 * 
 * @param arr El vector de enteros a ordenar.
 * @param left El índice inicial del subvector a ordenar.
 * @param right El índice final del subvector a ordenar.
 */
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left < right){
        int mid = left + (right - left) / 2;
        // División del arreglo
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        // Fusión de ambas partes
        merge(arr, left, mid, right);
    }
    // caso base
    return;
}