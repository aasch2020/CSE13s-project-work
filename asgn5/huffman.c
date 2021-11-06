#include "huffman.h"
#include "pq.h"
#include "io.h"
#include "node.h"
#include <stdio.h>
#include <stdbool.h>
Node *build_tree(uint64_t hist[static ALPHABET]) {
    Node *a = node_create('0', 0);
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
    return d;
}

static Code c;
static bool frstrun;
void build_codes(Node *root, Code table[static ALPHABET]) {
    if (!frstrun) {
        c = code_init();
        frstrun = true;
    }
    if (!(root == NULL)) {
        if (root->symbol == '$') {
            code_push_bit(&c, 0);
            build_codes(root->left, table);
            uint8_t bit;
            code_pop_bit(&c, &bit);
            code_push_bit(&c, 1);
            build_codes(root->right, table);

        } else {
            table[root->symbol] = c;
        }
    } else {
        printf("null root error\n");
    }
}

void dump_tree(int outfile, Node *root) {
    if (!(root == NULL)) {
        if (root->symbol == '$') {
            dump_tree(outfile, root->left);
            dump_tree(outfile, root->right);
            uint8_t bufprinta[1] = { 'I' };
            write_bytes(outfile, bufprinta, 1);

        } else {
            uint8_t bufprint[2] = { 'L', root->symbol };
            write_bytes(outfile, bufprint, 2);
        }
    } else {
        printf("null root error\n");
    }
}
