#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <numeric> // Para std::iota

/**
 * @brief Genera un dataset de enteros basado en el tipo de orden especificado.
 * 
 * @param size El tamaño del dataset.
 * @param order_type El tipo de orden del dataset (ordered, reverse, semi_ordered, partially_ordered, random).
 * @param ordered_percentage El porcentaje de elementos ordenados si se elige parcialmente/semi ordenado.
 * @return std::vector<int> El dataset generado.
 */
std::vector<int> generate_dataset(int size, const std::string& order_type, int ordered_percentage = 50) {
    std::vector<int> dataset;
    std::random_device rd;
    std::mt19937 g(rd());

    if (order_type == "ordered") {
        // Dataset en orden ascendente
        dataset.resize(size);
        std::iota(dataset.begin(), dataset.end(), 1); // Llenar de 1 a size

    } else if (order_type == "reverse") {
        // Dataset en orden descendente
        dataset.resize(size);
        std::iota(dataset.rbegin(), dataset.rend(), 1); // Llenar en orden inverso

    } else if (order_type == "semi_ordered") {
        // Semi ordenado: una pequeña parte está ordenada
        int ordered_size = size * ordered_percentage / 100;
        std::vector<int> ordered_part(ordered_size);
        std::vector<int> random_part(size - ordered_size);

        std::iota(ordered_part.begin(), ordered_part.end(), 1);
        std::generate(random_part.begin(), random_part.end(), [&g]() { return g() % 10000; });
        dataset.insert(dataset.end(), ordered_part.begin(), ordered_part.end());
        dataset.insert(dataset.end(), random_part.begin(), random_part.end());

    } else if (order_type == "partially_ordered") {
        // Parcialmente ordenado
        int ordered_size = size * ordered_percentage / 100;
        std::vector<int> ordered_part(ordered_size);
        std::vector<int> random_part(size - ordered_size);

        std::iota(ordered_part.begin(), ordered_part.end(), 1);
        std::iota(random_part.begin(), random_part.end(), ordered_size + 1);
        std::shuffle(random_part.begin(), random_part.end(), g);

        dataset.insert(dataset.end(), ordered_part.begin(), ordered_part.end());
        dataset.insert(dataset.end(), random_part.begin(), random_part.end());

    } else if (order_type == "random") {
        // Desordenado: completamente aleatorio
        dataset.resize(size);
        std::iota(dataset.begin(), dataset.end(), 1);
        std::shuffle(dataset.begin(), dataset.end(), g);

    } else {
        std::cerr << "Invalid order type specified." << std::endl;
        return {};
    }

    return dataset;
}

/**
 * @brief Guarda un dataset en un archivo.
 * 
 * @param dataset El dataset a guardar.
 * @param filename El nombre del archivo de salida.
 */
void save_dataset(const std::vector<int>& dataset, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const int& item : dataset) {
            file << item << "\n";
        }
        std::cout << "Dataset saved to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
}

int main() {
    bool autom = true;
    // Configuración
    int size = 8;  // Tamaño del dataset
    std::string order_type;  // Tipo de orden
    int ordered_percentage = 50;  // Porcentaje de elementos ordenados si se elige parcialmente/semi ordenado
    std::vector<std::string> opciones = {"ordered", "reverse", "semi_ordered", "partially_ordered", "random"};
    if (!autom){
        std::cout << "Potencia de 10 del dataset (2-8)\n> ";
        std::cin >> size;
        std::cout << "Tipo de orden, Opciones: ordered, reverse, semi_ordered, partially_ordered, random\n> ";
        std::cin >> order_type;
    }

    for (std::string opcion: opciones){
        if (autom) order_type = opcion;

        for (int num = 2; num <= size && num < 9; ++num) {
            int top = std::pow(10, num);
            // Genera el dataset
            std::vector<int> dataset = generate_dataset(top, order_type, ordered_percentage);

            // Ajusta el nombre del archivo dinámicamente
            std::string filename = "datasets/dataset_" + order_type + "_" + std::to_string(top) + ".txt";

            // Guarda el dataset en el archivo
            if (!dataset.empty()) {
                save_dataset(dataset, filename);
            }
        }
        if (!autom) break;
    }

    return 0;
}