#include "GraphHeader.h"

void initialize_graph(Graph **g, bool directed)
{
    int i;

    (*g)->nvertices = 0;
    (*g)->nedges = 0;
    (*g)->directed = directed;

    for (i = 0; i < N; i++)
    {
        (*g)->degree[i] = 0;
        (*g)->vertex[i] = NULL;
    }
}

void insert_edge(Vertex *v, Edge *e)
{
    e->next = v->next;
    v->next = (struct Edge *)e;
}

void create_link(Graph **g, int x, int y, int weight, bool directed)
{
    Vertex *v;
    Edge *e;
    if (!(*g)->vertex[x])
    {
        v = malloc(sizeof(Vertex));
        if (!v)
            return;
        v->x = x;
        (*g)->vertex[x] = v;
        (*g)->nvertices += 1;
    }
    else
        v = (*g)->vertex[x];

    e = malloc(sizeof(Edge));
    e->y = y;
    e->weight = weight;
    insert_edge(v, e);

    if (!directed)
        create_link(g, y, x, weight, true);
    else
        (*g)->nedges += 1;
}

Graph *buildGraphFromInfo(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return NULL;
    }

    // Assuming the file format is as described with lines like "0>17", "0>8", etc.
    int max_vertex = -1;
    int src, dest;
    while (fscanf(file, "%d>%d\n", &src, &dest) != EOF) {
        if (dest > max_vertex) {
            max_vertex = dest;
        }
        if (src > max_vertex) {
            max_vertex = src;
        }
    }

    // Create a graph with max_vertex + 1 vertices (assuming vertices are numbered from 0 to max_vertex)
    Graph *graph = malloc(sizeof(Graph));
    initialize_graph(&graph, true); // Directed graph
    if (graph == NULL) {
        printf("Error creating graph\n");
        fclose(file);
        return NULL;
    }

    // Add edges to the graph
    rewind(file);
    while (fscanf(file, "%d>%d\n", &src, &dest) != EOF) {
        // Assuming weight is always 1
        create_link(&graph, src, dest, 1, true);
    }

    fclose(file);
    return graph;
}


// Print the graph.
void print_graph(Graph *g) {
    Vertex *v;
    Edge *e;

    // Print the type of graph.
    printf("Graph (%s):\n", g->directed ? "Directed" : "Not directed");

    // Print the vertices and edges.
    for (int i = 0; i < g->nvertices + 1; i++) {
        v = g->vertex[i];
        if (v) {
            printf("\nVertex %d:\n", v->x);

            if (v->next != NULL) {
                for (e = (Edge *) v->next; e; e = (Edge *) e->next) {
                    printf("    ");
                    if (g->directed) {
                        printf("%d -> %d (%d)\n", v->x, e->y, e->weight);
                    } else {
                        printf("%d --> %d (%d)\n", v->x, e->y, e->weight);
                    }
                }
            } else {
                printf("    No edges\n");
            }
        }
    }
}
