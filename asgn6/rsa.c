#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"
//The above header files provided in the resources repository by Professor Long (2021 Professor Long).
#include <time.h>
#include <stdlib.h>
#include <inttypes.h>

//This function takes p, q, n, e, as mpz_t, and two integers of bits and iters.
//It computes two large primes, p , and q, their product n, and an exoponent e.
//it passes these values through the respective arguments and returns nothing.
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    srandom(time(NULL));
    //This code, after seeding the random number generator with current time, generates two primes.
    //The first prime being in between 1/4 nbits and 3/4 nbits bits, and the other being nbits - the bit count of the first prime.
    //It does this by calling make_prime with the respective bit counts.
    uint64_t p_bit_cnt = ((random() % ((nbits / 2))) + (nbits / 4));
    uint64_t q_bit_cnt = nbits - p_bit_cnt;
    make_prime(p, p_bit_cnt, iters);
    make_prime(q, q_bit_cnt, iters);

    //This code computes the totient of p and q, which is p-1 * q-1.
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
    //This code computes a random number of around nbits, which is coprime to the totient iteratively.
    while (!exp_found) {
        mpz_urandomb(e, state, nbits);
        gcd(g, e, totient);
        if (mpz_cmp_ui(g, 1) == 0) {
            exp_found = true;
        }
    }
    mpz_clears(g, totient, NULL);
    return;
}

//This function takes n, e, and s arguments of type mpz_t, a string for a username, and a file to print to.
//It returns void
//It prints n, e, and s as hexstrings witha trailing newline, then the username as a string.
void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n%Zx\n%Zx\n", n, e, s);
    fprintf(pbfile, "%s\n", username);
    return;
}

//This function takes n, e, and s of type mpz_t, a string of username and a file to read from.
//It returns void.
//it reads the hexstrings n, e, and s, from an input file, then reads the string of the username.
void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx", n);
    gmp_fscanf(pbfile, "%Zx", e);
    gmp_fscanf(pbfile, "%Zx", s);
    fscanf(pbfile, "%s", username);
    return;
}

//This function takes t4 mpz_t args, d, e, p, q, and generates a private key, which is stored in d.
//It returns void.
//The private key is the modular inverse of e modulo totient of p and q.
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
    return;
}

//This function takes two mpz_t, n and d, and a file to write to.
//It returns void.
//It prints n and d as hexstrings with a trailing new line.
void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
    return;
}

//This function takes two mpz_t, n and d, and a file to read from.
//It returns void.
//It reads n and d as hexstrings with a trailing new line from the file.
void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx", n);
    gmp_fscanf(pvfile, "%Zx", d);
    return;
}

//This function takes mpz_t args c, m, e, and n.
//It returns void.
//It takes the message m, and encrypts it as m to the e modulo n.
//It stores the computed ciphertext in c.
void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
    return;
}

//This function takes a file to read from, a file to write to, and two mpz_t, of n and e.
//It returns void.
//n is public modulus and e is the public exponent.
//It reads block - 1 number of characters from the input file, where block is floor((log2(n) - 1)/8)
//It then prepends this block with 0xFF, and turns this block into an mpz_t.
//It then encrypts the mpz_t, and writes it to the output file as a hexstring with a trailing newline.
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    uint64_t blocksize = (mpz_sizeinbase(n, 2) - 1) / 8;
    uint8_t *block = (uint8_t *) calloc(blocksize, sizeof(uint8_t));
    block[0] = 0xFF;
    uint64_t readcount;
    bool all_read = false;
    mpz_t impout, ciphertxt;
    mpz_inits(impout, ciphertxt, NULL);
    while (!all_read) {
        readcount = fread(block + 1, 1, blocksize - 1, infile);
        if (readcount == 0) {
            all_read = true;
        } else {

            mpz_import(impout, readcount + 1, 1, 1, 1, 0, block);

            rsa_encrypt(ciphertxt, impout, e, n);
            gmp_fprintf(outfile, "%Zx\n", ciphertxt);
        }
    }

    free(block);
    mpz_clears(impout, ciphertxt, NULL);
    return;
}

//This function decrypts ciphertext c into message m using the private key d and public modulus n, all as mpz_t.
//IT does this by taking the power modulus of c to the d mod n.
//It returns void, and stores the message into m as an mpz_t.
void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
    return;
}

//This function takes mpz_t n, and d which are the public exponent n and the private key d.
//It decrypts from the inputfile and print the decrypted data to the output fil which are given as file pointers.
//it returns void.
//It first creates a block, of size floor((log2(n) -1)/8)
//It then reads in mpz_t from the input file, and decrypts them using rsa_decrypt.
//It exports this mpz_t into an array of uint8_t of size block.
//It then writes from the index 1 to the end of block to the outfile, as the first index of block is 0xFF from the above encoding.
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
        if (readcount == EOF) {
            all_read = true;
        } else {
            rsa_decrypt(msg, in, d, n);
            writecount = mpz_sizeinbase(msg, 8);
            mpz_export(block, &writecount, 1, 1, 1, 0, msg);

            fwrite(block + 1, 1, writecount - 1, outfile);
        }
    }

    free(block);
    mpz_clears(in, msg, NULL);
    return;
}

//This function takes 4 mpz_t and computes the signature s as m to the d mod e.
//It returnbs void.
void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
    return;
}

//This function takes 4 mpz_t and checks if the signature s is equal to the exepected message m.
//It does this by decrypting the signature as s to the e mod n.
//then compares the decrypted siganture with message m.
//It returns true or false depending if the signature is verified.
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
