#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <iomanip>

using namespace std;

//writes a progress bar to the console
void progressBar(int max, int progress, int barWidth = 70) {
    float percentage = (float)progress / max;
    int pos = barWidth * percentage;

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(percentage * 100.0) << " %\r";
    std::cout.flush();
}


void timeFormat(int seg){
    // Calcular las horas, minutos y segundos
    int horas = seg / 3600;
    int minutos = (seg % 3600) / 60;
    int segundos_restantes = seg % 60;

    // Mostrar el resultado en formato 00h:00m:00s
    std::cout << "\rTiempo transcurrido: "
              << std::setw(2) << std::setfill('0') << horas << "h:"
              << std::setw(2) << std::setfill('0') << minutos << "m:"
              << std::setw(2) << std::setfill('0') << segundos_restantes << "s";
}

// Función para mostrar un temporizador en la consola
void mostrarTemporizador(std::atomic<bool>& ejecutando) {
    float delay = 1;
    auto tiempo_inicio = chrono::high_resolution_clock::now();

    while (ejecutando) {
        // Tiempo actual
        auto tiempo_actual = chrono::high_resolution_clock::now();

        // Calcula la diferencia entre el tiempo actual y el tiempo de inicio
        auto tiempo_transcurrido = chrono::duration_cast<chrono::seconds>(tiempo_actual - tiempo_inicio).count();

        // Verifica si ha pasado la duración deseada
        if (tiempo_transcurrido >= delay) {
            break;
        }
    }
    int segundos = 1;
    while (ejecutando) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        timeFormat(++segundos);
        std::cout.flush();
    }

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



// Function to write the matrix to a text file
void writeMatrixToFile(const std::vector<std::vector<int>>& matrix, const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        cout << "Writing...\n";
        for (const auto& row : matrix) {
            for (const auto& element : row) {
                file << std::setw(8) << element;  // Set width for alignment
            }
            file << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }
}



void writeTimeStats(string path, long double time, string algorithm, int dimA, int dimB, string numCases){
    ofstream file(path, ios::app);
    if (!file.is_open()){
        cerr << "No se pudo abrir el archivo: " << path << endl;
        return;
    }
    string line = "Algoritmo: " + algorithm + " | Dimension: " + to_string(dimA) + "x" + to_string(dimA) + " | Time: " + to_string(time) + " microsegundos | " + to_string(time/1000000) + " segundos";
    file << line << endl;
    file.close();
}