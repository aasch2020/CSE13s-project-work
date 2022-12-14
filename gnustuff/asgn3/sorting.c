#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "haeisqn:p:r:"
typedef enum { HEAP, SHELL, INSERT, QUICK, HELP } possible_args;
int main(int argc, char **argv) {
    Set input_args = 0;
    int opt = 0;
    unsigned int SEED = 13371453;
    int print = 100;
    int array_length = 100;
    char *endstroul;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        //Loop thugh all of the command line args and check if they are any of the important values

        switch (opt) {
        case 'n':
            array_length = strtoul(optarg, &endstroul, 10);
            if (array_length <= 0) {
                printf("Invalid array_length, using 100\n");
                array_length = 100;
            }
            break;
        case 'p':
            print = strtoul(optarg, &endstroul, 10);
            if (print <= 0) {
                printf("Invalid number of elements to print, using 100\n");
                print = 100;
            }
            break;
        case 'r': SEED = strtoul(optarg, &endstroul, 10); break;
        case 'h': input_args = insert_set(HELP, input_args); break;
        case 'i': input_args = insert_set(INSERT, input_args); break;
        case 'e': input_args = insert_set(HEAP, input_args); break;
        case 's': input_args = insert_set(SHELL, input_args); break;
        case 'q': input_args = insert_set(QUICK, input_args); break;
        case 'a':
            input_args = insert_set(INSERT, input_args);
            input_args = insert_set(HEAP, input_args);
            input_args = insert_set(SHELL, input_args);
            input_args = insert_set(QUICK, input_args);
            break;
        default: break;
        }
    }
    void (*function_pointers[])() = { heap_sort, shell_sort, insertion_sort, quick_sort };
    print = print > array_length ? array_length : print;
    if (input_args == 0) {
        printf("do a sort\n");
    }
    if (member_set(HELP, input_args)) {
        printf("help\n");
        input_args = empty_set();
    }
    Stats stats;
    for (uint32_t i = 0; i <= 10000; i+=100){
	array_length = i;
	for (possible_args k = HEAP; k <= QUICK; k++) {
        if (member_set(k, input_args)) {
            uint32_t *A = (uint32_t *) calloc(array_length, sizeof(uint32_t));
            srandom(SEED);
            reset(&stats);
            for (int i = 0; i < array_length; i += 1) {
                A[i] = random() & 0x3FFFFFFF;
            }

            function_pointers[k](&stats, A, array_length);
            switch (k) {
            case INSERT:
                printf("Insertion(%d) = %lu moves, ", array_length,
                    stats.compares);
                break;
            case HEAP:
                printf("Heap(%d) = %lu moves, ", array_length,
                    stats.compares);
                break;
            case SHELL:
                printf("Shell(%d) = %lu moves, ", array_length,
                    stats.compares);
                break;
            case QUICK:
                printf("Quick(%d) = %lu moves\n", array_length,
                    stats.compares);
                break;

            case HELP: printf("This shouldn't be happening. Like at all"); break;
            
	    }

  	free(A);
	
          
        }
    }
}
}
