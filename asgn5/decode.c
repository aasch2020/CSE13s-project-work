#include "node.h"
#include "pq.h"
#include "io.h"
#include "code.h"
#include "stack.h"
#include "defines.h"
#include "huffman.h"
#include "header.h"
//The above header files are provided in the resources repo by Profoessor Long. (Professor Long 2021)
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <inttypes.h>
#include <sys/stat.h>
#define OPTIONS "hvi:o:"

//The main function takes command line arguments as input, and reads from an input file and decodes it to the output file.
int main(int argc, char **argv) {
    // The below code parses command line arguments,
    // It can print a help message and return early if a given argument is specified.
    // It also sets the input and output files if they are given, and errors if the infile is invalid.
    int opt = 0;
    bool stats = false;
    int input = 0;
    int output = 1;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n  A Huffman decoder.\n  Decompresses a file using the Huffman coding "
                   "algorithm.\n\n");
            printf("USAGE\n  ./decode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n  -h             Program usage and help.\n  -v             Print "
                   "compression statistics.\n  -i infile      Input file to decompress.\n  -o "
                   "outfile     Output of decompressed data.\n");
            return 0;
            break;
        case 'v': stats = true; break;
        case 'i': input = open(optarg, O_RDONLY); break;
        case 'o': output = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 00400 | 00200); break;
        }
    }

    //The below code parses through the first 4 bytes of the input, and check if the given magic number in the infile matches the MAGIC macro
    uint8_t buf[4] = { 0 };
    read_bytes(input, buf, 4);
    uint32_t magic = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
    if (!(magic == MAGIC)) {
        printf("Error, unable to read header \n");
        return -1;
    }

    //This below code parses through 2 bytes of input, and fetches the permissions from the infile, it then setes the permissions of the outfile to the given permissions.
    uint8_t permissions[2] = { 0 };
    read_bytes(input, permissions, 2);
    uint16_t perms = permissions[0] | (permissions[1] << 8);
    fchmod(output, perms);

    //The below code parses through 2 bytes of input, and reads the size of the tree, it then sets the size to the given size variable
    uint8_t tree[2] = { 0 };
    read_bytes(input, tree, 2);
    uint16_t tree_size = tree[0] | (tree[1] << 8);
    //Thie fucntion parses through 8 bytes of input and reads in the file size and sets it to the given file size variable
    uint8_t file_size[8] = { 0 };
    uint64_t sizeinbyte = 0;
    read_bytes(input, file_size, 8);
    for (int i = 0; i < 8; i++) {
        sizeinbyte |= (file_size[i] << (8 * i));
    }

    //This function initializes a list of the tree size, and reads through the tree_size number of bytes and puts it into the tree buffer
    //It then calls rebuild tree to make a tree from the given input.
    uint8_t *treebuffs = (uint8_t *) calloc(tree_size, sizeof(uint8_t));
    read_bytes(input, treebuffs, tree_size);

    Node *root = rebuild_tree(tree_size, treebuffs);

    //This code then parses through both the given tree and the input.
    //It first checks if the node in the tree is a leaf node, if it is, it prints the symbol for the tree
    //If it is not a leaf, it reads from the input by bits, and if the bit is 0 goes down the left of the tree,
    //and if the bit is one goes down the right.
    //It continues this until the sizeinbytes of the written file is the same as given above.
    Node *iters = root;
    uint8_t bit = 0;
    uint64_t numdec = 0;
    while (!(numdec == sizeinbyte)) {
        if (!((iters->left) || (iters->right))) {
            uint8_t prnlis[1];
            numdec++;
            prnlis[0] = iters->symbol;
            write_bytes(output, prnlis, 1);

            iters = root;

        } else {
            read_bit(input, &bit);
            if (bit == 0) {
                iters = iters->left;
            } else if (bit == 1) {
                iters = iters->right;
            } else {
                return -1;
            }
        }
    }

    //This code frees the allocated list, closes the files, and deletes the tree to prevent memeory leaks
    free(treebuffs);
    delete_tree(&root);
    close(input);
    close(output);
    return 0;
}
