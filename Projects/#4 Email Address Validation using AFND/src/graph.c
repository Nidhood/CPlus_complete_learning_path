#include "graph.h"

// Funciones genéricas para trabajar con el grafo
void initialize_graph(Graph **g, bool directed, int type) {
    int i;
    *g = malloc(sizeof(Graph));
    (*g)->nvertices = 0;
    (*g)->nedges = 0;
    (*g)->directed = directed;
    (*g)->type = type; // Configurar el tipo de datos del grafo
    for (i = 0; i < N; i++) {
        (*g)->degree[i] = 0;
        (*g)->vertex[i] = NULL;
    }
}

void insert_edge_int(Vertex *v, EdgeInt *e) {
    e->next = v->next;
    v->next = (struct Edge *)e;
}

void insert_edge_string(Vertex *v, EdgeString *e) {
    e->next = v->next;
    v->next = (struct Edge *)e;
}

void insert_edge_char(Vertex *v, EdgeChar *e) {
    e->next = v->next;
    v->next = (struct Edge *)e;
}

void insert_edge_custom(Vertex *v, EdgeCustom *e) {
    e->next = v->next;
    v->next = (struct Edge *)e;
}

void create_link_int(Graph **g, int x, int y, int weight, EDGE_DATA_TYPE_INT data) {
    Vertex *v;
    EdgeInt *e;
    if (!(*g)->vertex[x]) {
        v = malloc(sizeof(Vertex));
        if (!v)
            return;
        v->x = x;
        (*g)->vertex[x] = v;
        (*g)->nvertices += 1;
    } else
        v = (*g)->vertex[x];

    e = malloc(sizeof(EdgeInt));
    e->y = y;
    e->weight = weight;
    e->data = data; // Guardamos el dato en el enlace.
    insert_edge_int(v, e);

    // Ajustar el número de bordes basado en la dirección del grafo
    if (!(*g)->directed)
        create_link_int(g, y, x, weight, data);
    else
        (*g)->nedges += 1;
}

void create_link_string(Graph **g, int x, int y, int weight, EDGE_DATA_TYPE_STRING data) {
    Vertex *v;
    EdgeString *e;
    if (!(*g)->vertex[x]) {
        v = malloc(sizeof(Vertex));
        if (!v)
            return;
        v->x = x;
        (*g)->vertex[x] = v;
        (*g)->nvertices += 1;
    } else
        v = (*g)->vertex[x];

    e = malloc(sizeof(EdgeString));
    e->y = y;
    e->weight = weight;
    e->data = strdup(data); // Guardamos una copia del string en el enlace.
    insert_edge_string(v, e);

    // Ajustar el número de bordes basado en la dirección del grafo
    if (!(*g)->directed)
        create_link_string(g, y, x, weight, data);
    else
        (*g)->nedges += 1;
}

void create_link_char(Graph **g, int x, int y, int weight, EDGE_DATA_TYPE_CHAR data) {
    Vertex *v;
    EdgeChar *e;
    if (!(*g)->vertex[x]) {
        v = malloc(sizeof(Vertex));
        if (!v)
            return;
        v->x = x;
        (*g)->vertex[x] = v;
        (*g)->nvertices += 1;
    } else
        v = (*g)->vertex[x];

    e = malloc(sizeof(EdgeChar));
    e->y = y;
    e->weight = weight;
    e->data = data; // Guardamos el char en el enlace.
    insert_edge_char(v, e);

    // Ajustar el número de bordes basado en la dirección del grafo
    if (!(*g)->directed)
        create_link_char(g, y, x, weight, data);
    else
        (*g)->nedges += 1;
}

void create_link_custom(Graph **g, int x, int y, int weight, EDGE_DATA_TYPE_CUSTOM data) {
    Vertex *v;
    EdgeCustom *e;
    if (!(*g)->vertex[x]) {
        v = malloc(sizeof(Vertex));
        if (!v)
            return;
        v->x = x;
        (*g)->vertex[x] = v;
        (*g)->nvertices += 1;
    } else
        v = (*g)->vertex[x];

    e = malloc(sizeof(EdgeCustom));
    e->y = y;
    e->weight = weight;
    e->data = data; // Guardamos el dato en el enlace.
    insert_edge_custom(v, e);

    // Ajustar el número de bordes basado en la dirección del grafo
    if (!(*g)->directed)
        create_link_custom(g, y, x, weight, data);
    else
        (*g)->nedges += 1;
}

void print_graph(Graph *g) {
    int i;
    Vertex *v;
    printf("Graph (%s):\n", g->directed ? "Dirigido" : "No dirigido");
    for (i = 0; i < g->nvertices; i++) {
        v = g->vertex[i];
        if (v) {
            printf("Vertex %d:\n", v->x);

            switch (g->type) {
                case GRAPH_TYPE_INT: {
                    EdgeInt *e_int;
                    for (e_int = (EdgeInt *) v->next; e_int; e_int = (EdgeInt *) e_int->next) {
                        printf("    %d -> %d (%d)\n", v->x, e_int->y, e_int->data);
                    }
                    break;
                }
                case GRAPH_TYPE_STRING: {
                    EdgeString *e_string;
                    for (e_string = (EdgeString *) v->next; e_string; e_string = (EdgeString *) e_string->next) {
                        printf("    %d -> %d (%s)\n", v->x, e_string->y, e_string->data);
                    }
                    break;
                }
                case GRAPH_TYPE_CHAR: {
                    EdgeChar *e_char;
                    for (e_char = (EdgeChar *) v->next; e_char; e_char = (EdgeChar *) e_char->next) {
                        printf("    %d -> %d (%c)\n", v->x, e_char->y, e_char->data);
                    }
                    break;
                }
                case GRAPH_TYPE_CUSTOM: {
                    EdgeCustom *e_custom;
                    for (e_custom = (EdgeCustom *) v->next; e_custom; e_custom = (EdgeCustom *) e_custom->next) {
                        printf("    %d -> %d (%d)\n", v->x, e_custom->y, e_custom->data.value);
                    }
                    break;
                }
            }
        }
    }

    // Mostrar todas las conexiones y nodos de una vez
    printf("\nAll connections and nodes:\n");
    for (i = 0; i < g->nvertices; i++) {
        v = g->vertex[i];
        if (v) {
            switch (g->type) {
                case GRAPH_TYPE_INT: {
                    EdgeInt *e_int;
                    for (e_int = (EdgeInt *) v->next; e_int; e_int = (EdgeInt *) e_int->next) {
                        if (g->directed) {
                            printf("%d -> %d (%d)\n", v->x, e_int->y, e_int->data);
                        } else {
                            printf("%d -- %d (%d)\n", v->x, e_int->y, e_int->data);
                        }
                    }
                    break;
                }
                case GRAPH_TYPE_STRING: {
                    EdgeString *e_string;
                    for (e_string = (EdgeString *) v->next; e_string; e_string = (EdgeString *) e_string->next) {
                        if (g->directed) {
                            printf("%d -> %d (%s)\n", v->x, e_string->y, e_string->data);
                        } else {
                            printf("%d -- %d (%s)\n", v->x, e_string->y, e_string->data);
                        }
                    }
                    break;
                }
                case GRAPH_TYPE_CHAR: {
                    EdgeChar *e_char;
                    for (e_char = (EdgeChar *) v->next; e_char; e_char = (EdgeChar *) e_char->next) {
                        if (g->directed) {
                            printf("%d -> %d (%c)\n", v->x, e_char->y, e_char->data);
                        } else {
                            printf("%d -- %d (%c)\n", v->x, e_char->y, e_char->data);
                        }
                    }
                    break;
                }
                case GRAPH_TYPE_CUSTOM: {
                    EdgeCustom *e_custom;
                    for (e_custom = (EdgeCustom *) v->next; e_custom; e_custom = (EdgeCustom *) e_custom->next) {
                        if (g->directed) {
                            printf("%d -> %d (%d)\n", v->x, e_custom->y, e_custom->data.value);
                        } else {
                            printf("%d -- %d (%d)\n", v->x, e_custom->y, e_custom->data.value);
                        }
                    }
                    break;
                }
            }
        }
    }
}

