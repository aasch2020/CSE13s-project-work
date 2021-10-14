#include "heap.h"
#include "insert.h"
#include "shell.h"
#include "stats.h"
#include "quick.h"
#include "set.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#define OPTIONS "haeisqn:p:r:"
typedef enum {INSERT, SHELL, HEAP, QUICK} possible_args;
int main(int argc, char **argv){
	Set input_args = 0;
	int opt = 0;
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        //Loop through all of the command line args and check if they are any of the important values
      	  switch (opt) {
      	  	case 'n': printf("n option %s\n", optarg); break;
       	 	case 'p': printf("p option %s\n", optarg); break;
       		case 'r': printf("r option %s\n", optarg); break;
       		case 'h': printf("da baby yuh\n"); return 0; break;
		case 'i': input_args = insert_set(input_args, INSERT); break;
		case 'e': input_args = insert_set(input_args, HEAP); break;
		case 's': input_args = insert_set(input_args, SHELL); break;
		case 'q': input_args = insert_set(input_args, QUICK); break;
		case 'a': input_args = insert_set(input_args, INSERT); input_args = insert_set(input_args, HEAP); input_args = insert_set(input_args, SHELL); input_args = insert_set(input_args, QUICK); break; 
        	default: printf("how in the heck"); break;
        }
	void (*function_pointers[])() = {insertion_sort, heap_sort, shell_sort, quick_sort};
	for (possible_args k = INSERT; k <= QUICK; k++){
		if (member_set(input_args, k)){
			function_pointers[k]();
		}
	}

	}
}
