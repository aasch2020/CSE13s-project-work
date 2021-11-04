#include "node.h"
#include "pq.h"
#include "io.h"
#include "code.h"
#include "stack.h"
#include "huffman.h"
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
        case 'o': output = open(optarg, O_WRONLY); break;
        }
    }
    /*  Code C = code_init();
    code_push_bit(&C, 1);
    code_push_bit(&C, 0);
    code_push_bit(&C, 1);

    code_push_bit(&C, 0);

    code_push_bit(&C, 0);

    code_push_bit(&C, 1);

    code_push_bit(&C, 1);

    code_print(&C);
    uint8_t as = 19;
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_print(&C);

    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_print(&C);
    Node *nodeone = node_create('s', 4);
    Node *nocdetwo = node_create('a', 8);
    Stack *s = stack_create(12);
    stack_push(s, nodeone);
    stack_push(s, nocdetwo);
    stack_print(s);
    Node *nd;
    stack_pop(s, &nd);
    node_print(nd);
    node_delete(&nodeone);
    node_delete(&nocdetwo);

    stack_delete(&s);
    uint8_t arr[1000];
    int cnt = read_bytes(input, arr, 10);
    uint8_t scarr[10000];
    int cnt2 = read_bytes(input, scarr, 1000);
    printf("%d, count 2 \n", cnt2);
    printf("\n");
    printf("%ld\n", bytes_read);
    write_bytes(output, arr, cnt - 1);
    write_bytes(output, scarr, cnt2 - 1);*/
    uint8_t bit = 0;
    while (read_bit(input, &bit)) {
        printf("%u", bit);
    }
}
