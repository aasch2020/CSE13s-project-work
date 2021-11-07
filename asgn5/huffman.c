#include "huffman.h"
#include "pq.h"
#include "io.h"
#include "stack.h"
#include "node.h"
#include <stdio.h>
#include <stdbool.h>
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
    } else {
        printf("null root error\n");
    }
}

void dump_tree(int outfile, Node *root) {
    if (!(root == NULL)) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);

        if (((root->left == NULL) && (root->right == NULL))) /*!(root->symbol == '$'))*/ {
            uint8_t buf[2] = { 'L', root->symbol };
            write_bytes(outfile, buf, 2);
        } else {
            uint8_t buff[1] = { 'I' };
            write_bytes(outfile, buff, 1);
        }
    }
}

void delete_tree(Node **root) {
    if (!(*root == NULL)) {
        delete_tree(&((*root)->left));
        delete_tree(&((*root)->right));

        if ((((*root)->left == NULL) && ((*root)->right == NULL))) /*!(root->symbol == '$'))*/ {
            node_delete(root);
        }
    }
}

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
            printf("nae nae break\n");
        }
    }
    if (stack_size(a) == 1) {
        Node *take;
        stack_pop(a, &take);
        stack_delete(&a);
        return take;
    } else {
        printf("what the heck\n");
        Node *take2;
        stack_pop(a, &take2);
        return take2;
    }
}
