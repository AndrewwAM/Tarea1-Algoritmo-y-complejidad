#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>

#include "bubblesort.hpp"
#include "selectionsort.hpp"
#include "mergesort.hpp"
#include "quicksort.hpp"
#include "utilities.hpp"


using namespace std;

bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            return false; // El arreglo no está ordenado
        }
    }
    return true; // El arreglo está ordenado
}

int main()
{
    chrono::time_point<chrono::high_resolution_clock> start;
    std::atomic<bool> ejecutando(true);
    bool w_output = false; // Si escribe el arreglo ordenado en archivos de salida [default = true]
    bool w_excec_time = true; // Si escribe los tiempos promedio de la ejecucion en un archivo log [default = true] 
    int tests = 5; // Cantidad de casos de prueba ademas del caso 0
    long double time;
    string linea;
    /* 
    <!> IMPORTANTE <!>
    Crear las carpetas "datasets" y "outputDataset" en caso de que no existan previamente,
    compilar y utilizar "main.cpp" para generar los datasets en el formato que recibe este código 
    */
    string in_path = "datasets/dataset_";
    string out_path = "outputDataset/out_dataset_";
    string time_path = "./timeStats.txt";
    vector<string> numCases = {"100", "1000", "10000", "100000", "1000000", "10000000", "100000000"};
    vector<string> algorithms = {"selectionsort", "mergesort", "quicksort", "c++ std::sort"};
    vector<string> datatypes = {"ordered", "reverse", "semi_ordered" , "random"};



    int choice;
    std::cout << ">>>> Seleccione un algoritmo:\n(0) selectionsort\n(1) mergesort\n(2) quicksort\n(3) c++ std::sort()\n> ";
    cin >> choice;

    int datatype;
    std::cout << ">>>> Seleccione tipo de dataset:\n(0) ordered\n(1) reverse\n(2) semi_ordered\n(3) random\n> ";
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

        std::cout << "Leyendo...";
        vector<int> original = filetovector(file);
        std::cout << "\r";
        vector<int> arr;
        file.close();
        int N = original.size();
        int j = 0;
        long double total = 0;
        std::cout << ">>>> Input: " << filepath.substr(9,filepath.size()-1) << endl; 

        while(j <= tests){
            ejecutando = true;
            chrono::duration<double, std::micro> duration;
            
            arr = original;
            //(isSorted(arr)) ? cout<< "\nestá ordenado ["+to_string(arr.size())+"]\n": cout << "\nmal\n";
            std::thread hiloTemporizador(mostrarTemporizador, std::ref(ejecutando));

            std::thread hiloAlgoritmo([&ejecutando, &arr, N, choice, &duration, &time, &start]() {
                start = chrono::high_resolution_clock::now();
                switch (choice)
                {               
                case 0:
                    selectionSort(arr, N);
                    break;
                
                case 1:
                    mergeSort(arr, 0, N);
                    break;
                
                case 2:
                    quickSort(arr, 0, N);
                    break;

                case 3:
                    std::sort(arr.begin(), arr.end());
                    break;
                
                default:
                    // FIXME poner bogo (utilities)
                    std::sort(arr.begin(), arr.end());
                    break;
                }
                auto end = chrono::high_resolution_clock::now();
                duration = end - start;
                time = duration.count();
                ejecutando = false;
            });

            hiloAlgoritmo.join();
            hiloTemporizador.join();
            cout << "\r";
            
            if (j != 0) total += time;

            string linea = "Caso: " + to_string(j) + " | " + "Tiempo de ejecucion: " + to_string(time) + " microsegundos / " + to_string(time/1000000) + " segundos" + ((j == 0) ? " (cache)\t\n" : "\t\n");
            std::cout << linea;
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

        total = (tests == 1) ?  total/tests :  total/(tests); // FIXME ?? xddd

        linea = "\n>Tiempo promedio de ejecucion: " + to_string(total) + " microsegundos / " + to_string(total/1000000) + " segundos.\n\n";
        std::cout << linea;

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
