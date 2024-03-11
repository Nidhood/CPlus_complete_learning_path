#include "include/TransitionMatrixHeader.h"
#include "include/MatrixOperationsHeader.h"
#include "include/GraphHeader.h"
#include "include/PageRankAlgorithmHeader.h"
#include "include/NumberNameEquivalenceHeader.h"
#include "include/AdjacencyMatrixHeader.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <epsilon> <alpha> <graph_file>\n", argv[0]);
        return -1;
    }

    // Parse command line arguments:
    double alpha = strtod(argv[1], NULL);
    double epsilon = strtod(argv[2], NULL);
    const char *graph_file = argv[3];

    // Detect the data structure to use:
    if(isGraphFile(graph_file)){

        // 1. Build the directed graph from the file:
        Graph *g = buildGraphFromInfo(graph_file);
        if(g == NULL) {
             printf("Error building graph from file %s, check the name please!\n", graph_file);
            return -1;
        }

        // 1.2. Get the name and the number of the papers:
        NumberName *numberName = createNumberName("csvToGraph/number_name_equivalence.csv");

        // 2. Convert the graph to a transition matrix:
        TransitionMatrix *matrix = graphToTransitionMatrix(g);

        // 2.1. Apply the damping function to the matrix:
        matrix = dampingFunction(matrix);

        // 3. Apply the PageRank algorithm:
        matrix = PageRankAlgorithm(matrix, alpha, g->nvertices, epsilon);

        // 4. Iterate the Markov chain method:
        TransitionMatrix *probabilitiesVector = createMatrix(g->nvertices, 1);
        probabilitiesVector = scalarAddition(probabilitiesVector, 1.0 / g->nvertices);
        TransitionMatrix *obtainedRank = markovChainMethod(matrix, probabilitiesVector, epsilon);

        // 5. Print the preference of students to work with each other:
        printTopNodesPapers(obtainedRank, numberName);

        // 6. Save the results to a file:
        saveResultsPageRankAlgorithmRankingPapers(obtainedRank, numberName, "results/papers_ranking.csv");

        // Free allocated memory
        free(g);
        freeMatrix(matrix);

    } else {
        // 1. Build the adjacency matrix from the file:
        AdjacencyMatrix *adjacencyMatrix = createAdjacencyMatrix(graph_file);
        if(adjacencyMatrix == NULL) {
            printf("Error building adjacency matrix from file %s, check the name please!\n", graph_file);
            return -1;
        }

        // 1.2. Get the name and the number of the papers:
        NumberName *numberName = createNumberName("csvToGraph/number_name_equivalence.csv");

        // 2. Convert the  adjacency matrix to a transition matrix:
        TransitionMatrix *matrix = AdjacencyMatrixToTransitionMatrix(adjacencyMatrix);

        // 2.1. Apply the damping function to the matrix:
        matrix = dampingFunction(matrix);

        // 3. Apply the PageRank algorithm:
        matrix = PageRankAlgorithm(matrix, alpha, adjacencyMatrix->rows, epsilon);

        // 4. Iterate the Markov chain method:
        TransitionMatrix *probabilitiesVector = createMatrix(adjacencyMatrix->rows, 1);
        probabilitiesVector = scalarAddition(probabilitiesVector, 1.0 / adjacencyMatrix->rows);
        TransitionMatrix *obtainedRank = markovChainMethod(matrix, probabilitiesVector, epsilon);

        // 5. Print the preference of students to work with each other:
        printTopNodesStudents(obtainedRank, numberName);

        // 6. Save the results to a file:
        saveResultsPageRankAlgorithmRankingStudents(obtainedRank, numberName, "results/students_ranking.csv");

        // Free allocated memory:
        freeAdjacencyMatrix(adjacencyMatrix);
        freeMatrix(matrix);
    }
    return 0;
}