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

#include "AdjacencyMatrixHeader.h"

// Function to perform scalar addition on an adjacency matrix:
AdjacencyMatrix *scalarAddition(AdjacencyMatrix *matrix, double scalar) {

    // Create a new matrix to store the result
    AdjacencyMatrix *resultMatrix = createMatrix(matrix->rows, matrix->columns);

    // Perform scalar addition
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            resultMatrix->data[i][j] = matrix->data[i][j] + scalar;
        }
    }

    return resultMatrix;
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

// Function to perform scalar subtraction on an adjacency matrix
AdjacencyMatrix *scalarSubtraction(AdjacencyMatrix *matrix, double scalar) {

    // Create a new matrix to store the result
    AdjacencyMatrix *resultMatrix = createMatrix(matrix->rows, matrix->columns);

    // Perform scalar subtraction
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            resultMatrix->data[i][j] = matrix->data[i][j] - scalar;
        }
    }

    return resultMatrix;
}

// Function to perform least squares subtraction of two matrices
AdjacencyMatrix *leastSquaresSubtraction(AdjacencyMatrix *matrix1, AdjacencyMatrix *matrix2) {

    // Check if matrices have the same dimensions
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns) {
        printf("Matrices must have the same dimensions for subtraction\n");
        return NULL;
    }

    // Create a new matrix to store the result
    int rows = matrix1->rows;
    int columns = matrix1->columns;
    AdjacencyMatrix *result = createMatrix(rows, columns);
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Perform least squares subtraction
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            double diff = matrix1->data[i][j] - matrix2->data[i][j];
            result->data[i][j] = diff * diff; // Square the difference
        }
    }

    return result;
}


// Function to perform scalar multiplication on an adjacency matrix
AdjacencyMatrix *scalarMultiplication(AdjacencyMatrix *matrix, double scalar) {
    // Create a new matrix to store the result
    AdjacencyMatrix *resultMatrix = createMatrix(matrix->rows, matrix->columns);

    // Perform scalar multiplication
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            resultMatrix->data[i][j] = matrix->data[i][j] * scalar;
        }
    }

    return resultMatrix;
}

// Function to perform scalar division on an adjacency matrix
AdjacencyMatrix *scalarDivision(AdjacencyMatrix *matrix, double scalar) {
    // Check if scalar is zero
    if (scalar == 0) {
        printf("Division by zero is not allowed\n");
        return NULL;
    }

    // Create a new matrix to store the result
    AdjacencyMatrix *resultMatrix = createMatrix(matrix->rows, matrix->columns);

    // Perform scalar division
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            resultMatrix->data[i][j] = matrix->data[i][j] / scalar;
        }
    }

    return resultMatrix;
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

// Bubble sort algorithm
void bubbleSort(double arr[], int indices[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                // Swap probabilities
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                // Swap indices
                int tempIndex = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tempIndex;
            }
        }
    }
}

// Print top nodes based on probabilities
void printTopNodes(AdjacencyMatrix *probabilitiesVector) {
    int n = probabilitiesVector->rows;
    double *probabilities = malloc(n * sizeof(double));
    int *indices = malloc(n * sizeof(int));

    // Copy probabilities and indices
    for (int i = 0; i < n; i++) {
        probabilities[i] = probabilitiesVector->data[i][0];
        indices[i] = i;
    }

    // Sort probabilities and corresponding indices
    bubbleSort(probabilities, indices, n);

    // Print top nodes
    printf("Top nodes based on probabilities:\n\n");
    for (int i = 0; i < n; i++) {
        if(i < 9){
            printf("#%d.  Node %d: \tProbability %.6f\n", i+1, indices[i], probabilities[i]);
        } else {
            printf("#%d. Node %d: \tProbability %.6f\n", i+1, indices[i], probabilities[i]);
        }
    }

    // Free allocated memory
    free(probabilities);
    free(indices);
}