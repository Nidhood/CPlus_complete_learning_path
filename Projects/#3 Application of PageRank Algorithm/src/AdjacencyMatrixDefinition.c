#include "AdjacencyMatrixHeader.h"

// Function to create a matrix of size rows x columns
AdjacencyMatrix *createMatrix(int rows, int columns) {
    AdjacencyMatrix *matrix = malloc(sizeof(AdjacencyMatrix));
    if (matrix == NULL) {
        return NULL; // Error: couldn't allocate memory
    }

    matrix->data = malloc(rows * sizeof(double *));
    if (matrix->data == NULL) {
        free(matrix);
        return NULL; // Error: couldn't allocate memory
    }

    for (int i = 0; i < rows; i++) {
        matrix->data[i] = malloc(columns * sizeof(double));
        if (matrix->data[i] == NULL) {
            // If allocation fails, free the previously allocated memory
            for (int j = 0; j < i; j++) {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            return NULL; // Error: couldn't allocate memory
        }
    }

    matrix->rows = rows;
    matrix->columns = columns;

    return matrix;
}

// Function to free the memory allocated to the matrix
void freeMatrix(AdjacencyMatrix *matrix) {
    if (matrix != NULL) {
        for (int i = 0; i < matrix->rows; i++) {
            free(matrix->data[i]);
        }
        free(matrix->data);
        free(matrix);
    }
}

// Function to get a specific element of the matrix
double getElement(AdjacencyMatrix *matrix, int row, int column) {
    if (row >= 0 && row < matrix->rows && column >= 0 && column < matrix->columns) {
        return matrix->data[row][column];
    } else {
        // Error: indices out of range
        return -1; // You could choose another value to represent the error
    }
}

// Function to set a value at a specific element of the matrix
void setElement(AdjacencyMatrix *matrix, int row, int column, double value) {
    if (row >= 0 && row < matrix->rows && column >= 0 && column < matrix->columns) {
        matrix->data[row][column] = value;
    }
}

// Function to convert a graph to an adjacency matrix using the PageRank algorithm
AdjacencyMatrix* graphToAdjacencyMatrix(Graph *g) {
    // Calculate the number of nodes in the graph
    int numNodes = g->nvertices;

    // Create a new adjacency matrix with dimensions numNodes x numNodes
    AdjacencyMatrix *adjMatrix = createMatrix(numNodes, numNodes);

    // Iterate over the vertices of the graph
    for (int i = 0; i < g->nvertices; i++) {
        Vertex *currentVertex = g->vertex[i];
        Edge *currentEdge = (Edge *) currentVertex->next;
        int totalConnections = 0;

        // Count total connections of the current vertex
        while (currentEdge != NULL) {
            totalConnections++;
            currentEdge = (Edge *) currentEdge->next;
        }

        // Update probabilities for each connection of the current vertex
        currentEdge = (Edge *) currentVertex->next;
        while (currentEdge != NULL) {
            adjMatrix->data[i][currentEdge->y] = 1.0 / totalConnections;
            currentEdge = (Edge *) currentEdge->next;
        }
    }

    // Return the resulting adjacency matrix
    return adjMatrix;
}

// Function to print the matrix
void printMatrix(AdjacencyMatrix *matrix) {
    if (matrix == NULL) {
        printf("Matrix is NULL\n");
        return;
    }

    printf("Matrix (%d x %d):\n", matrix->rows, matrix->columns);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            printf("%f\t", matrix->data[i][j]);
        }
        printf("\n");
    }
}

