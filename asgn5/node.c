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
/*
int main() {
    printf("main\n");
    struct Node *nodeone = node_create('a', 5);
    node_print(nodeone);
    struct Node *nodetwo = node_create('x', 12);
    struct Node *nodethree = node_join(nodeone, nodetwo);
    struct Node *nodefour = node_join(nodethree, nodetwo);

    node_print(nodethree);
    node_print(nodefour);
    node_delete(&nodeone);
    node_delete(&nodetwo);
    node_delete(&nodethree);
}
*/
