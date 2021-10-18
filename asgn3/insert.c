#include "stats.h"
//stats.h header provided by Professor Long (2021 Professor Long)

//This code is inspired by the Python code provided by Professor Long in the assignment pdf (2021 Professor Long)

//The below function take a stats struct, and array of uint32_t, and the last index of the array also of uint32_t
//This function implements insertion sort to sort the given array.
//In essence, this function goes through the list value by value, and moves the given value left by shifting the array right, until it is sorted
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    //This loop iterates through all indexes, setting a temporaty variable to store it's value.
    for (uint32_t i = 1; i < n; i++) {
        int current_index = i;
        int temporary_var = move(stats, A[i]);
        //This loop then iterates backwards from the current index, moving the values to the right by one.
        //Until the current value is the front of the array, or is greater than the temporary value
        while ((current_index > 0) && (cmp(stats, temporary_var, A[current_index - 1]) == -1)) {
            A[current_index] = move(stats, A[current_index - 1]);
            current_index--;
        }
        A[current_index] = move(stats, temporary_var);
        //This puts the stored temporary value into the current index.
    }
    return;
}
