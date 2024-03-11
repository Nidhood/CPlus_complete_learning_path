#include "../include/AdjacencyMatrixHeader.h"

// Function to create an adjacency matrix from a file, with the next format:
AdjacencyMatrix *createAdjacencyMatrix(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return NULL;
    }

    // Create adjacency matrix with pre-defined size
    AdjacencyMatrix *matrix = (AdjacencyMatrix *)malloc(sizeof(AdjacencyMatrix));
    matrix->rows = MAX_N_NODES;
    matrix->columns = MAX_N_NODES;
    matrix->data = (double **)malloc(MAX_N_NODES * sizeof(double *));
    for (int i = 0; i < MAX_N_NODES; i++) {
        matrix->data[i] = (double *)malloc(MAX_N_NODES * sizeof(double));
    }

    // Initialize matrix to zeros
    for (int i = 0; i < MAX_N_NODES; i++) {
        for (int j = 0; j < MAX_N_NODES; j++) {
            matrix->data[i][j] = 0.0;
        }
    }

    // Reading data from file into the matrix
    int row = 0, col = 0;
    double value;
    while (fscanf(file, "%lf", &value) == 1) {
        matrix->data[row][col] = value;
        col++;
        if (col == MAX_N_NODES) {
            col = 0;
            row++;
            if (row == MAX_N_NODES)
                break;
        }
    }

    fclose(file);
    return matrix;
}


// Function to free the memory allocated for an adjacency matrix:
void freeAdjacencyMatrix(AdjacencyMatrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

// Function to get the element at the given position of the adjacency matrix:
double getElementAdjacencyMatrix(AdjacencyMatrix *matrix, int row, int column) {
    return matrix->data[row][column] ;
}

// Function to set the element at the given position of the adjacency matrix:
void setElementAdjacencyMatrix(AdjacencyMatrix *matrix, int row, int column, double value) {
    matrix->data[row][column] = value;
}

// Function to print the adjacency matrix:
void printAdjacencyMatrix(AdjacencyMatrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            printf("%f\t", matrix->data[i][j]);
        }
        printf("\n");
    }
}
