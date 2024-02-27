#ifndef PROYECTO_PAGERANKALGORITHMHEADER_H
#define PROYECTO_PAGERANKALGORITHMHEADER_H

#include "AdjacencyMatrixHeader.h"
#include <stdbool.h>

// Apply the PageRank algorithm to the given matrix:
AdjacencyMatrix *PageRankAlgorithm(AdjacencyMatrix *matrix, double alpha, int n_nodes, double epsilon);

// Markov chain method:
AdjacencyMatrix *markovChainMethod(AdjacencyMatrix *matrix, AdjacencyMatrix *probabilitiesVector, double epsilon);

#endif
