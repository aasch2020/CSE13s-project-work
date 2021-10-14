
#include "mathlib.h"
#include <math.h>
#include <stdio.h>
static int counter = 1;
// This function returns pi calculated via the madhava series.
// Takes no inputs.
double pi_madhava() {
    double sum = 0.0;
    double term = 1.0;
    counter = 1;
    //Since term can be negative in this case, as the terms are multiplied each time by a negative
    //The absolute value of the term is used to calculate the loop condition
    //The first term in the series is 1, thus the counter and sum and term begin at 1
    //the term is the previous term times -3 divided by the non exponential part of the previous term
    //and then multiplied by the non exponential part of the current term.
   // while (absolute(term) > EPSILON) {
   for (int i = 0; i < 30; i++) {
        printf("e() = %16.15lf, M_E = %16.15lf, why is this rand num\n", sum * sqrt_newton(12), M_PI);

	sum += term;
        term *= (1 / -3.0) * (2 * (counter - 1) + 1) / ((2 * counter + 1));
        
        counter++;
    }
    //the sum is multiplied by square root of 12, since pi is equal to the summation times 12
    sum *= sqrt_newton(12);

    return sum;
}
//This function return the number of terms of the madhava series calculation.
//Must run the madhava series first to return reasonable data.
int pi_madhava_terms() {
    return counter;
}
