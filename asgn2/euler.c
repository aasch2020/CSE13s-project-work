#include "mathlib.h"

#include <stdio.h>
static int counter = 0;
double pi_euler() {
    double output = 0;
    double term = 1.0;
    counter = 0;
    while (term > EPSILON) {
        term = 1.0 / ((counter + 1.0) * (counter + 1.0));
        output += term;
        counter++;
    }
    return sqrt_newton(6 * output);
}
int pi_euler_terms() {
    return counter;
}
