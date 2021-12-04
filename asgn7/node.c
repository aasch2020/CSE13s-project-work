#include "node.h"
//This above header file provided in the resources repository by Professor Long (professor Long 2021)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Creates a new node with the given oldspeak and newspeak, and returns the pointer to the node.
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    if (newspeak) { //If there is newspeak, as is the case for oldspeak, and not badspeak, set newspeak.
        n->newspeak = strdup(newspeak);
    } else {

        n->newspeak = NULL;
    }
    n->oldspeak = strdup(oldspeak);
    return n;
}

//Frees the memory used by the strings of node oldspeak and newspeak, and the node itself.
//Sets the node pointer to null as well.
void node_delete(Node **n) {
    if ((*n)->oldspeak) {
        free((*n)->oldspeak);
    }
    if ((*n)->newspeak) {
        free((*n)->newspeak);
    }
    free(*n);
    *n = NULL;
    return;
}
//Prints the node by printing both oldspeak and newspeak if they exits, and only oldspeak if newspeak doesn't exist.
void node_print(Node *n) {
    if (n) {
        if (n->newspeak) {
            printf("%s -> %s\n", n->oldspeak, n->newspeak);
        } else {
            printf("%s\n", n->oldspeak);
        }
    }

    return;
}
