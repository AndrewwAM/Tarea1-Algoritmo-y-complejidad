#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

using Matrix = std::vector<std::vector<int>>;

// Basic cubic algorithm for matrix multiplication
Matrix basicMultiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}


// Helper functions for Strassen's algorithm
Matrix addMatrix(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix subtractMatrix(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

Matrix strassenMultiplyRecursive(const Matrix& A, const Matrix& B) {
    int n = A.size();

    /* OPTIMIZACION OPCIONAL
    if (n <= 64) {  // Base case: use standard multiplication for small matrices
        return basicMultiply(A, B);
    }
    */
    int k = n / 2;

    // Divide matrices into submatrices
    Matrix A11(k, std::vector<int>(k)), A12(k, std::vector<int>(k)),
           A21(k, std::vector<int>(k)), A22(k, std::vector<int>(k));
    Matrix B11(k, std::vector<int>(k)), B12(k, std::vector<int>(k)),
           B21(k, std::vector<int>(k)), B22(k, std::vector<int>(k));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Recursive steps
    Matrix M1 = strassenMultiplyRecursive(addMatrix(A11, A22), addMatrix(B11, B22));
    Matrix M2 = strassenMultiplyRecursive(addMatrix(A21, A22), B11);
    Matrix M3 = strassenMultiplyRecursive(A11, subtractMatrix(B12, B22));
    Matrix M4 = strassenMultiplyRecursive(A22, subtractMatrix(B21, B11));
    Matrix M5 = strassenMultiplyRecursive(addMatrix(A11, A12), B22);
    Matrix M6 = strassenMultiplyRecursive(subtractMatrix(A21, A11), addMatrix(B11, B12));
    Matrix M7 = strassenMultiplyRecursive(subtractMatrix(A12, A22), addMatrix(B21, B22));

    Matrix C11 = addMatrix(subtractMatrix(addMatrix(M1, M4), M5), M7);
    Matrix C12 = addMatrix(M3, M5);
    Matrix C21 = addMatrix(M2, M4);
    Matrix C22 = addMatrix(subtractMatrix(addMatrix(M1, M3), M2), M6);

    // Combine results
    Matrix C(n, std::vector<int>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    return C;
}

// Wrapper function for Strassen's algorithm
Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
    return strassenMultiplyRecursive(A, B);
}