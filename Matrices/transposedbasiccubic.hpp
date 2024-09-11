#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

/**
 * @brief Transpone una matriz cuadrada de enteros.
 * 
 * @param mat La matriz de entrada.
 * @return Matrix La matriz transpuesta.
 */
Matrix transpose(const Matrix& mat) {
    int n = mat.size();
    Matrix transposed(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transposed[j][i] = mat[i][j];
        }
    }
    return transposed;
}

/**
 * @brief Multiplica dos matrices cuadradas de enteros utilizando la transposición de la segunda matriz.
 * 
 * @param A La primera matriz de entrada.
 * @param B La segunda matriz de entrada.
 * @return Matrix La matriz resultante de la multiplicación de A y B.
 */
Matrix multiplyMatricesWithTranspose(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix B_transposed = transpose(B);
    Matrix C(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; i++) {          // Recorre filas de A
        for (int j = 0; j < n; j++) {      // Recorre columnas de B
            for (int k = 0; k < n; k++) {  // Realiza la multiplicación y suma
                C[i][j] += A[i][k] * B_transposed[j][k];
            }
        }
    }

    return C;
}