#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    struct Graph *graphone = graph_create(22, true);
    srandom(1234);
    graph_add_edge(graphone, 1, 4, 22);
    graph_add_edge(graphone, 3, 4, 10);
    graph_add_edge(graphone, 3, 3, 12321);
    graph_print(graphone);
    for(int i = 0; i < 80; i++){
	graph_add_edge(graphone, (random() % 22), (random() % 22), (random() % 100 + 1));
    }
    graph_print(graphone);
    struct Stack *stackone = stack_create(22);
}
