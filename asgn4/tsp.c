#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "huvi:o:"
void dsp(Path *current, Path *shortest, uint32_t v, Graph *G, bool verbose, FILE *outfile,
    char *cities[], uint32_t *recursions) {
    *recursions += 1;
    graph_mark_visited(G, v);
    path_push_vertex(current, v, G);
    uint32_t total_vertices = graph_vertices(G);
    bool no_dead_end = true;
    // path_print(shortest, outfile, cities);
    if (!((path_length(shortest) > 0) && (path_length(current) >= (path_length(shortest))))) {
        for (uint32_t i = 0; i < total_vertices; i++) {
            if ((!(graph_visited(G, i)) && (graph_has_edge(G, v, i)))) {
                no_dead_end = false;
                dsp(current, shortest, i, G, verbose, outfile, cities, recursions);
            }
        }
        if (no_dead_end) {
            if ((path_vertices(current) == total_vertices) && (graph_has_edge(G, v, 0))) {
                //  path_print(current, outfile, cities);
                path_push_vertex(current, 0, G);
                if (verbose) {
                    //	 printf("\n full path \n");
                    path_print(current, outfile, cities);
                }
                if ((path_length(current) < path_length(shortest))
                    || (path_length(shortest) == 0)) {
                    path_copy(shortest, current);
                }
                uint32_t ye = 0;
                path_pop_vertex(current, &ye, G);
            }
        }
    }
    graph_mark_unvisited(G, v);
    uint32_t popped = 0;
    if (!path_pop_vertex(current, &popped, G)) {

        printf("\n\n PANIC \n\n");
    }
    //   path_print(current, outfile, cities);
    return;
}
int main(int argc, char **argv) {
    int opt = 0;
    bool verbose = false;
    bool undirected = false;
    FILE *input = stdin;
    FILE *output = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("help msh\n");
            return 0;
            break;
        case 'v': verbose = true; break;
        case 'u': undirected = true; break;
        case 'i': input = fopen(optarg, "r"); break;
        case 'o': output = fopen(optarg, "w"); break;
        }
    }
    uint32_t number_vertices = 0;

    char buffer[1025];
    fgets(buffer, 1024, input);
    if (1 != sscanf(buffer, "%" SCNu32, &number_vertices)) {
        printf("Please enter vaid num vert\n");
        return 1;
    }
    char **city = (char **) calloc(number_vertices, sizeof(char *));
    for (uint32_t i = 0; i < number_vertices; i++) {
        if(fgets(buffer, 1024, input)){
        //	printf("%s", buffer);
        buffer[strlen(buffer) - 1] = '\0';
        //	fprintf(output,"%s", buffer);
        //sscanf(buffer, "%s", city[i]);
        city[i] = strdup(buffer);
	}
    }
    uint32_t i_vertex;
    uint32_t j_vertex;
    uint32_t weight;

    struct Graph *graph = graph_create(number_vertices, undirected);
    while (fgets(buffer, 1024, input)) {
        if (3 == sscanf(buffer, "%" SCNu32 "%" SCNu32 "%" SCNu32, &i_vertex, &j_vertex, &weight)) {
            graph_add_edge(graph, i_vertex, j_vertex, weight);
        } else {
            //        printf("bad inputs\n");
            break;
        }
    }
    struct Path *current = path_create();
    struct Path *shortest = path_create();
    uint32_t num_rcr = 0;
    dsp(current, shortest, 0, graph, verbose, output, city, &num_rcr);
    // printf("Total recursive calls: %u\n", num_rcr);
    path_print(shortest, output, city);

    graph_delete(&graph);
   // printf(" ");
    for (uint32_t i = 0; i < number_vertices; i++) {
        free(city[i]);
    }
    free(city);
    path_delete(&current);
    path_delete(&shortest);
}
