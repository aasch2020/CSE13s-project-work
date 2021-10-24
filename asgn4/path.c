#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) {
    Path *p = (Path *) calloc(1, sizeof(Path));
    p->length = 0;
    p->vertices = stack_create(VERTICES);
    return p;
}

void path_delete(Path **p) {
    stack_delete(&(*p)->vertices);
    free(*p);
    *p = NULL;
    return;
}

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

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path: ");
    stack_print(p->vertices, outfile, cities);
    fprintf(outfile, "Path length: %" PRIu32 "\n", p->length);
}
