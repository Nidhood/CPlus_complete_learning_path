#include "graph.h"
#include <stdlib.h>
#include <stdbool.h>

/* 1-----2---3 */
/* | ___/|   | */
/* |/    |   | */
/* 5-----4---+ */
int main()
{
    Graph *g = malloc(sizeof(Graph));
    initialize_graph(&g, false);
    create_link(&g, 1, 2, 1, false);
    create_link(&g, 1, 5, 1, false);
    create_link(&g, 2, 5, 1, false);
    create_link(&g, 2, 4, 1, false);
    create_link(&g, 2, 3, 1, false);
    create_link(&g, 3, 4, 1, false);
    create_link(&g, 4, 5, 1, false);
    print_graph(g);
    return 0;
}