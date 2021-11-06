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
        case 'i': input = open(optarg, O_RDONLY); break;
        case 'o': output = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 00400 | 00200); break;
        }
    }

    uint64_t hist[ALPHABET] = { 0 };
    uint8_t arr[10];
    int bytes_read = 11;
    while (bytes_read >= 10) {
        bytes_read = read_bytes(input, arr, 10);
        for (int i = 0; i < bytes_read; i++) {
            hist[arr[i]]++;
        }
    }
    hist[0]++;
    hist[255]++;
    Node *root = build_tree(hist);
    //    node_print(root);
    Code ctable[ALPHABET] = { 0 };
    build_codes(root, ctable);
    uint16_t numchar = 0;
    for (int i = 0; i < 256; i++) {
        if (!code_empty(&ctable[i])) {
            //        printf("the char is %d\n", i);
            numchar++;
        }
    }
    //  numchar -=2;
    numchar = numchar * 3 - 1;
    Header head;
    head.magic = MAGIC;
    struct stat statsbuf;
    fstat(input, &statsbuf);
    head.permissions = statsbuf.st_mode;
    head.file_size = statsbuf.st_size;

    head.tree_size = numchar;
    // printf("perms %d\n", statsbuf.st_mode);
    uint8_t *bufprin = (uint8_t *) &head;

    write_bytes(output, bufprin, 16);
    dump_tree(output, root);
    lseek(input, 0, SEEK_SET);
    uint8_t arr2[1000] = { 0 };
    // printf("num bytes we readin %d\n", bytes_read);
    int bytes_read_code = 11;
    while (bytes_read_code >= 10) {
        bytes_read_code = read_bytes(input, arr2, 10);
        for (int i = 0; i < bytes_read_code; i++) {
            //        printf("charr is %c\n", arr2[i]);
            //      code_print(&ctable[arr2[i]]);
            write_code(output, &ctable[arr2[i]]);
        }
    }
    flush_codes(output);
    // write_bytes(output, arr2, cntr2);
}
