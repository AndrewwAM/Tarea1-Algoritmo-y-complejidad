#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <math.h>

#include "strassen.hpp"
#include "utilities.hpp"
#include "basiccubic.hpp"

using Matrix = std::vector<std::vector<int>>;

// Function to generate a random matrix
Matrix generateMatrix(int rows, int cols) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    Matrix matrix(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

// Función para imprimir una matriz
void printMatrix(const Matrix& mat) {
    for (const auto& row : mat) {
        for (int elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Function to measure execution time
template<typename Func>
long long measureTime(Func func, Matrix& c) {
    auto start = std::chrono::high_resolution_clock::now();
    c = func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}


int main()
{
    chrono::time_point<chrono::high_resolution_clock> start;
    std::atomic<bool> ejecutando(true);
    bool w_output = true; // Si escribe el arreglo ordenado en archivos de salida [default = true]
    bool w_excec_time = true; // Si escribe los tiempos promedio de la ejecucion en un archivo log [default = true] 
    int tests = 3; // Cantidad de casos de prueba ademas del caso 0
    long double totalTime = 0;
    string linea;
    /* 
    <!> IMPORTANTE <!>
    Crear las carpetas "datasets" y "outputDataset" en caso de que no existan previamente,
    compilar y utilizar "main.cpp" para generar los datasets en el formato que recibe este código 
    */
    string out_path = "./outputMatrix";
    string time_path = "./matrixTimeStats.txt";
    vector<int> numCases = {64, 128, 256, 512, 1024, 2048, 4096};
    vector<string> algorithms = {"Basica", "Basica Optimizada","Strassen"};

    int topcap;


    int choice;
    std::cout << "Seleccione el algoritmo:\n(0) multiplicacion basica | (1) basica optimizada (2) para Strassen\n>";
    cin >> choice;

    int n;
    std::cout << "Ingresa la dimensión (2^n) de la matriz\n64 (n=6) 64 (n=6) | 128 (n=7) | 256 (n=8) | 512 (n=9) | 1024 (n=10) | 2048 (n=11) | 4096 (n=12)\nn: ";
    std::cin >> n;
    topcap = n;
    if (std::binary_search(numCases.begin(), numCases.end(), n)) {
        std::cout << "Error: Eleccion invalida." << std::endl;
        return 1;
    }


    if (w_output){

        string response;
        std::cout << "Desea conservar el modo escritura? (y/n)\n> ";
        cin >> response;
        if (response == "n"){
            w_output = false;
        }
    }

    
    int lowgap = 6;
    int i = 6;
    Matrix C;

    std::cout << "\n######################################\n" << "Algoritmo: " << algorithms[choice] << endl;
    std::cout << "Dimensiones de matriz: " << pow(2,n) << "x" << pow(2,n) << endl;

    
    std::cout << "Modo escritura: " << ((w_output) ? "yes" : "no") << "\n######################################" << endl;

    while(i <= topcap){
        int j = 0;
        
        string outputPath = out_path + "_" + to_string(numCases[i-lowgap]) + ".txt";
        int dimA, dimB;
        Matrix A, B;


        dimA = pow(2,i);
        dimB = pow(2,i);
        A = generateMatrix(dimA, dimB);
        B = generateMatrix(dimA, dimB);

        long double duration;

        while(j <= tests){
            ejecutando = true;
            
            std::thread hiloTemporizador(mostrarTemporizador, std::ref(ejecutando));

            std::thread hiloAlgoritmo([&ejecutando, &A, &B, choice, &duration, &C]() {
                
                switch (choice)
                {
                case 1:
                    duration = measureTime([&]() { return strassenMultiply(A, B); }, C);
                    break;
                default:
                    duration = measureTime([&A, &B, &C]() {return multiplyMatricesBasic(A, B);}, C);
                    break;
                }
                ejecutando = false;
            });

            hiloAlgoritmo.join();
            hiloTemporizador.join();
            printMatrix(C);
            cout << "\r";
            
            if (j != 0) totalTime += duration;

            string linea = "Caso: " + to_string(j) + " | " + "Tiempo de ejecucion: " + to_string(duration) + " microsegundos / " + to_string(duration/1000000) + " segundos" + ((j == 0) ? " (cache)\t\n" : "\t\n");
            std::cout << linea;
            j++;
        }

        
        if (w_output){
            cout << "\n>escribiendo..." << endl;
            ofstream file(outputPath);

            if (!file.is_open()){
                cerr << "<!> no se pudo escribir en: " << outputPath << endl;
            }
            writeMatrixToFile(C, out_path);
            std::cout << "\n>Output: " << outputPath << endl;

            file.close();
        }
        
        totalTime = totalTime/tests;

        linea = "\n>Tiempo promedio de ejecucion: " + to_string(totalTime) + " microsegundos / " + to_string(totalTime/1000000) + " segundos.\n\n";
        std::cout << linea;

        if (w_excec_time){
            writeTimeStats(time_path, totalTime, algorithms[choice], dimA, dimB, to_string(numCases[i-lowgap]));
        }
        i++;
    }
    if (w_excec_time){
        std::cout << "Estadisticas de tiempo guardadas en: " << time_path << endl;
    }

    return 0;
}