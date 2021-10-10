#include "mathlib.h"

#include <stdio.h>
static int counter = 0;
//Calculates the square root using newton's method, takes a double, which is the variable to be calculated
double sqrt_newton(double input) {
    double previous = 0.0;
    double guess = 1.0;
    counter = 0;
    //This loop is the implementation of each iterative guess of the
    // square root being the previous guess subtracted by
    //,the previous guess over the derivative of the previous guess
    while (absolute(guess - previous) > EPSILON) {
        counter++;
        previous = guess;
        guess = 0.5 * (previous + (input / previous));
    }
    return guess;
}
//This returns the number of iterations of the square root newton method, and takes no input
//need sqrt_newton() to be run prior to generate valuable data
int sqrt_newton_iters() {
    return counter;
}
