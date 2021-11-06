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
        case 'o': output = open(optarg, O_WRONLY | O_CREAT, 00400 | 00200); break;
        }
    }

    Code c = code_init();
    code_push_bit(&c, 1);
    code_push_bit(&c, 1);
    code_push_bit(&c, 0);
    code_push_bit(&c, 1);
    Code b = code_init();
    code_push_bit(&b, 1);
    code_push_bit(&b, 1);
    code_push_bit(&b, 1);
    code_push_bit(&b, 0);
    code_push_bit(&b, 1);

    code_print(&c);
    code_print(&b);
    write_code(output, &c);
    write_code(output, &b);
    flush_codes(output);
}
