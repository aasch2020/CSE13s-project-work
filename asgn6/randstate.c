#include "randstate.h"
#include "stdio.h"
#include <gmp.h>

gmp_randstate_t state;
void randstate_init(uint64_t seed){
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, seed);

}


void randstate_clear(void){
	gmp_randclear(state);
}
int main(){
	randstate_init(1);
	int asd = gmp_urandomb_ui(state, 10);
	printf("a is %d", asd);

}

