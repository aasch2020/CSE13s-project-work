#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#define OPTIONS "hvb:i:n:d:s:"

int main(int argc, char **argv) {
    // The below code parses command line arguments,
    // It prints the appropriate help message if the h input is given
    // It also sets the input and output files if they are given, and errors if the infile is invalid.
    int bitcnt = 256;
    int opt = 0;
    int iters = 50;
    FILE *pubkey = fopen("rsa.pub", "w");
    FILE *privkey = fopen("rsa.priv", "w");
    bool verb = false;
    bool initgiv = false;
    uint64_t seed = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("help\n");
            fclose(pubkey);
            fclose(privkey);

            return -1;
            break;
        case 'v': verb = true; break;
        case 'b': bitcnt = strtoul(optarg, NULL, 10); break;
        case 'i': iters = strtoul(optarg, NULL, 10); break;
        case 'n':
            fclose(pubkey);
            pubkey = fopen(optarg, "w");
            if (!pubkey) {
                printf("Failed to open public key\n");
                fclose(pubkey);
                fclose(privkey);
                return -1;
            }
            break;
        case 'd':
	    fclose(privkey);
            privkey = fopen(optarg, "w");
            if (!privkey) {

                printf("Failed to open private key\n");
                fclose(pubkey);
                fclose(privkey);
                return -1;
            }
            break;
        case 's':
            initgiv = true;
            seed = strtoul(optarg, NULL, 10);
            break;
        }
    }

    if (!initgiv) {
        randstate_init(seed);
    } else {
        randstate_init(time(NULL));
    }

    int filenum = fileno(privkey);
    fchmod(filenum, 0600);
    mpz_t p, q, n, e, d, s, u;
    mpz_inits(p, q, n, e, d, s, u, NULL);
    rsa_make_pub(p, q, n, e, bitcnt, iters);
    rsa_make_priv(d, e, p, q);
    char *uname = getenv("USER");
    mpz_set_str(u, uname, 62);
    rsa_sign(s, u, d, n);

    rsa_write_priv(n, d, privkey);
    rsa_write_pub(n, e, s, uname, pubkey);
    if (verb) {
        printf("user = %s\n", uname);
        gmp_printf("s (%lu bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("p (%lu bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_printf("q (%lu bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_printf("n (%lu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%lu bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
        gmp_printf("d (%lu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }
    fclose(pubkey);
    fclose(privkey);
    mpz_clears(p, q, n, e, d, s, u, NULL);
    randstate_clear();
}
