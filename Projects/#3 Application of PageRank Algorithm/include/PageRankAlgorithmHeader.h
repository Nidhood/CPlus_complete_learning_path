#ifndef PROYECTO_PAGERANKALGORITHMHEADER_H
#define PROYECTO_PAGERANKALGORITHMHEADER_H

#include "TransitionMatrixHeader.h"
#include "NumberNameEquivalenceHeader.h"
#include <stdbool.h>
#include <math.h>

// Apply the PageRank algorithm to the given matrix:
TransitionMatrix *PageRankAlgorithm(TransitionMatrix *matrix, double alpha, int n_nodes, double epsilon);

// Markov chain method:
TransitionMatrix *markovChainMethod(TransitionMatrix *matrix, TransitionMatrix *probabilitiesVector, double epsilon);

// Save the results of the PageRank algorithm to a file:
void saveResultsPageRankAlgorithmRankingStudents(TransitionMatrix *probabilitiesVector, NumberName *numberName, const char *filename);
void saveResultsPageRankAlgorithmRankingPapers(TransitionMatrix *probabilitiesVector, NumberName *numberName, const char *filename);

#endif
