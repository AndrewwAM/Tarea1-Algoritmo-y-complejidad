#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <iomanip>

using namespace std;

/**
 * @brief Escribe una barra de progreso en la consola.
 * 
 * @param max El valor máximo de progreso.
 * @param progress El progreso actual.
 * @param barWidth El ancho de la barra de progreso (por defecto es 70).
 */
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

/**
 * @brief Convierte segundos en un formato de tiempo legible.
 * 
 * @param seg El tiempo en segundos.
 */
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

/**
 * @brief Función para mostrar un temporizador en la consola.
 * 
 * @param ejecutando Variable atómica que controla la ejecución del temporizador.
 */
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

/**
 * @brief Convierte el contenido de un archivo en un vector de enteros.
 * 
 * @param file El archivo de entrada.
 * @return vector<int> El vector de enteros resultante.
 */
vector<int> filetovector(ifstream& file){
    int line;
    vector<int> output;
    while(!file.eof()){
        file >> line;
        output.push_back(line);
    }
    return output;
}

/**
 * @brief Escribe un vector de enteros en un archivo y muestra una barra de progreso.
 * 
 * @param file El archivo de salida.
 * @param arr El vector de enteros a escribir.
 */
void pidieronOutput(ofstream& file, vector<int> arr){
    int num, i = 0;
    for(const auto& num : arr){
        file << num << endl;
        progressBar(arr.size(), ++i);
    }
    file << endl;
}

/**
 * @brief Escribe estadísticas de tiempo en un archivo.
 * 
 * @param path La ruta del archivo de salida.
 * @param time El tiempo de ejecución.
 * @param algorithm El nombre del algoritmo.
 * @param datatype El tipo de datos.
 * @param numCases El número de casos.
 */
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