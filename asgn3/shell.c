#include "stats.h"
//The stats header file is given by Professor Long in the resources repo (2021 Professor Long)

#include <math.h>

//the below code is adapted off of the python code given in the assignment document. (2021 Professor Long)

//The below function takes a stats struct, a list of uint32_t A, and the index of the end of the array n/
//This sorts the array by using a shell_sort method. a method in which a value is compared to and sorted by value of given gap length away,
//with gap gradually decreasing to 1, thus sorting the array.
void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t starting_gap_calculation_value = log(3 + (2 * n)) / log(3);
    uint32_t gap = ((pow(3, starting_gap_calculation_value) - 1));
    //This above code initializes the first gap value. After which, the decrease in gap can be iteratively caluclated
    //
    //The below loop loops through the gap values, and then sorts in another internal loop.
    for (uint32_t k = starting_gap_calculation_value; k > 0; k--) {
        uint32_t j = 0;
        uint32_t temp = 0;

        //This loop iterates through all elements from the gap value to the end of the array
        for (uint32_t i = (gap / 2); i < n; i++) {
            j = i;
            temp = move(stats, A[i]);
            //This loop compares the current value to all elements within gap distance of it,
            //then moves the comparing elements right by until the current element is not less than the element to it's right.
            while ((j >= (gap / 2)) && ((cmp(stats, temp, A[j - (gap / 2)]) == -1))) {
                A[j] = move(stats, A[j - (gap / 2)]);
                j -= (gap / 2);
            }
            A[j] = move(stats, temp);
            //By moving the current value to the current found index, the function places the current value back in after the right shift.
            //This is effectively an insertion sort by gap value instead of 1
        }
        gap = (gap - 1) / 3;
        //Decrement the gap value
    }
    return;
}
