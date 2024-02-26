#include "graph.h"

int main() {

    // Crear un grafo dirigido de tipo entero
    Graph *directedGraph;
    initialize_graph(&directedGraph, true, GRAPH_TYPE_CHAR);

    // Crear enlaces para el grafo dirigido
    create_link_int(&directedGraph, 0, 1, 5, 'F);
    create_link_int(&directedGraph, 1, 2, 3, 'B');
    create_link_int(&directedGraph, 2, 3, 2, 'C');
    create_link_int(&directedGraph, 3, 4, 1, 'P');

    print_graph(directedGraph);

    // Limpiar la memoria
    free(directedGraph);
    return 0;
}
