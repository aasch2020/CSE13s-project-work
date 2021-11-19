#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"
//The above header files provided in the resources repository by Professor Long (2021 Professor Long)
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#define OPTIONS "hvi:n:o:"

//The belwo main function decrypts a given file with the given RSa private key
int main(int argc, char **argv) {
    // The below code parses command line arguments,
    // It prints the appropriate help message if the h input is given
    // It also sets the input and output files if they are given, and the private key file, and errors if the files are invalid.
    // It also osets if the verbose output is specified

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
            printf(
                "SYNOPSIS\n   Decrypts data using RSA decryption.\n   Encrypted data is encrypted "
                "by the encrypt program.\n\nUSAGE\n   ./decrypt [-hv] [-i infile] [-o outfile] -n "
                "privkey\n\nOPTIONS\n   -h              Display program help and usage.\n   -v     "
                "         Display verbose program output.\n   -i infile       Input file of data "
                "to decrypt (default: stdin).\n   -o outfile      Output file for decrypted data "
                "(default: stdout).\n   -n pvfile       Private key file (default: rsa.priv).\n");
            if (isoutfile) {
                fclose(output);
            }
            if (isinfile) {
                fclose(input);
            }
            if (isprivkey) {
                fclose(privkey);
            }
            return 0;
            break;
        case 'v': verb = true; break;
        case 'o':
            output = fopen(optarg, "w");
            if (!output) {
                printf("Failed to open output\n");
                if (isinfile) {
                    fclose(input);
                }
                if (isprivkey) {
                    fclose(privkey);
                }
                return -1;
            }
            isoutfile = true;
            break;
        case 'i':
            input = fopen(optarg, "r");
            if (!input) {
                printf("Failed to open input\n");
                if (isoutfile) {
                    fclose(output);
                }
                if (isprivkey) {
                    fclose(privkey);
                }
            }
            isinfile = true;
            break;
        case 'n':
            privkey = fopen(optarg, "r");
            if (!privkey) {
                printf("Failed to open private key\n");
                if (isoutfile) {
                    fclose(output);
                }
                if (isinfile) {
                    fclose(input);
                }
                return -1;
            }

            isprivkey = true;

            break;
        }
    }

    //This code initializes the private key as the default rsa.priv if not specified.
    if (!isprivkey) {
        privkey = fopen("rsa.priv", "r");
    }

    //This code reads the n and d from the private key and prints them if verbose output is specified
    mpz_t n, d;
    mpz_inits(n, d, NULL);
    rsa_read_priv(n, d, privkey);
    if (verb) {
        gmp_printf("n (%lu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("d (%lu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    //this code uses n and d to decrypt the input file to the output file.
    rsa_decrypt_file(input, output, n, d);
    fclose(privkey);
    mpz_clears(n, d, NULL);
    if (isoutfile) {
        fclose(output);
    }
    if (isinfile) {
        fclose(input);
    }
    return 0;
}
