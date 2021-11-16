#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#define OPTIONS "hvi:n:o:"

int main(int argc, char **argv) {
    // The below code parses command line arguments,
    // It prints the appropriate help message if the h input is given
    // It also sets the input and output files if they are given, and errors if the infile is invalid.

    int opt = 0;

    FILE *privkey;
    FILE *input = stdin;
    FILE *output = stdout;
    bool verb = false;
    bool isinfile = false;
    bool isoutfile = false;
    bool isprivkey = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("help\n");

            return 0;
            break;
        case 'v': verb = true; break;
        case 'o':
            output = fopen(optarg, "w");
            isoutfile = true;
            break;
        case 'i':
            input = fopen(optarg, "r");
            isinfile = true;
            break;
        case 'n':
            privkey = fopen(optarg, "r");
            isprivkey = true;
            if (!privkey) {
                printf("Failed to open private key\n");
                fclose(privkey);
                return -1;
            }
            break;
        }
    }
    if (!isprivkey) {
        privkey = fopen("rsa.priv", "r");
    }

    mpz_t n, d;
    mpz_inits(n, d, NULL);
    rsa_read_priv(n, d, privkey);
    if (verb) {
        gmp_printf("n (%lu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("d (%lu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    rsa_decrypt_file(input, output, n, d);
    fclose(privkey);
    mpz_clears(n, d, NULL);
    if (isoutfile) {
        fclose(output);
    }
    if (isinfile) {
        fclose(input);
    }
}
