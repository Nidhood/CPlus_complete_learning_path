#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // Incluir para trabajar con cadenas de caracteres

#define N 100

// Define una macro para el tipo de dato del grafo
#define GRAPH_TYPE_INT 0
#define GRAPH_TYPE_STRING 1
#define GRAPH_TYPE_CHAR 2
#define GRAPH_TYPE_CUSTOM 3

// Define una macro para el tipo de datos de los enlaces
#define EDGE_DATA_TYPE_INT int
#define EDGE_DATA_TYPE_STRING char *
#define EDGE_DATA_TYPE_CHAR char
#define EDGE_DATA_TYPE_CUSTOM CustomType

// Custom type (reemplaza "CustomType" con tu propio tipo de datos)
typedef struct {
    // Definir los campos necesarios para tu tipo de datos
    int value;
} CustomType;

// Vertex structure.
typedef struct {
    int x;
    struct Edge *next;
} Vertex;

// Edge structure for integer data.
typedef struct EdgeInt {
    int y;
    int weight;
    EDGE_DATA_TYPE_INT data; // Datos del enlace
    struct EdgeInt *next;
} EdgeInt;

// Edge structure for string data.
typedef struct EdgeString {
    int y;
    int weight;
    EDGE_DATA_TYPE_STRING data; // Datos del enlace
    struct EdgeString *next;
} EdgeString;

// Edge structure for char data.
typedef struct EdgeChar {
    int y;
    int weight;
    EDGE_DATA_TYPE_CHAR data; // Datos del enlace
    struct EdgeChar *next;
} EdgeChar;

// Edge structure for custom type data.
typedef struct EdgeCustom {
    int y;
    int weight;
    EDGE_DATA_TYPE_CUSTOM data; // Datos del enlace
    struct EdgeCustom *next;
} EdgeCustom;

// Graph structure.
typedef struct {
    Vertex *vertex[N];
    int degree[N];
    int nvertices;
    int nedges;
    bool directed;
    int type; // Tipo de datos del grafo
} Graph;

// Function prototypes:

// Initialize the graph with the graph and directed flag.
void initialize_graph(Graph **g, bool directed, int type);

// Insert a vertex into the graph.
void insert_edge_int(Vertex *v, EdgeInt *e);
void insert_edge_string(Vertex *v, EdgeString *e);
void insert_edge_char(Vertex *v, EdgeChar *e);
void insert_edge_custom(Vertex *v, EdgeCustom *e);

// Create a link between two vertices.
void create_link_int(Graph **g, int x, int y, int weight, EDGE_DATA_TYPE_INT data);
void create_link_string(Graph **g, int x, int y, int weight, EDGE_DATA_TYPE_STRING data);
void create_link_char(Graph **g, int x, int y, int weight, EDGE_DATA_TYPE_CHAR data);
void create_link_custom(Graph **g, int x, int y, int weight, EDGE_DATA_TYPE_CUSTOM data);

// Print the graph.
void print_graph(Graph *g);

// Define funciones específicas para el tipo de datos del grafo
#define DEFINE_GRAPH_FUNCTIONS(TYPE) \
void initialize_##TYPE##_graph(Graph **g, bool directed); \
void create_##TYPE##_link(Graph **g, int x, int y, int weight, TYPE data);

// Define funciones específicas para el tipo de datos del grafo
DEFINE_GRAPH_FUNCTIONS(EDGE_DATA_TYPE_INT)
DEFINE_GRAPH_FUNCTIONS(EDGE_DATA_TYPE_STRING)
DEFINE_GRAPH_FUNCTIONS(EDGE_DATA_TYPE_CHAR)
DEFINE_GRAPH_FUNCTIONS(EDGE_DATA_TYPE_CUSTOM)

#endif
