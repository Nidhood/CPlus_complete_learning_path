#ifndef PROYECTO_ADJACENCYMATRIXHEADER_H
#define PROYECTO_ADJACENCYMATRIXHEADER_H

#include <stdio.h> // Standard input/output definitions
#include <stdlib.h> // Standard library definitions

// Global variables:
#define MAX_N_NODES 21

// Structure to represent the adjacency matrix:
typedef struct {
    double **data;  // Pointer to the matrix data
    int rows;       // Number of rows
    int columns;    // Number of columns
} AdjacencyMatrix;

// Function prototypes:
AdjacencyMatrix *createAdjacencyMatrix(const char *filename);
void freeAdjacencyMatrix(AdjacencyMatrix *matrix);
double getElementAdjacencyMatrix(AdjacencyMatrix *matrix, int row, int column);
void setElementAdjacencyMatrix(AdjacencyMatrix *matrix, int row, int column, double value);
void printAdjacencyMatrix(AdjacencyMatrix *matrix);

#endif
