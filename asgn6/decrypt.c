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

/*int main(int argc, char **argv) {
    // The below code parses command line arguments,
    // It prints the appropriate help message if the h input is given
    // It also sets the input and output files if they are given, and errors if the infile is invalid.

    int opt = 0;

    FILE *pubkey = fopen("rsa.pub", "w");
    bool verb = false;
    bool initgiv = false;
    uint64_t seed = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("help\n");
            fclose(pubkey);
            fclose(privkey);

            return 0;
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

}*/
int main() {
    printf("placeholder");
}
