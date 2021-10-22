#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    if (vertices <= VERTICES) {
        G->vertices = vertices;
    } else {
        G->vertices = VERTICES;
        printf("too big array");
        G->undirected = undirected;
    }
    return G;
}
void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
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
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if ((i < G->vertices) && (j < G->vertices)) {
        if (G->matrix[i][j] > 0) {
            return true;
        }
    }
    return false;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (!(graph_has_edge(G, i, j))) {
        return 0;
    }
    return G->matrix[i][j];
}

bool graph_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        return G->visited[v];
    }
    return false;
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = true;
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = false;
    }
}

void graph_print(Graph *G) {
    printf("num vert %d\n", G->vertices);
    for (uint32_t i = 0; i < G->vertices; i++) {
        printf("[");
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("  %" PRIu32 "  ", G->matrix[i][j]);
        }
        printf("]\n");
    }
}

void test_graph_undirected(Graph *G) {
    return G->undirected;
}
