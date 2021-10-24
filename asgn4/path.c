#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"
//The above header files provided in the resources repository by Professor Long. (2021 Professor Long)
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//The below struct definitio is provided in the assingment documentory by Professor Long. (2021 Professor Long)
struct Path {
    Stack *vertices;
    uint32_t length;
};

//This function creates a path and returns a pointer the the created path.
//It allocates memory for the stack of vertices within path.
Path *path_create(void) {
    Path *p = (Path *) calloc(1, sizeof(Path));
    p->length = 0;
    p->vertices = stack_create(VERTICES);
    return p;
}

//This function takes a pointer to a path pointer, and deallocates the memory for the path and sets the pointer to null
//It uses the stack delete function for the stack within path.
void path_delete(Path **p) {
    stack_delete(&(*p)->vertices);
    free(*p);
    *p = NULL;
    return;
}

//This function takes a pointer to a path, an integer for vertex, and a pointer to a graph.
//thi function returns a boolean of false on failure, and true on success.
//It first checks if the vertex v is larger than the number of vertices in the graph, thus insuring we do not find
//a path longer than the Hamiltonian path for graph.
//it then checks if the stack in path is empty, in which case the length need not be incremented, and pushes v to stack.
//If the path is not empty, it adds the edge from the top of the stack to the current added vertex to length,
//Then pushes the vertex to the stack.
//This utilizes stack_peek, and graph_edge_weight, and stack_push.
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    if (v >= graph_vertices(G)) {
        return false;
    }
    if (stack_empty(p->vertices)) {
        stack_push(p->vertices, v);
        return true;
    } else {
        uint32_t x = 0;
        stack_peek(p->vertices, &x);
        p->length += graph_edge_weight(G, x, v);
        stack_push(p->vertices, v);
        return true;
    }
}

//THis function takes a pointer to a path, a pointer to an integer, adn a pointer to a graph.
//It returns a boolean value of false if the pop fails.
//It utilizes the stack_pop and stack_peek functions to access and manipulate the items in the stack,
//It also utilizes graph_edge_weight to find the weight of the edge used.
//It begins by checking if the stack of vertices is empty, in which case it fails
//It then pops the first vertex off the stack
//Then, if stack is still not empty, peeks at the top of the stack, and subtracts the vertex from the top to the popped from the length.
//It returns the popped value in a pointer given as *v.
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(p->vertices)) {
        return false;
    } else {
        uint32_t x = 0;
        stack_pop(p->vertices, &x);
        *v = x;
        if (!stack_empty(p->vertices)) {
            uint32_t y = 0;
            stack_peek(p->vertices, &y);
            p->length -= graph_edge_weight(G, y, x);
        }
        return true;
    }
}

//this takes a pointer to a path and returns the number of vertices by using stack_size.
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

//This function takes a pointer to a path and returns the length of the path given by p->length.
uint32_t path_length(Path *p) {
    return p->length;
}

//This function copies the path src to dst, given they are both properly allocated.
//Copies the stack within path using stack_copy,
//Then copies the two lengths.
void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
}

//This function prints a path to outfile, using the array of strings cities as the list of cities
//IT prints the length of the path to outfile, then uses stack_print to print the path in the stack
void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %" PRIu32 "\n", p->length);
    fprintf(outfile, "Path: ");
    stack_print(p->vertices, outfile, cities);
}
