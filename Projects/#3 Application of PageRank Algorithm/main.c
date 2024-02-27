#include "AdjacencyMatrixHeader.h"
#include "MatrixOperationsHeader.h"
#include "GraphHeader.h"
#include "PageRankAlgorithmHeader.h"
#include "MenusHeader.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        display_message("Caution! Make sure the parameters are: \%s alpha epsilon graph_file", RED_COLOR, BLACK_COLOR);
        return 1;
    }

    // Parse command line arguments:
    double alpha = strtod(argv[1], NULL);
    double epsilon = strtod(argv[2], NULL);
    const char *graph_file = argv[3];

    // 1. Build the directed graph from the file:
    Graph *g = buildGraphFromInfo(graph_file);

    // 2. Convert the graph to a transition matrix:
    AdjacencyMatrix *matrix = graphToAdjacencyMatrix(g);

    // 3. pply the PageRank algorithm:
    matrix = PageRankAlgorithm(matrix, alpha, g->nvertices, epsilon);

    // 4. Iterate the Markov chain method:
    AdjacencyMatrix *probabilitiesVector = createMatrix(g->nvertices, 1);
    probabilitiesVector = scalarAddition(probabilitiesVector, 1.0 / g->nvertices);
    AdjacencyMatrix *obtainedRank = markovChainMethod(matrix, probabilitiesVector, epsilon);

    // 5. Print the preference of students to work with each other:
    printTopNodes(obtainedRank);

    // Free allocated memory
    free(g);
    freeMatrix(matrix);
    return 0;
}