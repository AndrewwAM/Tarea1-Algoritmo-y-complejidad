#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>


using namespace std;
chrono::time_point<chrono::high_resolution_clock> start;

void bubbleSort(vector<int> arr, int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }
}

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


void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back 
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], 
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], 
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);


    /*
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double, std::micro> duration = stop - start;
    long double time = duration.count();
    cout << "Tiempo transcurrido: " << time << " microsegundos\r";
    cout.flush(); */
}


int partition(vector<int>& arr, int low, int high) {
  
    // Choose the pivot
    int pivot = arr[(high-low)/2];
  
    // Index of smaller element and indicates 
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[;ow..high] and move all smaller
    // elements on left side. Elements from low to 
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    // Move pivot after smaller elements and
    // return its position
    swap(arr[i + 1], arr[high]);  
    return i + 1;
}

// The QuickSort function implementation
void quickSort(vector<int>& arr, int low, int high) {
  
    if (low < high) {
      
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Función para mostrar un temporizador en la consola
void mostrarTemporizador(std::atomic<bool>& ejecutando) {
    int segundos = 0;
    while (ejecutando) {
        std::cout << "\rTiempo transcurrido: " << segundos << " segundos";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        segundos++;
    }
    std::cout << std::endl; // Imprime un salto de línea cuando el temporizador termina
}


// Funciones auxiliares para la lectura y escritura de archivo
vector<int> filetovector(ifstream& file){
    int line;
    vector<int> output;
    while(!file.eof()){
        file >> line;
        output.push_back(line);
    }
    return output;
}

void pidieronOutput(ofstream& file, vector<int> arr){
    int num, i = 0;
    for(const auto& num : arr){
        file << num << endl;
        progressBar(arr.size(), ++i);
    }
}

void writeTimeStats(string path, long double time, string algorithm, string datatype, string numCases){
    ofstream file(path, ios::app);
    if (!file.is_open()){
        cerr << "No se pudo abrir el archivo: " << path << endl;
        return;
    }
    string line = "Algorithm: " + algorithm + " | Dataset: " + datatype + " | Size: " + numCases + " | Time: " + to_string(time) + " microsegundos | " + to_string(time/1000000) + " segundos";
    file << line << endl;
    file.close();
}

// Función para mostrar un temporizador en la consola
void mostrarTemporizador(std::atomic<bool>& ejecutando) {
    int segundos = 0;
    while (ejecutando) {
        std::cout << "\rTiempo transcurrido: " << segundos << " segundos";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        segundos++;
    }
    std::cout << std::endl; // Imprime un salto de línea cuando el temporizador termina
}




int main()
{
    std::atomic<bool> ejecutando(true);
    bool w_output = true;
    bool w_excec_time = true;
    string in_path = "datasets/dataset_";
    string out_path = "outputDataset/out_dataset_";
    string time_path = "./timeStats.txt";
    vector<string> numCases = {"100", "1000", "10000", "100000", "1000000", "10000000", "100000000"};
    vector<string> algorithms = {"bubblesort", "selectionsort", "mergesort", "quicksort", "c++ std::sort"};
    vector<string> datatypes = {"partially_ordered", "reverse", "random", "repeated"};

    int choice;
    std::cout << ">>>> Seleccione un algoritmo:\n(0) bubblesort\n(1) selectionsort\n(2) mergesort\n(3) quicksort\n(4) c++ std::sort()\n> ";
    cin >> choice;

    int datatype;
    std::cout << ">>>> Seleccione tipo de dataset:\n(0) partially_ordered\n(1) reverse\n(2) random\n(3) repeated\n> ";
    cin >> datatype;

    int topcap;
    std::cout << ">>>> Mayor potencia de 10 a evaluar: (2-8)\n> ";
    cin >> topcap;

    if (topcap > 5){
        std::cout << "<!> Advertencia <!>" << endl;
        std::cout << "No se recomienda evaluar potencias mayores a 10^5 con el modo de escritura (output) activado" << endl;
        std::cout << "ya que el tiempo de ejecucion aumenta considerablemente." << endl;
        string response;
        std::cout << "Desea conservar el modo escritura? (y/n)\n> ";
        cin >> response;
        if (response == "n"){
            w_output = false;
        }
    }


    int tests = 5;

    int i = 2;

    std::cout << "\n######################################\n" << "Algoritmo: " << algorithms[choice] << endl;
    std::cout << "Dataset: " << datatypes[datatype] << endl;
    std::cout << "Modo escritura: " << ((w_output) ? "yes" : "no") << "\n######################################" << endl;

    while(i <= topcap){
        
        string filepath = in_path + datatypes[datatype] + "_" + numCases[i-2] + ".txt";
        string outputPath = out_path + datatypes[datatype] + "_" + numCases[i-2] + ".txt";

        ifstream file(filepath);
        if (!file.is_open()){
            cerr << "No se pudo abrir el archivo: " << filepath << endl;
            return -1;
        }

        vector<int> arr = filetovector(file);
        file.close();
        int N = arr.size();
        int j = 0;
        long double total = 0;
        std::cout << ">>>> Input: " << filepath.substr(9,filepath.size()-1) << endl; 

        while(j <= tests){
            start = chrono::high_resolution_clock::now();


            switch (choice)
            {
            case 0:

                bubbleSort(arr, N);
                break;
            
            case 1:
                selectionSort(arr, N);
                break;
            
            case 2:
                mergeSort(arr, 0, N);
                break;
            
            case 3:
                quickSort(arr, 0, N);
                break;

            case 4:
                std::sort(arr.begin(), arr.end());
                break;
            
            default:
                std::sort(arr.begin(), arr.end());
                break;
            }
        
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double, std::micro> duration = end - start;
            long double time = duration.count();



            
            if (j != 0) total += time;

            std::cout << "Caso: " << j << " | ";   
            std::cout << "Tiempo de ejecucion: " << time << " microsegundos / ";
            std::cout << time/1000000 << " segundos";
            (j == 0) ? std::cout << " (cache)" << endl : std::cout << endl;


            j++;
        }

        if (w_output){
            cout << "\n>escribiendo..." << endl;
            ofstream file(outputPath);

            if (!file.is_open()){
                cerr << "<!> no se pudo escribir en: " << outputPath << endl;
            }
            pidieronOutput(file, arr);
            std::cout << "\n>Output: " << outputPath << endl;

            file.close();
        }
        total = (tests == 1) ?  total/tests :  total/(tests);
        std::cout << "\n>Tiempo promedio de ejecucion: " << total << " microsegundos / ";
        std::cout << (total/1000000) << " segundos.\n" << endl;

        if (w_excec_time){
            writeTimeStats(time_path, total, algorithms[choice], datatypes[datatype], numCases[i-2]);
        }
        i++;
    }
    if (w_excec_time){
        std::cout << "Estadisticas de tiempo guardadas en: " << time_path << endl;
    }

    return 0;
}
