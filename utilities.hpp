#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <iomanip>

#include "barra.hpp"
using namespace std;

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


void pidieronOutput(ofstream& file, vector<int> arr){
    int num, i = 0;
    for(const auto& num : arr){
        file << num << endl;
        progressBar(arr.size(), ++i);
    }
    file << endl;
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