#include "mathlib.h"

#include <stdio.h>
static int counter = 0;
//This function estimates pi using Viete's method of repeated multiplication, and takes no input.
double pi_viete() {
    double result = 1.0;
    double guess = 0.0;
    counter = 0;
    //Since the function is multiplied by 2 over the guess to iterate, the condition compared to EPSILON
    //is 2/guess minus one, since the term converges to one.
    while (absolute(2.0 / guess - 1.0) > EPSILON) {
        guess = sqrt_newton(2.0 + guess);
        result *= 2.0 / guess;
        counter++;
    }
    //using the transformation outlined in the design document, pi is 2 times the repeated multiplication
    //thus 2 is multiplied before returning the result.
    return 2 * result;
}
//This returns the number of factors used in the pi_viete() function
//Takes no input and need pi_viete() to be run prior to return meaningful values.
int pi_viete_factors() {
    return counter;
}
