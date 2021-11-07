#include "node.h"
//The above header files proveded in resources repository by Professor Long (Professor Long 2021)
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//This function creates a node given a symbol and frequence and returns the address of the node.
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    n->symbol = symbol;
    n->frequency = frequency;
    return n;
}

//This function takes a pointer to a pointer to a node and deletes the ndoe and then sets the pointer to null
//It returns void.
void node_delete(Node **n) {
    if (*n) {
        free(*n);
        *n = NULL;
    }
    return;
}

//This function creates a new node, with symbol $, and frequency of the given nodes left and right combined
//It returns the adddress to the created node.
//It also sets the left and right parameters of the created node to the given nodes left and right.
Node *node_join(Node *left, Node *right) {
    struct Node *created = node_create('$', (left->frequency + right->frequency));
    created->left = left;
    created->right = right;
    return created;
}

//This function takes a pointer to a node, and recursively prints it, if there are left and right children to the ndoe.
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
    return;
}
