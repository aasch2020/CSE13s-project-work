#include "path.h"
#include "vertices.h"
#include "stack.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Path {
	Stack *vertices;
	uint32_t length;
};

Path *path_create(void){
	Path *p = (Path *) calloc(1, sizeof(Path));
	p->length = 0;
	p->vertices = stack_create(VERTICES);
}

void path_delete(Path **p){
	graph_delete((*p)->vertices);
	free(*p);
	*p = NULL;
	
	return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G){
	if((v >= graph_vertices(G)) || )

}
