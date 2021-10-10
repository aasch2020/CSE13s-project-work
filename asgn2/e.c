
#include "mathlib.h"

#include <stdio.h>
static int counter = 1;
//This function approximates e using a Taylor series, takes no inputs.
double e() {
    double sum = 1.0;
    double guess = 1.0;
    counter = 1;
    // This iterates over the Taylor series, by calculating the next term as the previous term divided
    // by current counter value.
    // It compares the term to epsilon to evaluate when the estimate is good enough
    //Adds to sum every time to calculate summation
    while (guess > EPSILON) {
        guess = guess * (1.0 / counter);
        sum += guess;
        counter++;
    }

    return sum;
}

int e_terms() {
    return counter;
}
