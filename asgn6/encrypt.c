
#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#define OPTIONS "hvi:n:o:"

int main(int argc, char **argv) {
    // The below code parses command line arguments,
    // It prints the appropriate help message if the h input is given
    // It also sets the input and output files if they are given, and errors if the infile is invalid.

    int opt = 0;

    FILE *pubkey = fopen("rsa.pub", "r");
    FILE *input = stdin;
    FILE *output = stdout;
    bool verb = false;
    bool isinfile = false;
    bool isoutfile = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("help\n");
            fclose(pubkey);

            return 0;
            break;
        case 'v': verb = true; break;
        case 'o':
            output = fopen(optarg, "w");
            isoutfile = true;
            break;
        case 'i':
            input = fopen(optarg, "r+");
            isinfile = true;
            break;
        case 'n':
            fclose(pubkey);
            pubkey = fopen(optarg, "r+");
            if (!pubkey) {
                printf("Failed to open public key\n");
                fclose(pubkey);
                return -1;
            }
            break;
        }
    }
    mpz_t n, e, s, user;
    mpz_inits(n, e, s, user, NULL);
    char uname[500] = { 0 };
    rsa_read_pub(n, e, s, uname, pubkey);
    mpz_set_str(user, uname, 62);
    if (verb) {
         printf("user = %s\n", uname);
        gmp_printf("s (%lu bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("n (%lu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%lu bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }

    if (!rsa_verify(user, s, e, n)) {
        printf("Could not verify signature with user, exiting");
        return -1;
    }
    rsa_encrypt_file(input, output, n, e);
    fclose(pubkey);
    mpz_clears(n, e, s, user, NULL);
    if (isoutfile) {
        fclose(output);
    }
    if (isinfile) {
        fclose(input);
    }
}
