#include <algorithm>
#include <vector>
#include <cmath>

class OptimizedQuickSort {
private:
    static constexpr int INSERTION_SORT_THRESHOLD = 16;

    // Insertion sort for small subarrays
    static void insertionSort(std::vector<int>& arr, int low, int high) {
        for (int i = low + 1; i <= high; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= low && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // Median of three for pivot selection
    static int medianOfThree(std::vector<int>& arr, int low, int high) {
        int mid = low + (high - low) / 2;
        if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
        if (arr[low] > arr[high]) std::swap(arr[low], arr[high]);
        if (arr[mid] > arr[high]) std::swap(arr[mid], arr[high]);
        return mid;
    }

    // Introsort
    static void introsortUtil(std::vector<int>& arr, int low, int high, int depthLimit) {
        while (high - low > INSERTION_SORT_THRESHOLD) {
            if (depthLimit == 0) {
                std::make_heap(arr.begin() + low, arr.begin() + high + 1);
                std::sort_heap(arr.begin() + low, arr.begin() + high + 1);
                return;
            }
            depthLimit--;

            int pivot = medianOfThree(arr, low, high);
            std::swap(arr[pivot], arr[high]);
            
            int p = partition(arr, low, high);
            introsortUtil(arr, p + 1, high, depthLimit);
            high = p - 1;
        }
        insertionSort(arr, low, high);
    }

    // Partition function for standard QuickSort
    static int partition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    // Dual-pivot QuickSort partition
    static std::pair<int, int> dualPivotPartition(std::vector<int>& arr, int low, int high) {
        if (arr[low] > arr[high]) std::swap(arr[low], arr[high]);
        int j = low + 1, g = high - 1, k = low + 1;
        int p = arr[low], q = arr[high];
        while (k <= g) {
            if (arr[k] < p) {
                std::swap(arr[k], arr[j]);
                j++;
            } else if (arr[k] >= q) {
                while (arr[g] > q && k < g) g--;
                std::swap(arr[k], arr[g]);
                g--;
                if (arr[k] < p) {
                    std::swap(arr[k], arr[j]);
                    j++;
                }
            }
            k++;
        }
        j--;
        g++;
        std::swap(arr[low], arr[j]);
        std::swap(arr[high], arr[g]);
        return {j, g};
    }

    // Three-way QuickSort partition (Dutch National Flag)
    static std::pair<int, int> threeWayPartition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1, j = high, p = low - 1, q = high;
        while (true) {
            while (arr[++i] < pivot);
            while (pivot < arr[--j]) if (j == low) break;
            if (i >= j) break;
            std::swap(arr[i], arr[j]);
            if (arr[i] == pivot) { p++; std::swap(arr[p], arr[i]); }
            if (arr[j] == pivot) { q--; std::swap(arr[j], arr[q]); }
        }
        std::swap(arr[i], arr[high]);
        j = i - 1;
        i = i + 1;
        for (int k = low; k < p; k++, j--) std::swap(arr[k], arr[j]);
        for (int k = high - 1; k > q; k--, i++) std::swap(arr[i], arr[k]);
        return {j, i};
    }

    // Dual-pivot QuickSort
    static void dualPivotQuickSort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            if (high - low < INSERTION_SORT_THRESHOLD) {
                insertionSort(arr, low, high);
                return;
            }
            auto [left, right] = dualPivotPartition(arr, low, high);
            dualPivotQuickSort(arr, low, left - 1);
            dualPivotQuickSort(arr, left + 1, right - 1);
            dualPivotQuickSort(arr, right + 1, high);
        }
    }

    // Three-way QuickSort
    static void threeWayQuickSort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            if (high - low < INSERTION_SORT_THRESHOLD) {
                insertionSort(arr, low, high);
                return;
            }
            auto [left, right] = threeWayPartition(arr, low, high);
            threeWayQuickSort(arr, low, left);
            threeWayQuickSort(arr, right, high);
        }
    }

public:
    // Introsort (similar to std::sort)
    static void introsort(std::vector<int>& arr) {
        int depthLimit = 2 * std::log2(arr.size());
        introsortUtil(arr, 0, arr.size() - 1, depthLimit);
    }

    // Dual-pivot QuickSort
    static void dualPivotQuickSort(std::vector<int>& arr) {
        dualPivotQuickSort(arr, 0, arr.size() - 1);
    }

    // Three-way QuickSort
    static void threeWayQuickSort(std::vector<int>& arr) {
        threeWayQuickSort(arr, 0, arr.size() - 1);
    }
};