
#include "mathlib.h"

#include <stdio.h>
static int counter = 1;
//This function takes no inputs, and calculates pi using the Bailey-Borwin_Plouffe formula in Horner normal form
double pi_bbp() {
    //This calculates the summation from the first term, by inputting the first term directly into
    //sum and term, since term is calculated partially based on previous term
    double sum = 47.0 / 15;
    double term = 47.0 / 15;
    counter = 1;
    while (term > EPSILON) {
        //This below calcuation for term multiplies the term by 16, then divides by the non exponential
        //portion of the previous term, and then multiplies by the non exponential portion of the current term
        //This is in horner normal form.
        term = term * (1 / 16.0)
               * ((counter * (120.0 * counter + 151.0) + 47.0)
                   / (counter * (counter * (counter * (512.0 * counter + 1024.0) + 712.0) + 194.0)
                       + 15.0))
               * (((counter - 1.0)
                          * ((counter - 1.0)
                                  * ((counter - 1.0) * (512.0 * (counter - 1.0) + 1024.0) + 712.0)
                              + 194.0)
                      + 15.0)
                   / ((counter - 1.0) * (120.0 * (counter - 1.0) + 151.0) + 47.0));
        counter++;
        sum += term;
    }
    return sum;
}
//This function returns the number of terms used by pi_bbp(). Requires pi_bbp to be run once before it.
int pi_bbp_terms() {
    return counter;
}
