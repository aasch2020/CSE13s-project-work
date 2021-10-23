#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int main() {

    struct Graph *graphone = graph_create(5, true);
    srandom(1234);
    graph_add_edge(graphone, 1, 4, 22);
    graph_add_edge(graphone, 3, 4, 10);
    graph_add_edge(graphone, 3, 3, 12321);
    graph_print(graphone);
    for (int i = 0; i < 80; i++) {
        graph_add_edge(graphone, (random() % 5), (random() % 5), (random() % 100 + 1));
    }
    graph_print(graphone);
    struct Stack *stackone = stack_create(5);
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
    path_pop_vertex(pathone, &popping, graphone);
    path_pop_vertex(pathone, &popping, graphone);
    path_print(pathone, output, city);
    printf("pathbnd\n");
    path_print(pathtwo, output, city);
    printf("vert count %d\n", path_vertices(pathone));
    printf("%d\n", path_length(pathone));
    path_delete(&pathone);
    path_delete(&pathtwo);
    graph_delete(&graphone);
}
