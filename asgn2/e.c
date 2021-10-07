#include <stdio.h>
#include <math.h>
#include "mathlib.h"
static int counter = 0;
double e()
{
    double eout = 0.0;
    double prev = 1.0;
    while (prev > EPSILON){
        eout+=prev;
        counter++;
        prev=prev*(1.0/counter);
    }
   // printf("%16.15lf\n", eout);
   // printf("%f", M_E);
   return eout;
}
int e_terms(){
	return counter;
}	
