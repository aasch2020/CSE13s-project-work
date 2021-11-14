#include "randstate.h"
#include "numtheory.h"
int main() {
    //	printf("main");
    randstate_init(1123984);
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
    mpz_init_set_ui(prm, 8);
    printf("is prime %d\n", is_prime(prm, 25));
    int x = 1;
    bool check = false;
    mpz_t ta, tb, tc, td, tf;
    mpz_inits(ta, tb, tc, td, tf, NULL);
    for (int i = 0; i < 100000; i++) {
        mpz_urandomb(ta, state, 150);
        mpz_set_ui(tb, 2);
        mpz_urandomb(tc, state, 150);
        mpz_powm(tf, ta, tb, tc);
        pow_mod(td, ta, tb, tc);
        if (mpz_cmp(td, tf) != 0) {
            printf("pow_mod err\n");
        }
        check = is_prime(prm, 150);
        x = mpz_probab_prime_p(prm, 150);
        if ((x != 0) != (check != 0)) {
            printf("error at %d\n", i + 8);
            printf("check is %d\n", check);
        }
        mpz_add_ui(prm, prm, 1);
    }

    is_prime(prm, 25);
    randstate_clear();
    mpz_clears(a, b, c, d, f, prm, NULL);
}
