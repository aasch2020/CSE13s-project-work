#include "stats.h"
//stats.h is supplied by Professor Long in the resources repositoty (2021 Professor Long)
#include <stdbool.h>

//This code is inspired by the python Python code in the Assignment document posted by Professor Long (2021 Professor Long)

//The evaluation of indices in this program is done assuming 1 based indexing.
//Thus, 1 is subtracted from all indices when used to get values from the array.

//This function takes a stats struct, an Array of uint32_t, a parent index of uint32_t, and a last index of type uint32_t
//It finds the largest child value of the given parent index.
uint32_t maximum_child(Stats *stats, uint32_t *A, uint32_t parent_index, uint32_t last) {
    uint32_t left = 2 * parent_index;
    uint32_t right = left + 1;
    //This statement makes sure that the right child is not off of the end of the list, and greater than the left child.
    if ((right <= last) && (cmp(stats, A[right - 1], A[left - 1]) == 1)) {
        return right;
    } else {
        return left;
    }
}

//This function takes a stats structe, an array of uint32_t, and a first and last index, both of type uint32_t.
//This function makes the roots of the parent value given by first index follow the max heap constraints
//This means for each element x  between the start and the end / 2, both A[x*2] and A[x*2+1} are less than x

void fix_heap(Stats *stats, uint32_t *A, uint32_t first_index, uint32_t last) {
    bool fixed = false;
    uint32_t parent = first_index;
    uint32_t greatest_child = maximum_child(stats, A, parent, last);

    //This loop iterate through the children of the given parent value.
    //This loop stops iteration, when either the given parent has both children less than it,
    //or if the given parent is the last parent value
    //In essence, this loop makes sure that all of the children of a parent node follow max heap constraints

    while ((parent <= (last / 2)) && !(fixed)) {
        if (cmp(stats, A[parent - 1], A[greatest_child - 1]) == -1) {

            swap(stats, &A[parent - 1], &A[greatest_child - 1]);

            parent = greatest_child;
            greatest_child = maximum_child(stats, A, parent, last);
        } else {
            fixed = true;
        }
    }
    return;
}

//This function takes a stats struct, an array of uint32_t, and two indexes of first and last, both of type uint32_t
//This function takes an unordered array and makes a max heap
//This is achieved by calling fix_heap on all parent value in a reverse order.

void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t i = (last / 2); i >= first; i--) {

        fix_heap(stats, A, i, last);
    }
    return;
}

//This function takes a stats struct, an array of uint32_t A, and uint32_t of the last index
//This function sorts an array using heap sort.

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first_ind = 1;
    uint32_t last = n;
    build_heap(stats, A, first_ind, n);
    //This calls the build heap function, thus making the array a max heap
    //
    //The below loop loops through the array from last to first, swapping the two values each iteration
    //In essence, this loop takes the first index, which in a max heap is the greatest value, and moves it to the end
    //It then fixes the heap, by fixing all the children of the new first index, and then iterates again.
    //Each iteration, it ignores the last value, effecfively shrinking the heap by one each time, and creating a sorted array.
    for (uint32_t i = last; i > first_ind; i--) {

        swap(stats, &A[first_ind - 1], &A[i - 1]);

        fix_heap(stats, A, first_ind, (i - 1));
    }
    return;
}
