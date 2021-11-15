#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"
#include <stdlib.h>
#include <inttypes.h>
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    srandom(124);
    uint64_t p_bit_cnt = ((random() % ((nbits / 2))) + (nbits / 4));
    uint64_t q_bit_cnt = nbits - p_bit_cnt;
    //  printf("%"PRIu64", %"PRIu64"\n", p_bit_cnt, q_bit_cnt);
    make_prime(p, p_bit_cnt, iters);
    //  printf("here\n");
    make_prime(q, q_bit_cnt, iters);
    mpz_t totient;
    mpz_init(totient);
    mpz_mul(n, p, q);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(totient, p, q);
    mpz_add_ui(p, p, 1);
    mpz_add_ui(q, q, 1);
    mpz_t g;
    mpz_init(g);
    bool exp_found = false;
    //   printf("asdf\n");
    while (!exp_found) {
        mpz_urandomb(e, state, nbits);
        gcd(g, e, totient);
        if (mpz_cmp_ui(g, 1) == 0) {
            //	gmp_printf("%Zd, %Zd, %Zd\n", g, e, n);
            exp_found = true;
        }
    }
    mpz_clear(totient);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zxd\n", n);
    gmp_fprintf(pbfile, "%Zxd\n", e);
    gmp_fprintf(pbfile, "%Zxd\n", s);
    fprintf(pbfile, "%s\n", username);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zxd", n);
    gmp_fscanf(pbfile, "%Zxd", e);
    gmp_fscanf(pbfile, "%Zxd", s);
    fscanf(pbfile, "%s", username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t totient;
    mpz_init(totient);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(totient, p, q);
    mpz_add_ui(p, p, 1);
    mpz_add_ui(q, q, 1);

    mod_inverse(d, e, totient);
    mpz_clear(totient);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zxd\n", n);
    gmp_fprintf(pvfile, "%Zxd\n", d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zxd", n);
    gmp_fprintf(pvfile, "%Zxd", d);
}
void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n);

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e);

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n);

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d);

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n);

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n);
