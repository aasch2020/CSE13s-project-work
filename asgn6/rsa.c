#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"
#include "time.h"
#include <stdlib.h>
#include <inttypes.h>
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    srandom(time(NULL));

    uint64_t p_bit_cnt = ((random() % ((nbits / 2))) + (nbits / 4));
    uint64_t q_bit_cnt = nbits - p_bit_cnt;
    // printf("%" PRIu64 ", %" PRIu64 "\n", p_bit_cnt, q_bit_cnt);
    make_prime(p, p_bit_cnt, iters);
    //  printf("here\n");
    make_prime(q, q_bit_cnt, iters);

    mpz_t totient;
    mpz_init(totient);
    mpz_mul(n, p, q);
    //    printf("size of n %lu\n", mpz_sizeinbase(n, 2));
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
    mpz_clears(g, totient, NULL);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n%Zx\n%Zx\n", n, e, s);
    fprintf(pbfile, "%s\n", username);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx", n);
    gmp_fscanf(pbfile, "%Zx", e);
    gmp_fscanf(pbfile, "%Zx", s);
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
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx", n);
    gmp_fscanf(pvfile, "%Zx", d);
}
void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    uint64_t blocksize = (mpz_sizeinbase(n, 2) - 1) / 8;
    //    printf("%lu blk \n", blocksize);
    uint8_t *block = (uint8_t *) calloc(blocksize, sizeof(uint8_t));
    block[0] = 0xFF;
    uint64_t readcount;
    bool all_read = false;
    mpz_t impout, ciphertxt;
    mpz_inits(impout, ciphertxt, NULL);
    while (!all_read) {
        readcount = fread(block + 1, 1, blocksize - 1, infile);
        // printf("%lu readcn \n", readcount);
        if (readcount == 0) {
            //          printf("eof\n");
            all_read = true;
            break;
        }

        mpz_import(impout, readcount + 1, 1, 1, 1, 0, block);
        //       gmp_printf("%Zx\n", impout);

        rsa_encrypt(ciphertxt, impout, e, n);
        //     gmp_printf("%Zx\n", ciphertxt);

        gmp_fprintf(outfile, "%Zx\n", ciphertxt);
    }
    free(block);
    mpz_clears(impout, ciphertxt, NULL);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    uint64_t blocksize = (mpz_sizeinbase(n, 2) - 1) / 8;
    uint8_t *block = (uint8_t *) calloc(blocksize, sizeof(uint8_t));
    bool all_read = false;
    int32_t readcount;
    uint64_t writecount;
    mpz_t in, msg;
    mpz_inits(in, msg, NULL);
    while (!all_read) {
        readcount = gmp_fscanf(infile, "%Zx", in);
        if (readcount == -1) {

            break;
        }
        // fprintf(outfile, "read %d\n", readcount);
        // mpz_import(in, readcount - 1, 1, 1, 1, 0, block);
        //      gmp_printf("hexin %Zx\n", in);
        rsa_decrypt(msg, in, d, n);
        writecount = mpz_sizeinbase(msg, 8);
        //	printf("amt to write %d writecount\n", writecount);
        mpz_export(block, &writecount, 1, 1, 1, 0, msg);

        fwrite(block + 1, 1, writecount - 1, outfile);
    }
    free(block);
    mpz_clears(in, msg, NULL);
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n);
    if (mpz_cmp(m, t) == 0) {
        mpz_clear(t);
        return true;
    }
    mpz_clear(t);
    return false;
}
