#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "names.h"
int main(){
    printf("%s", "How many players? ");
    int playercount;
    scanf("%d", &playercount);
    if((playercount<2)||(playercount>10)){
	    fprintf(stderr,"Invalid number of players. Using 2 instead.\n");
	    playercount = 2;
    
    }
    printf("%s","Random Seed: ");
    long int seed = -1;
    scanf("%ld", &seed);
    if((seed<0)||(seed>UINT_MAX)){
	    fprintf(stderr,"Invalid random seed. Using 2021 instead.\n");
	    seed = 2021;
    }
    srandom(seed);
    int currentnum = -1;
    // int scores[10]={0};
    int turnscore=0;
    while(turnscore<100){
        if(currentnum==playercount-1){
	    currentnum = 0;
	}else{
	    currentnum++;
	}
	turnscore += (random() % 20);
	printf("%s rolls the pig...", names[currentnum]);
    }	
}



