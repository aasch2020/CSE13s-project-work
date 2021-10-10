#include "mathlib.h"

#include <stdio.h>
static int counter = 0;
double pi_viete() {
    double eout = 1.0;
    double prev = sqrt_newton(2.0);
    counter = 0;
    while (absolute(2 / prev - 1) > EPSILON) {
        eout *= 2.0 / prev;
        prev = sqrt_newton(2.0 + prev);
        counter++;
    }
    return 2 * eout;
}
int pi_viete_factors() {
    return counter;
}
