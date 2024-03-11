#include "../include/MatrixOperationsHeader.h"

// Function to perform addition of two adjacency matrices:
TransitionMatrix *addMatrices(TransitionMatrix *matrix1, TransitionMatrix *matrix2) {

    // Check if matrices have the same dimensions:
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns) {
        printf("Matrices must have the same dimensions for addition\n");
        return NULL;
    }

    // Create a new matrix to store the result
    TransitionMatrix *result = createMatrix(matrix1->rows, matrix1->columns);
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
TransitionMatrix* sumRows(TransitionMatrix *matrix) {

    // Create a new matrix with 1 column and the same number of rows as the input matrix
    TransitionMatrix *sumMatrix = createMatrix(matrix->rows, 1);
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

// Function to perform scalar addition on an adjacency matrix:
TransitionMatrix *scalarAddition(TransitionMatrix *matrix, double scalar) {

    // Create a new matrix to store the result
    TransitionMatrix *resultMatrix = createMatrix(matrix->rows, matrix->columns);

    // Perform scalar addition
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            resultMatrix->data[i][j] = matrix->data[i][j] + scalar;
        }
    }

    return resultMatrix;
}

// Function to perform subtraction of two adjacency matrices
TransitionMatrix *subtractMatrices(TransitionMatrix *matrix1, TransitionMatrix *matrix2) {
    // Check if matrices have the same dimensions
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns) {
        printf("Matrices must have the same dimensions for subtraction\n");
        return NULL;
    }

    // Create a new matrix to store the result
    TransitionMatrix *result = createMatrix(matrix1->rows, matrix1->columns);
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
TransitionMatrix *scalarSubtraction(TransitionMatrix *matrix, double scalar) {

    // Create a new matrix to store the result
    TransitionMatrix *resultMatrix = createMatrix(matrix->rows, matrix->columns);

    // Perform scalar subtraction
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            resultMatrix->data[i][j] = matrix->data[i][j] - scalar;
        }
    }

    return resultMatrix;
}

// Function to perform least squares subtraction of two matrices
TransitionMatrix *leastSquaresSubtraction(TransitionMatrix *matrix1, TransitionMatrix *matrix2) {

    // Check if matrices have the same dimensions
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns) {
        printf("Matrices must have the same dimensions for subtraction\n");
        return NULL;
    }

    // Create a new matrix to store the result
    int rows = matrix1->rows;
    int columns = matrix1->columns;
    TransitionMatrix *result = createMatrix(rows, columns);
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
TransitionMatrix *scalarMultiplication(TransitionMatrix *matrix, double scalar) {
    // Create a new matrix to store the result
    TransitionMatrix *resultMatrix = createMatrix(matrix->rows, matrix->columns);

    // Perform scalar multiplication
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            resultMatrix->data[i][j] = matrix->data[i][j] * scalar;
        }
    }

    return resultMatrix;
}

// Function to perform scalar division on an adjacency matrix
TransitionMatrix *scalarDivision(TransitionMatrix *matrix, double scalar) {
    // Check if scalar is zero
    if (scalar == 0) {
        printf("Division by zero is not allowed\n");
        return NULL;
    }

    // Create a new matrix to store the result
    TransitionMatrix *resultMatrix = createMatrix(matrix->rows, matrix->columns);

    // Perform scalar division
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            resultMatrix->data[i][j] = matrix->data[i][j] / scalar;
        }
    }

    return resultMatrix;
}

// Function to perform element-wise multiplication (Hadamard product) of two adjacency matrices
TransitionMatrix *elementWiseProduct(TransitionMatrix *matrix1, TransitionMatrix *matrix2) {
    // Check if matrices have the same dimensions
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns) {
        printf("Matrices must have the same dimensions for element-wise multiplication\n");
        return NULL;
    }

    // Create a new matrix to store the result
    TransitionMatrix *result = createMatrix(matrix1->rows, matrix1->columns);
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
TransitionMatrix *elementWiseDivision(TransitionMatrix *matrix1, TransitionMatrix *matrix2) {
    // Check if matrices have the same dimensions
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns) {
        printf("Matrices must have the same dimensions for element-wise division\n");
        return NULL;
    }

    // Create a new matrix to store the result
    TransitionMatrix *result = createMatrix(matrix1->rows, matrix1->columns);
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
TransitionMatrix *matrixMultiplication(TransitionMatrix *matrix1, TransitionMatrix *matrix2) {

    // Check if matrices have compatible dimensions for multiplication1
    if (matrix1->columns != matrix2->rows) {
        printf("Incompatible dimensions for matrix multiplication\n");
        return NULL;
    }

    // Create a new matrix to store the result
    TransitionMatrix *result = createMatrix(matrix1->rows, matrix2->columns);
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
TransitionMatrix *transposeMatrix(TransitionMatrix *matrix) {

    // Create a new matrix to store the transposed matrix:
    TransitionMatrix *transposed = createMatrix(matrix->columns, matrix->rows);
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

// Print top nodes based on probabilities of the students:
void printTopNodesStudents(TransitionMatrix *probabilitiesVector, NumberName *numberName) {
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
            printf("#%d.  Node #%d: \tProbability %.6f\n", i+1, indices[i], probabilities[i]);
        } else {
            printf("#%d. Node #%d: \tProbability %.6f\n", i+1, indices[i], probabilities[i]);
        }
    }

    // Free allocated memory
    free(probabilities);
    free(indices);
}

// Print top nodes based on probabilities
void printTopNodesPapers(TransitionMatrix *probabilitiesVector, NumberName *numberName) {
    int n = probabilitiesVector->rows;
    int counter = 1;
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
        if(numberName->papers[indices[i]]->paperNumber < 178){
            if(i < 9){
                printf("#%d. %s (Node #%d): \tProbability %.6f\n", counter++, numberName->papers[indices[i]]->paperName, numberName->papers[indices[i]]->paperNumber, probabilities[i]);
            } else if(i < 99){
                printf("#%d.  %s (Node #%d): \tProbability %.6f\n", counter++, numberName->papers[indices[i]]->paperName, numberName->papers[indices[i]]->paperNumber, probabilities[i]);
            } else {
                printf("#%d.   %s (Node #%d): \tProbability %.6f\n", counter++, numberName->papers[indices[i]]->paperName, numberName->papers[indices[i]]->paperNumber, probabilities[i]);
            }
        }
    }

    // Free allocated memory
    free(probabilities);
    free(indices);
}

// Proof the file if it is a graph or a matrix (using regex to check the word "graph" or "matrix" in the txt):
bool isGraphFile(const char *filename) {
    if (filename == NULL)
        return false;

    // Compile regular expression
    regex_t regex;
    int ret = regcomp(&regex, "graph", REG_EXTENDED | REG_ICASE);
    if (ret != 0) {
        printf("Error compiling regex\n");
        return false;
    }

    // Execute regular expression
    ret = regexec(&regex, filename, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return true; // Match found
    } else if (ret == REG_NOMATCH) {
        return false; // No match found
    } else {
        printf("Error executing regex\n");
        return false;
    }
}
