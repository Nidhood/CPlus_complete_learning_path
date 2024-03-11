#include "../include/TransitionMatrixHeader.h"

// Function to create a matrix of size rows x columns and initialize all elements to 0.0
TransitionMatrix *createMatrix(int rows, int columns) {
    TransitionMatrix *matrix = malloc(sizeof(TransitionMatrix));
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

        // Initialize all elements to 0.0
        for (int j = 0; j < columns; j++) {
            matrix->data[i][j] = 0.0;
        }
    }

    matrix->rows = rows;
    matrix->columns = columns;

    return matrix;
}


// Function to free the memory allocated to the matrix
void freeMatrix(TransitionMatrix *matrix) {
    if (matrix != NULL) {
        for (int i = 0; i < matrix->rows; i++) {
            free(matrix->data[i]);
        }
        free(matrix->data);
        free(matrix);
    }
}

// Function to free the memory allocated to the vector
void freeVector(TransitionMatrix *vector) {
    if (vector != NULL && vector->data != NULL) {
        free(vector->data[0]);  // Liberar solo la columna de datos
        free(vector->data);     // Liberar el arreglo de punteros
        free(vector);           // Liberar la estructura de matriz
    }
}


// Function to get a specific element of the matrix
double getElement(TransitionMatrix *matrix, int row, int column) {
    if (row >= 0 && row < matrix->rows && column >= 0 && column < matrix->columns) {
        return matrix->data[row][column];
    } else {
        // Error: indices out of range
        return -1; // You could choose another value to represent the error
    }
}

// Function to set a value at a specific element of the matrix
void setElement(TransitionMatrix *matrix, int row, int column, double value) {
    if (row >= 0 && row < matrix->rows && column >= 0 && column < matrix->columns) {
        matrix->data[row][column] = value;
    }
}

// Function to convert a graph to an adjacency matrix using the PageRank algorithm
TransitionMatrix* graphToTransitionMatrix(Graph *g) {

    // Calculate the number of nodes in the graph
    int numNodes = 3237;

    // Create a new adjacency matrix with dimensions numNodes x numNodes
    TransitionMatrix *adjMatrix = createMatrix(numNodes, numNodes);

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

            // Check if the edge points to the same vertex
            if (currentEdge->y != i) {
                adjMatrix->data[i][currentEdge->y] = 1.0 / totalConnections;
            }
            currentEdge = (Edge *) currentEdge->next;
        }
    }

    // Return the resulting adjacency matrix
    return adjMatrix;
}

// Function to convert a graph to an adjacency matrix using the PageRank algorithm with the relevance factor:
TransitionMatrix *graphToTransitionMatrixWithRelevanceFactor(Graph *g) {

    // Calculate the number of nodes in the graph
    int numNodes = 3237;

    // Create a new adjacency matrix with dimensions numNodes x numNodes
    TransitionMatrix *transitionMatrix = createMatrix(numNodes, numNodes);

    // Iterate over the vertices of the graph
    for (int i = 0; i < g->nvertices; i++) {
        Vertex *currentVertex = g->vertex[i];
        Edge *currentEdge = (Edge *) currentVertex->next;

        // Update probabilities for each connection of the current vertex
        while (currentEdge != NULL) {
            setElement(transitionMatrix, i, currentEdge->y, currentEdge->weight);
            double number = currentEdge->weight;
            double weight = getElement(transitionMatrix, i, currentEdge->y);
            currentEdge = (Edge *) currentEdge->next;
        }
    }

    // Return the resulting transition matrix
    return transitionMatrix;
}

// Function to convert an adjacency matrix to a transition matrix with the next format:
TransitionMatrix *AdjacencyMatrixToTransitionMatrix(AdjacencyMatrix *adjacencyMatrix) {
    TransitionMatrix *matrix = createMatrix(adjacencyMatrix->rows, adjacencyMatrix->columns);
    for (int i = 0; i < adjacencyMatrix->rows; i++) {
        for (int j = 0; j < adjacencyMatrix->columns; j++) {
            matrix->data[i][j] = adjacencyMatrix->data[i][j];
        }
    }
    return matrix;
}

// Function to apply the damping function to the given matrix (correct the matrix to be a stochastic matrix):
TransitionMatrix *dampingFunction(TransitionMatrix *matrix) {

    // Iterate over the rows of the matrix
    for (int i = 0; i < matrix->rows; i++) {
        double sum = 0.0;

        // Iterate over the columns of the matrix
        for (int j = 0; j < matrix->columns; j++) {
            sum += matrix->data[i][j];
        }

        // If the sum of the row is 0, set all elements to 1/n
        if (sum == 0.0) {
            for (int j = 0; j < matrix->columns; j++) {
                matrix->data[i][j] = 1.0 / matrix->columns;
            }
        } else {

            // Normalize the row to make it a stochastic matrix
            for (int j = 0; j < matrix->columns; j++) {
                matrix->data[i][j] /= sum;
            }
        }
    }
    return matrix;
}

// Function to print the matrix
void printMatrix(TransitionMatrix *matrix) {
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

// Function to print the matrix without zeros:
void printMatrixWithoutZeros(TransitionMatrix *matrix) {
    if (matrix == NULL) {
        printf("Matrix is NULL\n");
        return;
    }

    printf("Matrix (%d x %d):\n", matrix->rows, matrix->columns);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            if (matrix->data[i][j] != 0.0) {
                printf("%f\t", matrix->data[i][j]);
            }
        }
        printf("\n");
    }
}

