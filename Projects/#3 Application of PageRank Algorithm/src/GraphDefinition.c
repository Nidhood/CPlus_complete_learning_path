#include "../include/GraphHeader.h"

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

void create_link(Graph **g, int x, int y, double weight, bool directed)
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
        create_link(&graph, src, dest, 0, true);
    }

    fclose(file);
    return graph;
}

// Get the value with the relevance factory of the edge between two vertices.
double getRelevanceFactoryValue(Edge *e, MetricsPaper *metricsPaper, NumberName *numberName) {
    const char *paper_name = numberName->papers[e->y]->paperName;
    double total_weight = 0;

    // Buscar la métrica asociada al nombre del paper en el objeto MetricsPaper
    for (int j = 0; j < MAX_AMOUNT_METRICS; j++) {
        Metric *metric = metricsPaper->metrics[j];
        if (metric == NULL) {
            break;
        }
        const char *metric_name = getMetricName(metric);

        // Utilizar regex para encontrar la métrica en el nombre del paper
        regex_t regex;
        if (regcomp(&regex, metric_name, 0) != 0) {
            fprintf(stderr, "Error compiling regex\n");
            exit(EXIT_FAILURE);
        }
        if (regexec(&regex, paper_name, 0, NULL, 0) == 0) {
            // Si se encuentra la métrica en el nombre, sumar su valor al peso total
            total_weight += getMetricValue(metric);
        }
        regfree(&regex);
    }
    return total_weight;
}

// Add weight to the graph edges with the metrics.
void addWeightToGraphWithRelevanceFactory(Graph *g, MetricsPaper *metricsPaper, NumberName *numberName) {

    // Iterar sobre todos los nodos del grafo
    for (int i = 0; i < g->nvertices; i++) {
        Vertex *current_vertex = g->vertex[i];
        double total_weight = 0;

        // Iterar sobre todas las conexiones (aristas) del nodo actual para calcular la suma total
        Edge *current_edge = (Edge *) current_vertex->next;
        while (current_edge != NULL) {
            total_weight += getRelevanceFactoryValue(current_edge, metricsPaper, numberName);
            current_edge = (Edge *) current_edge->next;
        }

        // Asignar los pesos a las aristas salientes del nodo actual
        current_edge = (Edge *) current_vertex->next;
        while (current_edge != NULL) {
            if (total_weight == 0.0) {

                // Si la suma total es 0, asignamos un peso de 0 a todas las aristas
                current_edge->weight = 0.0;
            } else {

                // De lo contrario, asignamos un porcentaje uniforme basado en la suma total
                current_edge->weight = getRelevanceFactoryValue(current_edge, metricsPaper, numberName) / total_weight;
            }

            // Continue to the next edge:
            current_edge = (Edge *) current_edge->next;
        }
    }
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

// Print graph and their weights.
void print_graph_with_weights(Graph *g) {
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
                        printf("%d -> %d (%.2f)\n", v->x, e->y, e->weight);
                    } else {
                        printf("%d --> %d (%.2f)\n", v->x, e->y, e->weight);
                    }
                }
            } else {
                printf("    No edges\n");
            }
        }
    }
}
