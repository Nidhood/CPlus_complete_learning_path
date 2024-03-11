#include "../include/PageRankAlgorithmHeader.h"
#include "../include/MatrixOperationsHeader.h"

// Apply the PageRank algorithm to the given matrix:
TransitionMatrix *PageRankAlgorithm(TransitionMatrix *matrix, double alpha, int n_nodes, double epsilon){

    // 1. Multiply the matrix by the alpha value:
    matrix = scalarMultiplication(matrix, alpha);

    // 2. Create matrix of ones:
    TransitionMatrix *ones = createMatrix(n_nodes, n_nodes);
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
TransitionMatrix *markovChainMethod(TransitionMatrix *matrix, TransitionMatrix *probabilitiesVector, double epsilon) {
    bool converged = false;
    TransitionMatrix *oldProbabilities = probabilitiesVector;

    int counter = 0;

    while (!converged) {

        // 1. Multiply the matrix by the probabilities vector:
        TransitionMatrix *newProbabilitiesVector = matrixMultiplication(matrix, oldProbabilities);

        // 2. Subtract the old probabilities vector from the new one:
        TransitionMatrix *difference = leastSquaresSubtraction(newProbabilitiesVector, oldProbabilities);
        // 3. Calculate the sum of squared differences:
        double sumSquaredDifference = 0.0;
        for (int i = 0; i < difference->rows; i++) {
            sumSquaredDifference += difference->data[i][0];
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

        counter++;
    }

    printf("Iterations: %d\n", counter);
    return oldProbabilities;
}

// Save the results of the PageRank algorithm to a file (with the format of printTopNodesStudents):
void saveResultsPageRankAlgorithmRankingStudents(TransitionMatrix *probabilitiesVector, NumberName *numberName, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    int n = probabilitiesVector->rows;
    double *probabilities = malloc(n * sizeof(double));
    int *indices = malloc(n * sizeof(int));

    // Copy probabilities and indices
    for (int i = 0; i < n; i++) {
        probabilities[i] = probabilitiesVector->data[i][0];
        indices[i] = i;
    }

    // Sort probabilities and corresponding indices
    bubbleSort(probabilities, indices, n);

    // Print top nodes
    fprintf(file, "Rank,Student,Probability\n");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d,%d,%.6f\n", i+1, indices[i], probabilities[i]);
    }

    // Free allocated memory
    free(probabilities);
    free(indices);
    fclose(file);
}

// Save the results of the PageRank algorithm to a file (with the format of printTopNodesPapers):
void saveResultsPageRankAlgorithmRankingPapers(TransitionMatrix *probabilitiesVector, NumberName *numberName, const char *filename) {
    // Counter for the number of papers:
    int counter = 1;

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    int n = probabilitiesVector->rows;
    double *probabilities = malloc(n * sizeof(double));
    int *indices = malloc(n * sizeof(int));

    // Copy probabilities and indices
    for (int i = 0; i < n; i++) {
        probabilities[i] = probabilitiesVector->data[i][0];
        indices[i] = i;
    }

    // Sort probabilities and corresponding indices
    bubbleSort(probabilities, indices, n);

    // Print top nodes
    fprintf(file, "Rank,No.,Paper,Probability\n");
    for (int i = 0; i < n; i++) {
        if(numberName->papers[indices[i]]->paperNumber < 178){
            fprintf(file, "%d,%d,%s,%.6f\n", counter++, numberName->papers[indices[i]]->paperNumber, numberName->papers[indices[i]]->paperName, probabilities[i]);
        }
    }

    // Free allocated memory
    free(probabilities);
    free(indices);
    fclose(file);
}