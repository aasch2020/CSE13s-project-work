#include "mathlib.h"

#include <stdio.h>
static int counter = 1;
double pi_madhava() {
    double sum = 1.0;
    double term = 1.0;
    while (absolute(term) > EPSILON) {
        term *= (1 / -3.0) * (2 * (counter - 1) + 1) / ((2 * counter + 1));
        sum += term;
        counter++;
    }
    sum *= sqrt_newton(12);
    return sum;
}
int pi_madhava_terms() {
    return counter;
}
