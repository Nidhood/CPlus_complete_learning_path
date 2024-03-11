#ifndef PROYECTO_TRANSITIONMATRIXHEADER_H
#define PROYECTO_TRANSITIONMATRIXHEADER_H

#include <stdio.h> // Standard input/output definitions
#include <stdlib.h> // Standard library definitions
#include "GraphHeader.h" // Graph structure
#include "AdjacencyMatrixHeader.h" // Adjacency matrix structure

// Global variables:
#define MAX_N_NODES 21

// Definition of the matrix structure:
typedef struct {
    double **data;     // Pointer to the matrix data
    int rows;       // Number of rows
    int columns;    // Number of columns
} TransitionMatrix;

// Function prototypes:
TransitionMatrix *createMatrix(int rows, int columns);
void freeMatrix(TransitionMatrix *matrix);
void freeVector(TransitionMatrix *vector);
double getElement(TransitionMatrix *matrix, int row, int column);
void setElement(TransitionMatrix *matrix, int row, int column, double value);
TransitionMatrix *graphToTransitionMatrix(Graph *g);
TransitionMatrix *AdjacencyMatrixToTransitionMatrix(AdjacencyMatrix *adjacencyMatrix);
TransitionMatrix *dampingFunction(TransitionMatrix *matrix);
void printMatrix(TransitionMatrix *matrix);

#endif
