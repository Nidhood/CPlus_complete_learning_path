#include "MatrixOperationsHeader.h"

// Function to perform addition of two adjacency matrices:
AdjacencyMatrix *addMatrices(AdjacencyMatrix *matrix1, AdjacencyMatrix *matrix2) {

    // Check if matrices have the same dimensions:
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns) {
        printf("Matrices must have the same dimensions for addition\n");
        return NULL;
    }

    // Create a new matrix to store the result
    AdjacencyMatrix *result = createMatrix(matrix1->rows, matrix1->columns);
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Perform addition
    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix1->columns; j++) {
            result->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
        }
    }

    return result;
}

// Function to calculate the sum of all rows and generate a column matrix with the total sum
AdjacencyMatrix* sumRows(AdjacencyMatrix *matrix) {

    // Create a new matrix with 1 column and the same number of rows as the input matrix
    AdjacencyMatrix *sumMatrix = createMatrix(matrix->rows, 1);
    if (sumMatrix == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Calculate the sum of each row and store it in the corresponding position of the sum matrix
    for (int i = 0; i < matrix->rows; i++) {
        double rowSum = 0.0;
        for (int j = 0; j < matrix->columns; j++) {
            rowSum += matrix->data[i][j];
        }
        sumMatrix->data[i][0] = rowSum;
    }

    // Return the sum matrix
    return sumMatrix;
}


// Function to perform subtraction of two adjacency matrices
AdjacencyMatrix *subtractMatrices(AdjacencyMatrix *matrix1, AdjacencyMatrix *matrix2) {
    // Check if matrices have the same dimensions
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns) {
        printf("Matrices must have the same dimensions for subtraction\n");
        return NULL;
    }

    // Create a new matrix to store the result
    AdjacencyMatrix *result = createMatrix(matrix1->rows, matrix1->columns);
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Perform subtraction
    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix1->columns; j++) {
            result->data[i][j] = matrix1->data[i][j] - matrix2->data[i][j];
        }
    }

    return result;
}

// Function to perform scalar multiplication on an adjacency matrix
void scalarMultiplication(AdjacencyMatrix *matrix, int scalar) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            matrix->data[i][j] *= scalar;
        }
    }
}

#include <stdio.h>

// Function to perform scalar division on an adjacency matrix
void scalarDivision(AdjacencyMatrix *matrix, int scalar) {

    // Check if scalar is zero
    if (scalar == 0) {
        printf("Division by zero is not allowed\n");
        return;
    }

    // Perform scalar division
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            matrix->data[i][j] /= scalar;
        }
    }
}




// Function to perform element-wise multiplication (Hadamard product) of two adjacency matrices
AdjacencyMatrix *elementWiseProduct(AdjacencyMatrix *matrix1, AdjacencyMatrix *matrix2) {
    // Check if matrices have the same dimensions
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns) {
        printf("Matrices must have the same dimensions for element-wise multiplication\n");
        return NULL;
    }

    // Create a new matrix to store the result
    AdjacencyMatrix *result = createMatrix(matrix1->rows, matrix1->columns);
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Perform element-wise multiplication
    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix1->columns; j++) {
            result->data[i][j] = matrix1->data[i][j] * matrix2->data[i][j];
        }
    }

    return result;
}

// Function to perform element-wise division (Hadamard division) of two adjacency matrices
AdjacencyMatrix *elementWiseDivision(AdjacencyMatrix *matrix1, AdjacencyMatrix *matrix2) {
    // Check if matrices have the same dimensions
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns) {
        printf("Matrices must have the same dimensions for element-wise division\n");
        return NULL;
    }

    // Create a new matrix to store the result
    AdjacencyMatrix *result = createMatrix(matrix1->rows, matrix1->columns);
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Perform element-wise division
    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix1->columns; j++) {
            // Check for division by zero
            if (matrix2->data[i][j] == 0) {
                printf("Division by zero at index (%d, %d)\n", i, j);
                freeMatrix(result);
                return NULL;
            }
            result->data[i][j] = matrix1->data[i][j] / matrix2->data[i][j];
        }
    }

    return result;
}

// Function to perform matrix multiplication:
AdjacencyMatrix *matrixMultiplication(AdjacencyMatrix *matrix1, AdjacencyMatrix *matrix2) {

    // Check if matrices have compatible dimensions for multiplication1
    if (matrix1->columns != matrix2->rows) {
        printf("Incompatible dimensions for matrix multiplication\n");
        return NULL;
    }

    // Create a new matrix to store the result
    AdjacencyMatrix *result = createMatrix(matrix1->rows, matrix2->columns);
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Perform matrix multiplication
    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix2->columns; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < matrix1->columns; k++) {
                result->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
            }
        }
    }

    return result;
}

// Function to transpose a matrix:
AdjacencyMatrix *transposeMatrix(AdjacencyMatrix *matrix) {

    // Create a new matrix to store the transposed matrix:
    AdjacencyMatrix *transposed = createMatrix(matrix->columns, matrix->rows);
    if (transposed == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Perform matrix transposition:
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            transposed->data[j][i] = matrix->data[i][j];
        }
    }

    return transposed;
}