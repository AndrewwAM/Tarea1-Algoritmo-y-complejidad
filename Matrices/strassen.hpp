#ifndef STRASSEN_HPP
#define STRASSEN_HPP

#include <vector>

using Matrix = std::vector<std::vector<int>>;

// Función para sumar dos matrices
/**
 * @brief Suma dos matrices.
 * 
 * @param A La primera matriz de entrada.
 * @param B La segunda matriz de entrada.
 * @return Matrix La matriz resultante de la suma de A y B.
 */
Matrix sumarMatrices(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Función para restar dos matrices
/**
 * @brief Resta dos matrices.
 * 
 * @param A La primera matriz de entrada.
 * @param B La segunda matriz de entrada.
 * @return Matrix La matriz resultante de la resta de A y B.
 */
Matrix restarMatrices(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Implementación del algoritmo de Strassen
/**
 * @brief Implementa el algoritmo de Strassen para multiplicar dos matrices.
 * 
 * @param A La primera matriz de entrada.
 * @param B La segunda matriz de entrada.
 * @return Matrix La matriz resultante de la multiplicación de A y B usando el algoritmo de Strassen.
 */
Matrix strassenMultiplicar(const Matrix& A, const Matrix& B) {
    int n = A.size();
    
    // Caso base: matriz de 1x1
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }
    
    // Dividir las matrices en submatrices
    int mitad = n / 2;
    Matrix A11(mitad, std::vector<int>(mitad));
    Matrix A12(mitad, std::vector<int>(mitad));
    Matrix A21(mitad, std::vector<int>(mitad));
    Matrix A22(mitad, std::vector<int>(mitad));
    Matrix B11(mitad, std::vector<int>(mitad));
    Matrix B12(mitad, std::vector<int>(mitad));
    Matrix B21(mitad, std::vector<int>(mitad));
    Matrix B22(mitad, std::vector<int>(mitad));

    // Llenar las submatrices
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mitad];
            A21[i][j] = A[i + mitad][j];
            A22[i][j] = A[i + mitad][j + mitad];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mitad];
            B21[i][j] = B[i + mitad][j];
            B22[i][j] = B[i + mitad][j + mitad];
        }
    }

    // Calcular los productos de Strassen
    Matrix M1 = strassenMultiplicar(sumarMatrices(A11, A22), sumarMatrices(B11, B22));
    Matrix M2 = strassenMultiplicar(sumarMatrices(A21, A22), B11);
    Matrix M3 = strassenMultiplicar(A11, restarMatrices(B12, B22));
    Matrix M4 = strassenMultiplicar(A22, restarMatrices(B21, B11));
    Matrix M5 = strassenMultiplicar(sumarMatrices(A11, A12), B22);
    Matrix M6 = strassenMultiplicar(restarMatrices(A21, A11), sumarMatrices(B11, B12));
    Matrix M7 = strassenMultiplicar(restarMatrices(A12, A22), sumarMatrices(B21, B22));

    // Calcular las submatrices de la matriz resultante
    Matrix C11 = sumarMatrices(restarMatrices(sumarMatrices(M1, M4), M5), M7);
    Matrix C12 = sumarMatrices(M3, M5);
    Matrix C21 = sumarMatrices(M2, M4);
    Matrix C22 = sumarMatrices(restarMatrices(sumarMatrices(M1, M3), M2), M6);

    // Combinar las submatrices en la matriz resultante
    Matrix C(n, std::vector<int>(n));
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mitad] = C12[i][j];
            C[i + mitad][j] = C21[i][j];
            C[i + mitad][j + mitad] = C22[i][j];
        }
    }

    return C;
}

#endif // STRASSEN_HPP