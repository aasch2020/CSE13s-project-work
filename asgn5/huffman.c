#include "huffman.h"
#include "pq.h"
#include "io.h"
#include "stack.h"
#include "node.h"
//The above header files given by Professor Long in the resources repository. (Professor Long 2021)
#include <stdio.h>
#include <stdbool.h>

//The below function takes a histogram of the amount of times characters show up in given input, and then build a tree of nodes.
//This returns the root node of the tree.
//This function begins by creating a priority queue of size ALPHABET, and goes through the histogram adding a node foe every
//character that has a frequeny greater than zero in the histogram
//It then dequeues two elements from the node, and joins them, then enqueuing that joined element until the size of the queue is 1
//This one node is the root of the tree, which is returned.
Node *build_tree(uint64_t hist[static ALPHABET]) {
    Node *a;
    PriorityQueue *pq = pq_create(ALPHABET);
    for (int i = 0; i < 256; i++) {
        if (hist[i]) {
            a = node_create(i, hist[i]);
            enqueue(pq, a);
        }
    }
    while (pq_size(pq) >= 2) {
        Node *a;
        Node *b;
        dequeue(pq, &a);
        dequeue(pq, &b);
        Node *c = node_join(a, b);
        enqueue(pq, c);
    }
    Node *d;
    dequeue(pq, &d);

    pq_delete(&pq);
    return d;
}

//The below function uses a static code, and a static boolean value, one to track the code to add to the table, and the other track if this is
//the first iteration of the recursive function.
//This takes a node, and if the node is not null, and a leaf node it adds the current code to the code table at the index of the character
//If it is a interior node, push 0 into the code and recurse down the left, then pop, push one and recurse down the right.
//It returns void.
static Code c;
static bool frstrun;
void build_codes(Node *root, Code table[static ALPHABET]) {
    if (!frstrun) {
        c = code_init();
        frstrun = true;
    }
    if (!(root == NULL)) {
        if ((root->left == NULL) && (root->right == NULL)) {
            table[root->symbol] = c;

        } else {

            code_push_bit(&c, 0);
            build_codes(root->left, table);
            uint8_t bit;
            code_pop_bit(&c, &bit);
            code_push_bit(&c, 1);
            build_codes(root->right, table);
            code_pop_bit(&c, &bit);
        }
    }
    return;
}

//This function takes an integer filenumber to an output file, and a pointer to a node which is the root of the tree
//This function first checks if the root is NULL, and if it is not, it calls itself on the right and left children of itself
//It then checks if it is an interior node or a leaf node
//If it is a leaf node, it writes L and it's symbol to outfile.
//If it is an interior node, it writes and I to the outfile
//It returns void.
void dump_tree(int outfile, Node *root) {
    if (!(root == NULL)) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);

        if (((root->left == NULL) && (root->right == NULL))) {
            uint8_t buf[2] = { 'L', root->symbol };
            write_bytes(outfile, buf, 2);
        } else {
            uint8_t buff[1] = { 'I' };
            write_bytes(outfile, buff, 1);
        }
    }
    return;
}

//This function takes a pointer to a pointer to a root and traverses through the tree deleting each node
//It does this by checking if the node exists, and if it does calling itself recursively on the left and right nodes
//of the given node.
//It then checks if the given node is a leaf node, and if it is, deletes the node.
//It returns void.
void delete_tree(Node **root) {
    if (!(*root == NULL)) {
        delete_tree(&((*root)->left));
        delete_tree(&((*root)->right));

        if ((((*root)->left == NULL) && ((*root)->right == NULL))) {
            node_delete(root);
        }
    }
    return;
}

//This function rebuilds a tree, by traversing a tree dump, which is in the array tree_dump.
//It takes a number for the number of bytes in the tree, and the array of the tree dump.
//It creates a stack for holding the nodes created by parsing through the tree dump.
//This code iterates through the tree dump size of tree times, and if the symbol in the given spot in the tree dump is L
//it is an interior node, thus it moves forward two, creates a node with the given symbol after the L, and continues iterating
//If the symbol is I, it is an interior node, it pops two elements off the stack, right and left, joins them to make a new node,
//and then pushes the joined node.
//After iterating, there should be one thing left in the stack, dequeue this and return it as it is the root of the tree.
Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]) {
    Stack *a = stack_create(nbytes + 1);
    for (uint16_t i = 0; i < nbytes; i++) {
        if (tree_dump[i] == 'L') {
            i++;
            Node *c = node_create(tree_dump[i], 0);
            stack_push(a, c);

        } else if (tree_dump[i] == 'I') {
            Node *left;
            Node *right;
            stack_pop(a, &right);
            stack_pop(a, &left);
            Node *parent = node_join(left, right);
            stack_push(a, parent);
        } else {
            printf("This shouldn't happen\n");
        }
    }
    if (stack_size(a) == 1) {
        Node *take;
        stack_pop(a, &take);
        stack_delete(&a);
        return take;
    } else {
        Node *take2;
        stack_pop(a, &take2);
        stack_delete(&a);
        return take2;
    }
}
