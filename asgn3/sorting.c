#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"
//All of the above header files are provided by Professor Long in the resources repository (2021 Professor Long)
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "haeisqn:p:r:"
typedef enum { HEAP, SHELL, INSERT, QUICK, HELP } possible_args;
//The main function takes command line arguments for input, and is the testing harness for the sortin algorithm
int main(int argc, char **argv) {
    Set input_args = 0;
    int opt = 0;
    unsigned int SEED = 13371453;
    int print = 100;
    int array_length = 100;
    //this loop and switch takes the input options, and if the option is am argument to perform a sort, adds it to the set of sorting.
    //If the argument has a number as well, in the case of n, p, and s, the switch statement, the loop checks for valid values, and sets those values.
    //This code is inspired by both the set.h header file in the resources repo, and the assignment 2 pdf of getting user input (2021 Professor Long)
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {
        case 'n':
            array_length = strtoul(optarg, NULL, 10);
            if (array_length < 0) {
                printf("Invalid array_length, using 100\n");
                array_length = 100;
            }
            break;
        case 'p':
            print = strtoul(optarg, NULL, 10);
            if (print <= 0) {
                printf("Invalid number of elements to print, using 100\n");
                print = 100;
            }
            break;
        case 'r': SEED = strtoul(optarg, NULL, 10); break;
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
    //This below method of using a enumerated type to loop through, and a list of function pointers is inspired by
    //code posted by Professor Long (2021 Professor Long)
    //initializes a list of the function pointers for the sorting functions
    void (*function_pointers[])() = { heap_sort, shell_sort, insertion_sort, quick_sort };
    print = print > array_length ? array_length : print;
    //a ternary oprator that sets the value of numbers to print equal to the length of the array, if it is greater than the length of the array
    if (input_args == 0) {
        input_args = insert_set(HELP, input_args);
        printf("Select at least one sort to perform.\n");
    }
    //The program shows an error message if there are no input arguments
    if (member_set(HELP, input_args)) {
        printf("SYNOPSIS\n   A collection of comparison-based sorting algorithms.\n\nUSAGE\n   "
               "./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
        printf("OPTIONS\n   -h              display program help and usage.\n   -a              "
               "enable all sorts.\n   -e              enable Heap Sort.\n   -i              enable "
               "Insertion Sort.\n   -s              enable Shell Sort.\n   -q              enable "
               "Quick Sort.\n   -n length       specify number of array elements (default: 100).\n "
               "  -p elements     specify number of elements to print (default: 100).\n   -r seed  "
               "       specify random seed (default: 13371453).\n");
        input_args = empty_set();
    }
    //The program shows a help and usage text when -h is used.
    Stats stats;
    //This loop loops thoough the enumeration, which contains all available function names, then, if that value is also found in the set of input functions,
    //it will run a test with the given function.
    for (possible_args k = HEAP; k <= QUICK; k++) {
        if (member_set(k, input_args)) {
            uint32_t *A = (uint32_t *) calloc(array_length, sizeof(uint32_t));
            srandom(SEED);
            reset(&stats);
            for (int i = 0; i < array_length; i += 1) {
                A[i] = random() & 0x3FFFFFFF;
            }
            //The above lines allocated an array of uint32_t with a length of the given input length, seeds the rng,
            //and resets the stats struct so that both omves and compares are zero.
            //it then fills the allocated array with random numbers, bit masked to a size of 30 bits.
            function_pointers[k](&stats, A, array_length);
            //This callls the sorting function specified.
            switch (k) {
                //This switch statement prints the name, number of element, number of moves, and number of compares for the sorting functions.
            case INSERT:
                printf("Insertion Sort, %d elements, %lu moves, %lu compares\n", array_length,
                    stats.moves, stats.compares);
                break;
            case HEAP:
                printf("Heap Sort, %d elements, %lu moves, %lu compares\n", array_length,
                    stats.moves, stats.compares);
                break;
            case SHELL:
                printf("Shell Sort, %d elements, %lu moves, %lu compares\n", array_length,
                    stats.moves, stats.compares);
                break;
            case QUICK:
                printf("Quick Sort, %d elements, %lu moves, %lu compares\n", array_length,
                    stats.moves, stats.compares);
                break;

            case HELP: printf("This shouldn't be happening. Like at all"); break;
            }
            for (int i = 0; i < print; i += 1) {
                if (((i % 5) == 0) && (i > 0)) {
                    printf("\n");
                }
                printf("%13" PRIu32, A[i]);
            }
            //This prints the now sorter array iteratively.
            printf("\n");
            free(A);
            //this frees the memory allocated for the array
        }
    }
    return 0;
}
