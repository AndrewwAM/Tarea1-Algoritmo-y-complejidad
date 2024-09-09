#include <vector>
#include <algorithm>
#include <limits>

class CountingSort {
public:
    static void sort(std::vector<int>& arr) {
        if (arr.empty()) return;

        // Find range of array elements
        int min = *std::min_element(arr.begin(), arr.end());
        int max = *std::max_element(arr.begin(), arr.end());

        // Create count array
        std::vector<int> count(max - min + 1, 0);

        // Count occurrences
        for (int num : arr) {
            count[num - min]++;
        }

        // Modify count array to store actual position of elements
        for (size_t i = 1; i < count.size(); i++) {
            count[i] += count[i - 1];
        }

        // Build output array
        std::vector<int> output(arr.size());
        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[arr[i] - min] - 1] = arr[i];
            count[arr[i] - min]--;
        }

        // Copy output array to original array
        arr = output;
    }
};







/*
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

// Función para particionar el arreglo
int qpartition(vector<int>& arr, int start, int end) {
    int pivot = arr[end];
    int i = start - 1;
    for (int j = start; j < end; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[end]);
    return i + 1;
}

void quickerSort(vector<int>& arr, int start, int end) {
    while (start < end) {
        int pivotIndex = qpartition(arr, start, end);
        thread leftThread, rightThread;

        if (pivotIndex - start > 1000) { // Umbral de partición
            leftThread = thread(quickerSort, ref(arr), start, pivotIndex - 1);
        } else {
            quickerSort(arr, start, pivotIndex - 1);
        }

        if (end - pivotIndex > 1000) { // Umbral de partición
            rightThread = thread(quickerSort, ref(arr), pivotIndex + 1, end);
        } else {
            quickerSort(arr, pivotIndex + 1, end);
        }

        if (leftThread.joinable()) leftThread.join();
        if (rightThread.joinable()) rightThread.join();

        break;
    }
}

*/