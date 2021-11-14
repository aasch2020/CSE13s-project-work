#include "randstate.h"
#include "numtheory.h"
int main() {
    //	printf("main");
    randstate_init(123);
    mpz_t a, d, b, c, f, prm;
    mpz_inits(a, d, b, c, f, prm, NULL);
    mpz_set_ui(a, 64);
    mpz_set_ui(b, 24);
    mpz_set_ui(c, 17);
    gcd(d, a, b);
    gmp_printf("The thing %Zd\n", d);
    pow_mod(d, a, b, c);
    gmp_printf("The thing pow %Zd\n", d);
    mpz_set_ui(d, 9);
    mpz_set_ui(c, 64);
    mod_inverse(f, d, c);
    gmp_printf("The thing modinv %Zd\n", f);
    mpz_init_set_ui(prm, 66);
    printf("is prime %d\n", is_prime(prm, 25));
    randstate_clear();
    mpz_clears(a,b,c,d,f, prm,  NULL);

}
