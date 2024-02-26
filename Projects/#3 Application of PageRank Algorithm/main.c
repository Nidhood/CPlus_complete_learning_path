#include "AdjacencyMatrixHeader.h"
#include "MatrixOperationsHeader.h"
#include "GraphHeader.h"

// Main function
int main() {

    // Build the graph from a file:
    Graph *g = buildGraphFromInfo("../groups/group_2.txt");

    // Convert the graph to an adjacency matrix:
    AdjacencyMatrix *matrix = graphToAdjacencyMatrix(g);

    // Print the matrix:
    printMatrix(matrix);

    // Sum rows of the matrix:
    AdjacencyMatrix *vector = sumRows(matrix);

    // Print the vector:
    printMatrix(vector);

    // Free the graph:
    free(g);

    // Free the matrix:
    freeMatrix(matrix);

    return 0;
}