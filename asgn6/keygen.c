#include "randstate.h"
#include "numtheory.h"
int main() {
    //	printf("main");
    mpz_t a, d, b, c, f;
    mpz_inits(a, d, b, c, f, NULL);
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
}
