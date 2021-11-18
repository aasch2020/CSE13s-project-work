#include "randstate.h"
//The above header file(s) provided in the resources repository by Professor Long (2021, Professor Long).

//The function takes an argument for a random seed, and initializes a random state using the Mersenne twister algorithm with the given seed.
gmp_randstate_t state;
void randstate_init(uint64_t seed) {
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
    return;
}

//This function takes no values, and calls the gmp randclear function to clear the currently initialized random state.
void randstate_clear(void) {
    gmp_randclear(state);
    return;
}
