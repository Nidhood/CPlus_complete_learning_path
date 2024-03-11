#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>
#include "NumberNameEquivalenceHeader.h"
#include "MetricsHeader.h"

#define N 3240

// Data structures:

// Edge structure.
typedef struct {
    int y;
    double weight;
    struct Edge *next; /* next in adj list */
} Edge;

// Vertex structure.
typedef struct {
    int x;
    struct Edge *next;
} Vertex;


// Graph structure.
typedef struct {
    Vertex *vertex[N];
    int degree[N];
    int nvertices;
    int nedges;
    bool directed;
} Graph;

// Function prototypes:

// Initialize the graph with the graph and directed flag.
void initialize_graph(Graph **g, bool directed);

// Insert a vertex into the graph.
void insert_edge(Vertex *v, Edge *e);

// Create a link between two vertices.
void create_link(Graph **g, int x, int y, double weight, bool directed);

// Build a graph from a file.
Graph *buildGraphFromInfo(const char *filename);

// Get the value with the relevance factory of the edge between two vertices.
double getRelevanceFactoryValue(Edge *e, MetricsPaper *metricsPaper, NumberName *numberName);

// Add weight to the graph edges with the metrics.
void addWeightToGraphWithRelevanceFactory(Graph *g, MetricsPaper *metricsPaper, NumberName *numberName);

// Print the graph.
void print_graph(Graph *g);

// Print graph and their weights.
void print_graph_with_weights(Graph *g);

#endif
