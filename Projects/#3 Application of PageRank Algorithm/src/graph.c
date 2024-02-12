#include "graph.h"

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

void print_graph(Graph *g) {
    int i, j;
    Vertex *v;
    Edge *e;

    printf("Graph (%s):\n", g->directed ? "Dirigido" : "No dirigido");

    for (i = 0; i < g->nvertices + 1; i++) {
        v = g->vertex[i];
        if (v) {
            printf("Vertex %d:", v->x);

            // Mostrar todas las conexiones incluso si no hay aristas salientes
            for (j = 1; j < g->nvertices + 1; j++) {
                if (g->directed) {
                    printf(" %d -> ", j);
                } else {
                    printf(" %d -- ", j);
                }
            }
            printf("\n");

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

    // Mostrar todas las conexiones y nodos de una vez
    printf("\nAll connections and nodes:\n");
    for (i = 0; i < g->nvertices + 1; i++) {
        v = g->vertex[i];
        if (v) {
            for (e = (Edge *) v->next; e; e = (Edge *) e->next) {
                if (g->directed) {
                    printf("%d -> %d\n", v->x, e->y);
                } else {
                    printf("%d -- %d\n", v->x, e->y);
                }
            }
        }
    }
}