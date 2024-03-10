#include "include/AdjacencyMatrixHeader.h"
#include "include/MatrixOperationsHeader.h"
#include "include/GraphHeader.h"
#include "include/PageRankAlgorithmHeader.h"
#include "include/NumberNameEquivalenceHeader.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <epsilon> <alpha> <graph_file>\n", argv[0]);
        return -1;
    }

    // Parse command line arguments:
    double alpha = strtod(argv[1], NULL);
    double epsilon = strtod(argv[2], NULL);
    const char *graph_file = argv[3];

    // 1. Build the directed graph from the file:
    Graph *g = buildGraphFromInfo(graph_file);
    if(g == NULL) {
        printf("Error building graph from file %s, check the name please!\n", graph_file);
        return -1;
    }
    // 1.1. Get the name and the number of the papers:
    NumberName *numberName = createNumberName("../number_name_equivalence.txt");

    // 2. Convert the graph to a transition matrix:
    AdjacencyMatrix *matrix = graphToAdjacencyMatrix(g);

    // 3. Apply the PageRank algorithm:
    matrix = PageRankAlgorithm(matrix, alpha, g->nvertices, epsilon);

    // 4. Iterate the Markov chain method:
    AdjacencyMatrix *probabilitiesVector = createMatrix(g->nvertices, 1);
    probabilitiesVector = scalarAddition(probabilitiesVector, 1.0 / g->nvertices);
    AdjacencyMatrix *obtainedRank = markovChainMethod(matrix, probabilitiesVector, epsilon);

    // 5. Print the preference of students to work with each other:
    printTopNodes(obtainedRank, numberName);

    // Free allocated memory
    free(g);
    freeMatrix(matrix);
    return 0;
}