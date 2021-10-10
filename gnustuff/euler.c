
#include "mathlib.h"

#include <stdio.h>
static int counter = 0;
//This function takes no arguments, and returns pi calculated via the euler method.
double pi_euler() {
    double output = 0;
    double term = 1.0;
    counter = 0;
    //This loop calculates the summation while the term is less than epsilon.
    //The term is calculated using the formula from the assignment sheet
    //The term is 1 divided by the current iteration + 1 squared
    while (term > EPSILON) {
        term = 1.0 / ((counter + 1.0) * (counter + 1.0));
        output += term;
        counter++;
    }
    return sqrt_newton(6 * output);
}
//This function requires pi_euler() to be run first to generate reasonable data
//This function returns the number of terms iterated to calculate pi
int pi_euler_terms() {
    return counter;
}
