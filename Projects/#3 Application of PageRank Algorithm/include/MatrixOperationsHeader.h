#ifndef MATRIXOPERATIONSHEADER_H
#define MATRIXOPERATIONSHEADER_H

#include <stdio.h>
#include <regex.h>
#include "TransitionMatrixHeader.h"
#include "NumberNameEquivalenceHeader.h"

// Function to perform addition of two adjacency matrices:
TransitionMatrix *addMatrices(TransitionMatrix *matrix1, TransitionMatrix *matrix2);

// Function to calculate the sum of all rows and generate a column matrix with the total sum:
TransitionMatrix* sumRows(TransitionMatrix *matrix);

// Function to perform scalar addition on an adjacency matrix:
TransitionMatrix *scalarAddition(TransitionMatrix *matrix, double scalar);

// Function to perform subtraction of two adjacency matrices
TransitionMatrix *subtractMatrices(TransitionMatrix *matrix1, TransitionMatrix *matrix2);

// Function to perform least squares subtraction of two matrices:
TransitionMatrix *leastSquaresSubtraction(TransitionMatrix *matrix1, TransitionMatrix *matrix2);

// Function to perform scalar subtraction on an adjacency matrix
TransitionMatrix *scalarSubtraction(TransitionMatrix *matrix, double scalar);

// Function to perform scalar multiplication on an adjacency matrix:
TransitionMatrix *scalarMultiplication(TransitionMatrix *matrix, double scalar);

// Function to perform scalar division on an adjacency matrix:
TransitionMatrix *scalarDivision(TransitionMatrix *matrix, double scalar);

// Function to perform element-wise division (Hadamard division) of two adjacency matrices
TransitionMatrix *elementWiseDivision(TransitionMatrix *matrix1, TransitionMatrix *matrix2);

// Function to perform matrix multiplication (dot product) on two matrices:
TransitionMatrix *elementWiseProduct(TransitionMatrix *matrix1, TransitionMatrix *matrix2);

// Function to perform matrix multiplication (cross product) on two matrices:
TransitionMatrix *matrixMultiplication(TransitionMatrix *matrix1, TransitionMatrix *matrix2);

// Function to transpose a matrix:
TransitionMatrix *transposeMatrix(TransitionMatrix *matrix);

// Bubble sort algorithm:
void bubbleSort(double arr[], int indices[], int n);

// Print top nodes based on probabilities of the students:
void printTopNodesStudents(TransitionMatrix *probabilitiesVector, NumberName *numberName);

// Print top nodes based on probabilities of the papers:
void printTopNodesPapers(TransitionMatrix *probabilitiesVector, NumberName *numberName);

// Proof the file if it is a graph or a matrix:
bool isGraphFile(const char *filename);

#endif
