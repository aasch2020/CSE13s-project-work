#include "node.h"
#include "pq.h"
#include "io.h"
#include "code.h"
#include "stack.h"
#include "defines.h"
#include "huffman.h"
#include "header.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
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
        case 'i':
            input = open(optarg, O_RDONLY);
            if (input == -1) {
                printf("No input file given\n");
                return -1;
            }
            break;
        case 'o': output = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 00400 | 00200); break;
        }
    }

    uint64_t hist[ALPHABET] = { 0 };
    uint8_t arr[BLOCK];
    int bytes_read = BLOCK + 1;
    while (bytes_read > 0) {
        bytes_read = read_bytes(input, arr, BLOCK);
        for (int i = 0; i < bytes_read; i++) {
            hist[arr[i]]++;
        }
    }
    hist[0]++;
    hist[255]++;
    Node *root = build_tree(hist);
    Code ctable[ALPHABET] = { 0 };
    build_codes(root, ctable);
    uint16_t numchar = 0;
    for (int i = 0; i < 256; i++) {
        if (!code_empty(&ctable[i])) {
            numchar++;
        }
    }
    numchar = numchar * 3 - 1;
    Header head;
    head.magic = MAGIC;
    struct stat statsbuf;
    fstat(input, &statsbuf);
    head.permissions = statsbuf.st_mode;
    head.file_size = statsbuf.st_size;

    head.tree_size = numchar;
    uint8_t *bufprin = (uint8_t *) &head;

    write_bytes(output, bufprin, 16);
    dump_tree(output, root);
    lseek(input, 0, SEEK_SET);
    uint8_t arr2[BLOCK] = { 0 };
    int bytes_read_code = BLOCK + 1;
    while (bytes_read_code > 0) {
        bytes_read_code = read_bytes(input, arr2, BLOCK);
        for (int i = 0; i < bytes_read_code; i++) {
            write_code(output, &ctable[arr2[i]]);
        }
    }
    fchmod(output, head.permissions);
    flush_codes(output);
    delete_tree(&root);

    close(input);
    close(output);
}
