#include "node.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    n->symbol = symbol;
    n->frequency = frequency;
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free(*n);
        *n = NULL;
    }
    return;
}

Node *node_join(Node *left, Node *right) {
    struct Node *created = node_create('$', (left->frequency + right->frequency));
    created->left = left;
    created->right = right;
    return created;
}

void node_print(Node *n) {
    printf("The symbol is %d\n", n->symbol);
    printf("With a frequency of %" PRIu64 "\n", n->frequency);
    if (n->left) {

        node_print(n->left);
    }
    if (n->right) {

        node_print(n->right);
    }
    printf("\n");
}
