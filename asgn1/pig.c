#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "names.h"
int main(){
    printf("%s", "How many players? ");
    int input;
    scanf("%d", &input);
    if((input<2)||(input>10)){
	    fprintf(stderr,"Invalid number of players. Using 2 instead.\n");
	    input = 2;
    
    }
    printf("%s","Random Seed: ");
    long int seed = -1;
    scanf("%ld", &seed);
    if((seed<0)||(seed>UINT_MAX)){
	    fprintf(stderr,"Invalid random seed. Using 2021 instead.\n");
	    seed = 2021;
    }
    srandom(seed);


}
