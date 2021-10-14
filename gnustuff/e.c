
#include "mathlib.h"

#include <math.h>
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
    // while (guess > EPSILON) {
    for (int i = 0; i < 20; i++) {
        printf("e() = %16.15lf, M_E = %16.15lf, asdf = %16.15lf\n", guess, EPSILON, M_E);
        guess = guess * (1.0 / counter);
        sum += guess;
        counter++;
    }

    return sum;
}
//This returns the number of terms used to calculate e. It takes no input, and needs e() to be run first.
int e_terms() {
    return counter;
}
