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
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define OPTIONS "hvi:o:"

//The below function takes command line arguments, and encodes the given input file into the output file.
int main(int argc, char **argv) {
    // The below code parses command line arguments,
    // It prints the appropriate help message if the h input is given
    // It also sets the input and output files if they are given, and errors if the infile is invalid.
    int opt = 0;
    bool stats = false;
    int input = 0;
    int output = 1;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n  A Huffman encoder.\n  Compresses a file using the Huffman coding "
                   "algorithm.\n\n");
            printf("USAGE\n  ./encode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n  -h             Program usage and help.\n  -v             Print "
                   "compression statistics.\n  -i infile      Input file to compress.\n  -o "
                   "outfile     Output of compressed data.\n");
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
    //This below code creates a list of the length of all the characters in extended ascii (0-255)
    //This code then reads through the entire input file, and for each time a character is in the input file
    //increments the character by 1 in the given histogram
    uint64_t hist[ALPHABET] = { 0 };
    uint8_t arr[BLOCK];
    int bytes_read = BLOCK + 1;
    while (bytes_read > 0) {
        bytes_read = read_bytes(input, arr, BLOCK);
        for (int i = 0; i < bytes_read; i++) {
            hist[arr[i]]++;
        }
    }

    //Both 0 and 255 are incremented by one, this is to make sure the program still runs with an empty input file
    hist[0]++;
    hist[255]++;

    //This code calls the build tree function to build a huffman tree from the above histogram.
    Node *root = build_tree(hist);

    //Thi code takes the given tree, and creates a code table for the given tree.
    Code ctable[ALPHABET] = { 0 };
    build_codes(root, ctable);
    uint16_t numchar = 0;
    //This code counts the number of unique characters in the input, which is all nonzero parts of the code table.
    for (int i = 0; i < 256; i++) {
        if (!code_empty(&ctable[i])) {
            numchar++;
        }
    }
    //This below code takes the size of the tree, which is unique chars *3 -1, and sets it in the given header struct
    numchar = numchar * 3 - 1;
    Header head;

    //This cide sets all the paramets of the header struct to their appropriate values, by reading the file size and permissions of the input file
    //and writing in the defined magic number

    head.magic = MAGIC;
    struct stat statsbuf;
    fstat(input, &statsbuf);
    head.permissions = statsbuf.st_mode;
    head.file_size = statsbuf.st_size;
    head.tree_size = numchar;
    //This code creates a new uint8_t pointer to the header struct, so that it can be written, then writes it to the outfile
    uint8_t *bufprin = (uint8_t *) &head;
    write_bytes(output, bufprin, 16);

    //This code writes to the output by parsing throught the tree using dump_tree
    dump_tree(output, root);

    //This code then returns to the start of the file, and reads each symbol in the input, then writes the appropriate code for each symbol
    //from the above code table until the end of the file.
    lseek(input, 0, SEEK_SET);
    uint8_t arr2[BLOCK] = { 0 };
    int bytes_read_code = BLOCK + 1;
    while (bytes_read_code > 0) {
        bytes_read_code = read_bytes(input, arr2, BLOCK);
        for (int i = 0; i < bytes_read_code; i++) {
            write_code(output, &ctable[arr2[i]]);
        }
    }

    //This code sets the permissions of the output file to those given by the input file,
    //Then it flushes codes, to make sure any unwritten code are written.
    fchmod(output, head.permissions);
    flush_codes(output);

    //this closes the files and deletes the tree to prevent memory leak
    delete_tree(&root);
    close(input);
    close(output);
}
