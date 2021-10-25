#include "graph.h"

#include "vertices.h"
//The above header files provided in the resources repository by Professor Long. (2021 Professor Long)
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//The below struct definition provided in the assignement document by Professor Long. (2021 Professor Long)
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

//The below function take an integer number of vertices, and a boolean for undirectedness, and initializes an allocates a graph struct.
//The below code inspired by the assignment document code provided by Professor Long. (2021 Professor Long)
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    if (vertices <= VERTICES) {
        G->vertices = vertices;
        G->undirected = undirected;
    } else {
        G->vertices = VERTICES;
        printf("Input array is too large\n");
        G->undirected = undirected;
    }
    return G;
}

//The below function takes a pointer to a pointer of a graph struct G, it then deallocates the memoery for the graph,
//and makes the pointer null to prevent use after free.
//The below code is provided by Professor Long in the assignment document (2021 Professor Long).
void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

//This function takes a pointer to a graph and returns it's number of vertices.
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

//This function takes a three integers, for the vertices of the graph and the weight of the edge.
//It checks if the edge is within the bounds of vertices, and if it is adds it to the matrix.
//If the graph is undirected it also adds the reflected edge.
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i == j) {
        return false;
    }
    if ((i < G->vertices) && (j < G->vertices)) {
        G->matrix[i][j] = k;
        if (G->undirected) {
            G->matrix[j][i] = k;
            if (G->matrix[i][j] == G->matrix[j][i] == k) {
                return true;
            }
        } else {
            if (G->matrix[i][j] == k) {
                return true;
            }
        }
    }
    return false;
}

//This function takes two vertices and checks if there is an edge from the vertex to the other vertex.
//It achieves this by checking if the weight of the two vertices is greater than 0.
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if ((i < G->vertices) && (j < G->vertices)) {
        if (G->matrix[i][j] != 0) {
            return true;
        }
    }
    return false;
}

//This function takes two vertices and returns the weight of the weight of the edge in the matrix
//IF the graph doesn't have that edge it returns 0
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (!(graph_has_edge(G, i, j))) {
        return 0;
    }
    return G->matrix[i][j];
}

//This function takes a vertex and checks if it is visited.
//It does this by checking if the index v in the array of booleans visited it true
bool graph_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        return G->visited[v];
    }
    return false;
}

//This function takes a vertex and marks it as visited, by marking the index v in the visited array true.
void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = true;
    }
}

//This function takes a vertex and marks it as visited, by marking the index v in the visited array false
void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = false;
    }
}

//This function is for debugging purposes, and prints the matrix of edges.
void graph_print(Graph *G) {
    printf("num vert %d\n", G->vertices);
    for (uint32_t i = 0; i < G->vertices; i++) {
        printf("[");
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%3" PRIu32 "", G->matrix[i][j]);
        }
        printf("]\n");
    }
}

//This is an accessor function for if the graph is undirected, it take a graph pointer and returns a boolean of directedness
bool test_graph_undirected(Graph *G) {
    return G->undirected;
}
