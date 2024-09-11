#include <vector>

// Definimos un alias para una matriz de enteros
using Matrix = std::vector<std::vector<int>>;

/**
 * @brief Multiplica dos matrices cuadradas de enteros.
 * 
 * @param A La primera matriz de entrada.
 * @param B La segunda matriz de entrada.
 * @return Matrix La matriz resultante de la multiplicación de A y B.
 */
Matrix multiplyMatricesBasic(const Matrix& A, const Matrix& B) {
    // Calculamos la dimensión de las matrices (n x n)
    int n = A.size();
    
    // Inicializamos la matriz C con ceros (n x n)
    Matrix C(n, std::vector<int>(n, 0));

    // Tres bucles anidados para la multiplicación
    for (int i = 0; i < n; i++) {          // Recorre filas de A
        for (int j = 0; j < n; j++) {      // Recorre columnas de B
            for (int k = 0; k < n; k++) {  // Realiza la multiplicación y suma
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return C;
}