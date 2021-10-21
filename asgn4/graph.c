#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "vertices.h"
struct Graph{
	uint32_t vertices;
	bool undirected;
	bool visited[VERTICES];
	uint32_t matrix[VERTICES][VERTICES};
}

Graph *graph_create(uint32_t vertices, bool undirected){
	Graph *G = (Graph *)calloc(1, sizeof(Graph));
	if (vertices <= VERTICES){
		G->vertices = vertices;
	}else{
		G->vertices = VERTICES;
		printf("too big array");
	G->undirected = undirected;
	return G;
}
void graph_delete(Graph **G)
	free(*G);
	*G = NULL;
	return;
}

uint32_t graph_vertices(Graph *G){
	return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k){
	if((i < G->vertices) && (j < G->vertices)){
		G->matrix[i][j] = k;
		if(G->undirected){
			G->matrix[j][i] = k;
			if (G->matrix[i][j] == G->matrix[j][i] == k){
				return true;
			}
		}else{
			if (G->matrix[i][j] == k){
				return true;
			}
	}
	return false;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j){
	
}
