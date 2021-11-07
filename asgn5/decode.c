#include "node.h"
#include "pq.h"
#include "io.h"
#include "code.h"
#include "stack.h"
#include "defines.h"
#include "huffman.h"
#include "header.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <inttypes.h>
#include <sys/stat.h>
#define OPTIONS "hvi:o:"
int main(int argc, char **argv) {
    // The below code parses command line arguments,
    // It sets the verbose and undirected booleans to true if given.
    // It also sets the input and output files if they are given, and errors if the infile is invalid.
    int opt = 0;
    bool stats = false;
    int input = 0;
    int output = 1;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("HELP\n");
            printf("HELPMSG\n\n");
            return 0;
            break;
        case 'v': stats = true; break;
        case 'i': input = open(optarg, O_RDONLY); break;
        case 'o': output = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 00400 | 00200); break;
        }
    }
    uint8_t buf[4] = { 0 };
    read_bytes(input, buf, 4);
    uint32_t magic = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
    if (!(magic == MAGIC)) {
        printf("bad file \n");
        return 1;
    }
    uint8_t permissions[2] = { 0 };
    read_bytes(input, permissions, 2);
    uint16_t perms = permissions[0] | (permissions[1] << 8);
    fchmod(output, perms);
    uint8_t tree[2] = { 0 };
    read_bytes(input, tree, 2);
    uint16_t tree_size = tree[0] | (tree[1] << 8);
    uint8_t file_size[8] = { 0 };
    uint64_t sizeinbyte = 0;
    read_bytes(input, file_size, 8);
    for (int i = 0; i < 8; i++) {
        sizeinbyte |= (file_size[i] << (8 * i));
    }
    uint8_t *treebuffs = (uint8_t *) calloc(tree_size, sizeof(uint8_t));
    read_bytes(input, treebuffs, tree_size);

    Node *root = rebuild_tree(tree_size, treebuffs);

    Node *iters = root;
    uint64_t numdec = 0;
    uint8_t bit = 0;

    while (numdec < sizeinbyte) {
        if (!((iters->left) || (iters->right))) {
            uint8_t prnlis[1];
            prnlis[0] = iters->symbol;
            write_bytes(output, prnlis, 1);
            iters = root;
            numdec++;
        } else {
            read_bit(input, &bit);
            if (bit == 0) {
                iters = iters->left;
            } else if (bit == 1) {
                iters = iters->right;
            } else {
                printf("what the");
            }
        }
    }
    free(treebuffs);
    delete_tree(&root);
    close(input);
    close(output);
}
