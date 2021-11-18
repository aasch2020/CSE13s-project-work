
#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"
//The above header files provided in the resources repository by Professor Long (2021 Professor Long)
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#define OPTIONS "hvi:n:o:"

//This main function takes command line arguments, and encrypts a given file with a given public key.
int main(int argc, char **argv) {
    // The below code parses command line arguments,
    // It prints the appropriate help message if the h input is given
    // It also sets the input and output files, and the key file, and errors if any of these files could not be opened.
    // It also checks for verbose output and set the boolean as appropriate.

    int opt = 0;

    FILE *pubkey;
    FILE *input = stdin;
    FILE *output = stdout;
    bool verb = false;
    bool isinfile = false;
    bool isoutfile = false;
    bool ispubkey = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("help\n");
            if (isinfile) {
                fclose(infile);
            }
            if (ispubkey) {
                fclose(pubkey);
            }
            if (isoutfile) {
                fclose(outfile);
            }

            return 0;
            break;
        case 'v': verb = true; break;
        case 'o':
            output = fopen(optarg, "w");
            if (!output) {
                printf("Failed to open output\n");
                if (isinfile) {
                    fclose(infile);
                }
                if (ispubkey) {
                    fclose(pubkey);
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
                    fclose(outfile);
                }
                if (isinfile) {
                    fclose(infile);
                }

                return -1;
            }

            isinfile = true;
            break;
        case 'n':
            pubkey = fopen(optarg, "r");
            if (!pubkey) {
                printf("Failed to open public key\n");
                if (isoutfile) {
                    fclose(outfile);
                }
                if (ispubkey) {
                    fclose(pubkey);
                }

                return -1;
            }
            ispubkey = true;

            break;
        }
    }

    //This below code checks if the public key has been opened, if not, opens it as the default of rsa.pub.
    if (!ispubkey) {
        pubkey = fopen("rsa.pub", "r");
    }

    //This below code reads the public key, and sets the n, e, and s variables as appropriate, and reads the username.
    mpz_t n, e, s, user;
    mpz_inits(n, e, s, user, NULL);
    char uname[500] = { 0 };
    rsa_read_pub(n, e, s, uname, pubkey);
    mpz_set_str(user, uname, 62);
    //Prints verbose output if specified
    if (verb) {
        printf("user = %s\n", uname);
        gmp_printf("s (%lu bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_printf("n (%lu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_printf("e (%lu bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }

    //This code checks if the username could be verified with given signature, and exits if it cannot be.
    if (!rsa_verify(user, s, e, n)) {
        printf("Could not verify signature with user, exiting\n");
        fclose(pubkey);
        mpz_clears(n, e, s, user, NULL);
        if (isoutfile) {
            fclose(output);
        }
        if (isinfile) {
            fclose(input);
        }

        return -1;
    }
    //This code encrypts the given input file into the output file.
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
