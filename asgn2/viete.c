#include "mathlib.h"

#include <stdio.h>
static int counter = 0;
double pi_viete() {
    double eout = 1.0;
    double prev = 0.0;
    counter = 0;
    while (absolute(2.0 / prev - 1.0) > EPSILON) {
        prev = sqrt_newton(2.0 + prev);
        eout *= 2.0 / prev;
        counter++;
    }
    return 2 * eout;
}
int pi_viete_factors() {
    return counter;
}
