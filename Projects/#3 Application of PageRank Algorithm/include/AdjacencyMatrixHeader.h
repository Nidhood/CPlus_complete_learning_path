#ifndef PROYECTO_ADJACENCYMATRIXHEADER_H
#define PROYECTO_ADJACENCYMATRIXHEADER_H

#include <stdio.h> // Standard input/output definitions
#include <stdlib.h> // Standard library definitions
#include "GraphHeader.h" // Graph structure

// Definition of the matrix structure:
typedef struct {
    double **data;     // Pointer to the matrix data
    int rows;       // Number of rows
    int columns;    // Number of columns
} AdjacencyMatrix;

// Function prototypes:
AdjacencyMatrix *createMatrix(int rows, int columns);
void freeMatrix(AdjacencyMatrix *matrix);
void freeVector(AdjacencyMatrix *vector);
double getElement(AdjacencyMatrix *matrix, int row, int column);
void setElement(AdjacencyMatrix *matrix, int row, int column, double value);
AdjacencyMatrix* graphToAdjacencyMatrix(Graph *g);
void printMatrix(AdjacencyMatrix *matrix);

#endif
