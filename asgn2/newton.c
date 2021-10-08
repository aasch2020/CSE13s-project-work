#include "mathlib.h"

#include <math.h>
#include <stdio.h>
static int counter = 0;
double sqrt_newton(double input) {
    double previous = 0.0;
    double guess = 1.0;
    while (absolute(guess - previous) > EPSILON) {
        counter++;
        previous = guess;
        guess = 0.5 * (previous + (input / previous));
    }
    return guess;
}
int sqrt_newton_iters() {
    return counter;
}
