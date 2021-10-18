#include "stats.h"
//The stats header file is given by Professor Long in the resources repo (2021 Professor Long)

#include <math.h>

//the below code is adapted off of the python code given in the assignment document. (2021 Professor Long)

//This function takes a stats structure, an array of uint_32t, with both the low and high indeces of the array.
//The below function takes an array, and using a pivot,  creates two arrays
//The two arrays are created in a way that the left array contains all values less than pivot, and the right is all values greater than.
//This function returns the index of the division of the two arrays
uint32_t partition(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    uint32_t i = low - 1;
    //This loops over the array from the start to end, and if the current value is greater than the last
    //Swaps the value at the pivot and the current index
    //It then increments the pivot by one.
    for (uint32_t j = low; j < high; j++) {
        if (cmp(stats, A[j - 1], A[high - 1]) == -1) {
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[high - 1]);
    return i + 1;
}

//This function takes a stats struct, an array of unit32_t, and indices of unit32_t indicating the beginning and end of the array.
//This first paritions the array into two sub arrays, where everything to the left array is smaller than pivot, and to the right array is greater than
//This function then calls itself on the two sublists, and repeats until there is a list of length one,which is sorted.
void quick_sorter(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    if (low < high) {
        uint32_t p = partition(stats, A, low, high);
        quick_sorter(stats, A, low, p - 1);
        quick_sorter(stats, A, p + 1, high);
    }
    return;
}
//This function takes a stats struct, an array of uin32_t, and the index of the end of the array n
//Thi function is the start for the above recursive function, and intializes the value of the first index.
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
    return;
}
