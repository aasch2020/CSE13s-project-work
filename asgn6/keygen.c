#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"
int main() {
    //	printf("main");
    randstate_init(11239);

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
    mpz_init_set_ui(prm, 0);
    //  printf("is prime %d\n", is_prime(prm, 100));
    int x = 1;
    bool check = false;
    mpz_t ta, tb, tc, td, tf;
    mpz_inits(ta, tb, tc, td, tf, NULL);
    for (int i = 0; i < 100; i++) {
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
            printf("error at %d\n", i);
            printf("check is %d\n", check);
        }
        mpz_add_ui(prm, prm, 1);
    }
    //  mpz_set(prm, 1);
    //  is_prime(prm, 25);
    // randstate_clear();
    mpz_t prime;
    mpz_init(prime);
    for (int i = 0; i < 10; i++) {
        make_prime(prime, 100, 150);
        gmp_printf("%Zd is a prime\n", prime);
    }
    mpz_t p, q, n, e;
    mpz_inits(p, q, n, e, NULL);
    rsa_make_pub(p, q, n, e, 100, 100);
    FILE *file;
    file = fopen("outs.txt", "r");
    FILE *filel;
    filel = fopen("out1.txt", "w");
    // char as[] = "asdf";
    // rsa_read_pub(n, e, a, as, file);
    // rsa_write_pub(n, e, a, as, filel);
    rsa_encrypt_file(file, filel, n, e);
    mpz_clears(a, b, c, d, f, prm, NULL);
}
