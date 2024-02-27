#include "PageRankAlgorithmHeader.h"
#include "MatrixOperationsHeader.h"

// Apply the PageRank algorithm to the given matrix:
AdjacencyMatrix *PageRankAlgorithm(AdjacencyMatrix *matrix, double alpha, int n_nodes, double epsilon){

    // 1. Multiply the matrix by the alpha value:
    matrix = scalarMultiplication(matrix, alpha);

    // 2. Create matrix of ones:
    AdjacencyMatrix *ones = createMatrix(n_nodes, n_nodes);
    ones = scalarAddition(ones, (1 - alpha) / n_nodes); // Damping factor !

    // 3. Sum the matrices:
    matrix = addMatrices(matrix, ones);

    // 4. Find the transpose of the matrix:
    matrix = transposeMatrix(matrix);

    // Free the ones matrix:
    freeMatrix(ones);

    return matrix;
}

// Markov chain method:
AdjacencyMatrix *markovChainMethod(AdjacencyMatrix *matrix, AdjacencyMatrix *probabilitiesVector, double epsilon) {
    bool converged = false;
    AdjacencyMatrix *oldProbabilities = probabilitiesVector;

    while (!converged) {
        // 1. Multiply the matrix by the probabilities vector:
        AdjacencyMatrix *newProbabilitiesVector = matrixMultiplication(matrix, oldProbabilities);

        // 2. Subtract the old probabilities vector from the new one:
        AdjacencyMatrix *difference = leastSquaresSubtraction(newProbabilitiesVector, oldProbabilities);

        // 3. Calculate the sum of squared differences:
        double sumSquaredDifference = 0.0;
        for (int i = 0; i < difference->rows; i++) {
            sumSquaredDifference += difference->data[i][0] * difference->data[i][0];
        }

        // Check if the sum of squared differences is less than epsilon squared
        if (sumSquaredDifference < epsilon * epsilon) {
            converged = true;
        }

        // 4. Update the old probabilities vector:
        freeMatrix(oldProbabilities);
        oldProbabilities = newProbabilitiesVector;

        // 5. Free the difference matrix:
        freeMatrix(difference);
    }

    return oldProbabilities;
}

