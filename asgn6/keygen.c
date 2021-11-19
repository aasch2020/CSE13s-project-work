#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"
//The above header files provided in the resources respository by Professor Long(2021 Professor Long)
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#define OPTIONS "hvb:i:n:d:s:"
#include <string.h>

//This function takes in command line arguments, and generates rsa public and private key pair.
int main(int argc, char **argv) {
    // The below code parses command line arguments,
    // It prints the appropriate help message if the h input is given
    // It also sets the public and private key files, the number of bits and the number of iterations.
    int bitcnt = 256;
    int opt = 0;
    int iters = 50;
    FILE *pubkey;
    bool ispubkey = false;
    FILE *privkey;
    bool isprivkey = false;
    bool verb = false;
    bool initgiv = false;
    uint64_t seed = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n   Generates an RSA public/private key pair.\n\nUSAGE\n   ./keygen "
                   "[-hv] [-b bits] -n pbfile -d pvfile\n\n");
            printf("OPTIONS\n   -h              Display program help and usage.\n   -v             "
                   " Display verbose program output.\n");
            printf("   -b bits         Minimum bits needed for public key n (default: 256).\n");
            printf(
                "   -i confidence   Miller-Rabin iterations for testing primes (default: 50).\n");
            printf("   -n pbfile       Public key file (default: rsa.pub).\n");
            printf("   -d pvfile       Private key file (default: rsa.priv).\n");
            printf("   -s seed         Random seed for testing\n");
            if (isprivkey) {
                fclose(privkey);
            }
            if (ispubkey) {
                fclose(pubkey);
            }

            return 0;
            break;
        case 'v': verb = true; break;
        case 'b': bitcnt = strtoul(optarg, NULL, 10); break;
        case 'i': iters = strtoul(optarg, NULL, 10); break;
        case 'n':
            pubkey = fopen(optarg, "w");
            if (!pubkey) {
                printf("Failed to open public key\n");
                if (isprivkey) {
                    fclose(privkey);
                }
                return -1;
            }

            ispubkey = true;

            break;
        case 'd':
            privkey = fopen(optarg, "w");
            if (!privkey) {
                if (ispubkey) {
                    fclose(pubkey);
                }
                printf("Failed to open private key\n");
                return -1;
            }
            isprivkey = true;
            break;
        case 's':
            initgiv = true;
            seed = strtoul(optarg, NULL, 10);
            break;
        }
    }
    //The below code  Opens public and private keys as default values if they are not given
    if (!isprivkey) {
        privkey = fopen("rsa.priv", "w");
    }
    if (!ispubkey) {

        pubkey = fopen("rsa.pub", "w");
    }

    //The below code intializes randstate with the given seed, if a seed is not given, seed with time(NULL)
    if (!initgiv) {
        randstate_init(seed);
    } else {
        randstate_init(time(NULL));
    }
    //The below code sets the permissions on the private key to read and write for current user only.
    int filenum = fileno(privkey);
    fchmod(filenum, 0600);

    //The below code generates public and private keys with nbits beign the number of bits of n, and iters being Miller Rabin iterations
    mpz_t p, q, n, e, d, s, u;
    mpz_inits(p, q, n, e, d, s, u, NULL);
    rsa_make_pub(p, q, n, e, bitcnt, iters);
    rsa_make_priv(d, e, p, q);
    //Gets the current username as a string using getenv, converts the username to an mpz_t, and performs rsa_signing with the given username
    char *uname = getenv("USER");
    mpz_set_str(u, uname, 62);
    rsa_sign(s, u, d, n);
    //Write the public and private key to the given output files, and prints verbose output if so specified.
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
    return 0;
}
