#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
void dsp(Path *current, Path *shortest, uint32_t v, Graph *G, bool verbose, FILE *outfile,
    char *cities[]) {
    graph_mark_visited(G, v);
    path_push_vertex(current, v, G);
    uint32_t total_vertices = graph_vertices(G);
    bool no_dead_end = false;
    for (uint32_t i = 0; i < total_vertices; i++) {
        if ((!graph_visited(G, i) && (graph_has_edge(G, v, i)))) {
            //	printf("there is a path from %d to %d\n", v, i);
            //	printf("%d, checking with the graph\n", graph_has_edge(G, v, i));
            no_dead_end = true;
            dsp(current, shortest, i, G, verbose, outfile, cities);
        }
    }
    if (!no_dead_end) {
        if ((path_vertices(current) == total_vertices) && (graph_has_edge(G, v, 0))) {
            if (verbose) {
                path_print(current, outfile, cities);
                printf("length %d\n", path_length(current));
            }
            if ((path_length(current) < path_length(shortest)) || (path_length(shortest) == 0)) {
                path_copy(shortest, current);
            }
        }
    }
    graph_mark_unvisited(G, v);
    uint32_t popped = 0;
    path_pop_vertex(current, &popped, G);
    return;
}
int main() {

    struct Graph *graphone = graph_create(26, false);
    srandom(1234);
    graph_add_edge(graphone, 1, 4, 22);
    graph_add_edge(graphone, 3, 4, 10);
    graph_add_edge(graphone, 1, 0, 56);
    graph_add_edge(graphone, 0, 1, 21);
    graph_add_edge(graphone, 1, 3, 10);
    graph_add_edge(graphone, 3, 2, 90);
    graph_add_edge(graphone, 2, 4, 13);
    graph_add_edge(graphone, 4, 0, 9);
    for (int yeet = 0; yeet < 800; yeet++) {
        graph_add_edge(graphone, random() % 26, random() % 26, random() % 100);
    }
    graph_print(graphone);
    ///    for (int i = 0; i < 80; i++) {
    //        graph_add_edge(graphone, (random() % 5), (random() % 5), (random() % 100 + 1));
    //    }
    FILE *output = stdout;
    graph_print(graphone);
    char *city[26] = { "the zero city", "the first city", "the second city", "3city", "4city",
        "5city", "7city", "8city", "9city", "10", "11", "12", "13", "14", "15", "16", "17", "18",
        "19", "20", "21", "22", "23", "24", "25", "26" };

    struct Path *pathone = path_create();
    struct Path *pathtwo = path_create();

    dsp(pathone, pathtwo, 0, graphone, true, output, city);
    path_print(pathtwo, output, city);
    printf("shortest length = %d\n", path_length(pathtwo));
}
