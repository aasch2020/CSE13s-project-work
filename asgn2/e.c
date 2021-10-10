#include "mathlib.h"

#include <stdio.h>
static int counter = 1;
double e() {
    double eout = 1.0;
    double prev = 1.0;
    counter = 1;
    while (prev > EPSILON) {
        prev = prev * (1.0 / counter);
        eout += prev;
        counter++;
    }
    // printf("%16.15lf\n", eout);
    // printf("%f", M_E);
    return eout;
}
int e_terms() {
    return counter;
}
