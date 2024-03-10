#ifndef MATRIXOPERATIONSHEADER_H
#define MATRIXOPERATIONSHEADER_H

#include <stdio.h>
#include "AdjacencyMatrixHeader.h"
#include "NumberNameEquivalenceHeader.h"

// Function to perform addition of two adjacency matrices:
AdjacencyMatrix *addMatrices(AdjacencyMatrix *matrix1, AdjacencyMatrix *matrix2);

// Function to calculate the sum of all rows and generate a column matrix with the total sum:
AdjacencyMatrix* sumRows(AdjacencyMatrix *matrix);

// Function to perform scalar addition on an adjacency matrix:
AdjacencyMatrix *scalarAddition(AdjacencyMatrix *matrix, double scalar);

// Function to perform subtraction of two adjacency matrices
AdjacencyMatrix *subtractMatrices(AdjacencyMatrix *matrix1, AdjacencyMatrix *matrix2);

// Function to perform least squares subtraction of two matrices:
AdjacencyMatrix *leastSquaresSubtraction(AdjacencyMatrix *matrix1, AdjacencyMatrix *matrix2);

// Function to perform scalar subtraction on an adjacency matrix
AdjacencyMatrix *scalarSubtraction(AdjacencyMatrix *matrix, double scalar);

// Function to perform scalar multiplication on an adjacency matrix:
AdjacencyMatrix *scalarMultiplication(AdjacencyMatrix *matrix, double scalar);

// Function to perform scalar division on an adjacency matrix:
AdjacencyMatrix *scalarDivision(AdjacencyMatrix *matrix, double scalar);

// Function to perform element-wise division (Hadamard division) of two adjacency matrices
AdjacencyMatrix *elementWiseDivision(AdjacencyMatrix *matrix1, AdjacencyMatrix *matrix2);

// Function to perform matrix multiplication (dot product) on two matrices:
AdjacencyMatrix *elementWiseProduct(AdjacencyMatrix *matrix1, AdjacencyMatrix *matrix2);

// Function to perform matrix multiplication (cross product) on two matrices:
AdjacencyMatrix *matrixMultiplication(AdjacencyMatrix *matrix1, AdjacencyMatrix *matrix2);

// Function to transpose a matrix:
AdjacencyMatrix *transposeMatrix(AdjacencyMatrix *matrix);

// Bubble sort algorithm:
void bubbleSort(double arr[], int indices[], int n);

// Print top nodes based on probabilities
void printTopNodes(AdjacencyMatrix *probabilitiesVector, NumberName *numberName);

#endif