#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
void dsp(Path *current, Path *shortest, uint32_t v, Graph *G, bool verbose, FILE *outfile, char *cities[]){
	graph_mark_visited(G, v);
	path_push_vertex(current, v, G);
	uint32_t total_vertices = graph_vertices(G);
	bool no_dead_end = false;
	for(uint32_t i = 0; i < total_vertices; i++){
		if(!graph_visited(G, i)){
			no_dead_end = true;
			dsp(current, shortest, i, G, verbose, outfile, cities);
		}
	}
	if(!no_dead_end){
		if((path_vertices(current) == total_vertices) && (graph_has_edge(G, v, 0))){
			if(verbose){
				path_print(current, outfile, cities);
			}
			if(path_length(current) < path_length(shortest)){
				path_copy(shortest, current);
			}

		}
	}
	graph_mark_unvisited(G,v);
	uint32_t popped = 0;
	path_pop_vertex(current,&popped , G);
	return;
}
int main() {

    struct Graph *graphone = graph_create(5, false);
    srandom(1234);
    graph_add_edge(graphone, 1, 4, 22);
    graph_add_edge(graphone, 3, 4, 10);
    graph_add_edge(graphone, 3, 3, 12321);
    graph_print(graphone);
    graph_add_edge(graphone, 0, 1, 21);
    graph_add_edge(graphone, 1, 3, 10);
    graph_add_edge(graphone, 3, 2, 90);
    graph_add_edge(graphone, 2, 4, 13);
    graph_add_edge(graphone, 4, 1, 9);
///    for (int i = 0; i < 80; i++) {
//        graph_add_edge(graphone, (random() % 5), (random() % 5), (random() % 100 + 1));
//    }
    graph_print(graphone);
printf("is visited %d\n", graph_visited(graphone, 3));

    graph_mark_visited(graphone, 3);
printf("is visited %d\n", graph_visited(graphone, 3));
graph_mark_unvisited(graphone, 3);
printf("is visited %d\n", graph_visited(graphone, 3));
        struct Stack *stackone = stack_create(5);
	printf("emtpy working as intended %d\n", stack_empty(stackone));
    for (int i = 0; i < 5; i++) {
        stack_push(stackone, i + 3);
    }
    FILE *output = stdout;
    if (stack_full(stackone)) {
        //	printf("full\n");
    }
    char *city[9] = { "as", "sa", "fd", "4city", "5city", "nae", "31", "32", "33" };
    //  stack_print(stackone, output, city);
    //  printf("size %d \n", stack_size(stackone));
    uint32_t popping = 15;
    stack_pop(stackone, &popping);
    // printf("popping off %d\n", popping);
    // stack_print(stackone, output, city);
    stack_peek(stackone, &popping);
    //  printf("peeking %" PRIu32 "\n", popping);
    // for (int i = 0; i < 10; i ++){
    //	stack_pop(stackone, &popping);

    //	 }
    //   stack_print(stackone, output, city);
    struct Stack *stacktwo = stack_create(5);
    stack_copy(stacktwo, stackone);

    //  stack_print(stacktwo, output, city);
    stack_delete(&stackone);
    stack_delete(&stacktwo);
    //graph_delete(&graphone);
    struct Path *pathone = path_create();
    struct Path *pathtwo = path_create();

    path_push_vertex(pathone, 3, graphone);
    path_push_vertex(pathone, 4, graphone);
    path_push_vertex(pathone, 1, graphone);
    path_push_vertex(pathone, 0, graphone);
    path_push_vertex(pathone, 2, graphone);
    path_copy(pathtwo, pathone);
    path_pop_vertex(pathone, &popping, graphone);
    path_pop_vertex(pathone, &popping, graphone);
    path_pop_vertex(pathone, &popping, graphone);
    path_pop_vertex(pathone, &popping, graphone);
printf("len path shld be zero? %d\n", path_length(pathone));
//path_print(pathone, output, city);
    path_pop_vertex(pathone, &popping, graphone);
    printf("len path shld be zero ?%d\n", path_length(pathone));

    path_pop_vertex(pathone, &popping, graphone);
//    path_print(pathone, output, city);
    printf("pathbnd\n");
//    path_print(pathtwo, output, city);
    printf("vert count %d\n", path_vertices(pathone));
    printf("%d\n", path_length(pathone));
    //path_delete(&pathone);
    //path_delete(&pathtwo);
    //graph_delete(&graphone);
    dsp(pathone, pathtwo, 0, graphone, true, output, city);
}


