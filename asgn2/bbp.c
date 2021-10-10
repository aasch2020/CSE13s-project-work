#include "mathlib.h"

#include <stdio.h>
static int counter = 1;
double pi_bbp() {
    double sum = 47.0 / 15;
    double term = 47.0 / 15;
    counter = 1;
    while (term > EPSILON) {
         term = term * (1 / 16.0)
               * ((counter * (120.0 * counter + 151.0) + 47.0)
                   / (counter * (counter * (counter * (512.0 * counter + 1024.0) + 712.0) + 194.0)
                       + 15.0))
               * (((counter - 1.0)
                          * ((counter - 1.0)
                                  * ((counter - 1.0) * (512.0 * (counter - 1.0) + 1024.0) + 712.0)
                              + 194.0) + 15.0)
                   / ((counter - 1.0) * (120.0 * (counter - 1.0) + 151.0) + 47.0));
        counter++;
        sum += term;
   }
    return sum;
}
int pi_bbp_terms() {
    return counter;
}
