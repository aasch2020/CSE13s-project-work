#include "numtheory.h"
#include "randstate.h"
//The above header files provided in the resources repository by Professor Long. (2021 Professor Long)

//
//
//This function takes three arguments, of type mpz_t and does not return a value. This function computes the greatest common denominator of a and b
//and stores the computed value in d.
//This function initializes and clears temporary variable so a and b do not get changed during while running.
//The below function inspired by the pseudocode provided in the assignment document by Professor Long(2021 Professor Long)
void gcd(mpz_t d, mpz_t a, mpz_t b) {
    mpz_t ac;
    mpz_t bc;
    mpz_t temp;
    mpz_init_set(temp, b);
    mpz_init_set(ac, a);
    mpz_init_set(bc, b);
    while (mpz_cmp_ui(bc, 0) != 0) {
        mpz_set(temp, bc);
        mpz_mod(bc, ac, bc);
        mpz_set(ac, temp);
    }

    mpz_set(d, ac);
    mpz_clears(ac, bc, temp, NULL);
    return;
}

//
//
//This below function takes three arguments and computes the modular inverse of a and n, and stores it in i. It does not return a value.
//The below function inspired by the pseudocode provided in the assignment document by Professor Long(2021 Professor Long)
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    mpz_t r, rz, t, tz, q, rtemp, ttemp;
    mpz_init_set(r, n);
    mpz_init_set(rz, a);
    mpz_init_set_ui(t, 0);
    mpz_init_set_ui(tz, 1);
    mpz_init_set_ui(q, 0);
    mpz_init_set_ui(rtemp, 0);
    mpz_init_set_ui(ttemp, 0);
    //In this loop rz is continually decremented until it equals 0, to calculate t as a part of mod inverse
    while ((mpz_cmp_ui(rz, 0) != 0)) {
        mpz_tdiv_q(q, r, rz);
        mpz_set(rtemp, rz);
        mpz_mul(rz, q, rz);
        mpz_sub(rz, r, rz);
        mpz_set(r, rtemp);
        mpz_set(ttemp, tz);
        mpz_mul(tz, q, tz);
        mpz_sub(tz, t, tz);
        mpz_set(t, ttemp);
    }
    //If r is greater than 1 after the loop is finished, there is no modular inverse, this condition returns accordingly.
    if ((mpz_cmp_ui(r, 1) > 0)) {
        mpz_set_ui(i, 0);
        mpz_clears(r, rz, t, tz, q, rtemp, ttemp, NULL);
        return;
    }
    //If t is less than 0, it cannot be a valid modular inverse, add n to t to make it the modular inverse.
    if ((mpz_cmp_ui(t, 0) < 0)) {
        mpz_add(t, t, n);
    }
    mpz_set(i, t);
    mpz_clears(r, rz, t, tz, q, rtemp, ttemp, NULL);
    return;
}

//This function takes 4 arguments, and calculates the base to the exponent modulo the modulus, and stores the computes value in out.
// It does not return a value
//The below function inspired by the pseudocode provided in the assignment document by Professor Long(2021 Professor Long)
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_t v, p, exp;
    mpz_init_set_ui(v, 1);
    mpz_init_set(p, base);
    mpz_init_set(exp, exponent);
    while (mpz_cmp_ui(exp, 0) > 0) {
        if (!(mpz_divisible_ui_p(exp, 2))) {
            mpz_mul(v, v, p);
            mpz_mod(v, v, modulus);
        }
        mpz_mul(p, p, p);
        mpz_mod(p, p, modulus);
        mpz_tdiv_q_2exp(exp, exp, 1);
    }
    mpz_set(out, v);
    mpz_clears(v, p, exp, NULL);
    return;
}

//The function takes two arguments, n and iters, and computes probablisticly if the n is prime using iters iterations of the Milller Rabin method.
//the function returns a boolean value of the computed primality of the given n
//The below function inspired by the pseudocode provided in the assignment document by Professor Long(2021 Professor Long)
bool is_prime(mpz_t n, uint64_t iters) {
    //These conditional statements check if the given n is a number that will not correctly be decided with the implementation
    //of the Miller Rabin method, as a number in the rand 2 to n-2 will not exist.
    //It retu
    if ((mpz_cmp_ui(n, 3) == 0) || (mpz_cmp_ui(n, 2) == 0)) {
        return true;
    }
    if (mpz_cmp_ui(n, 1) == 0 || mpz_cmp_ui(n, 0) == 0) {
        return false;
    }

    mpz_t r, s, nz, nrand, a, y, j, pm2;
    mpz_inits(a, y, j, NULL);
    mpz_init_set_ui(pm2, 2);
    mpz_init_set(nz, n);
    mpz_init_set(nrand, n);
    mpz_sub_ui(nz, nz, 1);
    mpz_sub_ui(nrand, nrand, 3);
    mpz_init_set(r, n);
    mpz_sub_ui(r, r, 1);
    mpz_init_set_ui(s, 0);
    //This code computes r and s such that n-1=2^s*r and r is odd
    //It does this by repeatedly dividing r by two, until it is no longer divisible by 2.
    //The value of r begins at n-1.
    //The number of iterations of this loop is s.
    while (mpz_divisible_2exp_p(r, 2) != 0) {
        mpz_tdiv_q_2exp(r, r, 1);
        mpz_add_ui(s, s, 1);
    }

    //THis code the does iters iterations of the Miller Rabin method.
    //It generates a random number between 2 and n-2, takes the power modulus of the random number to r mod n
    //Then while the computed pow mod is not 1 or n - 1, sets j t 1.
    //While j is less than s -1, and y still does not equal n - 1
    //Take the powuer moudulus of y to the 2, n
    //if y is 1 the number is not prime
    //After the interior loop is y is n-1 the number is not prime.
    for (uint64_t i = 0; i < iters; i++) {
        mpz_urandomm(a, state, nrand);
        mpz_add_ui(a, a, 2);
        pow_mod(y, a, r, n);
        if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, nz))) {
            mpz_set_ui(j, 1);
            while ((mpz_cmp(j, s) < 0) && (mpz_cmp(y, nz) != 0)) {
                pow_mod(y, y, pm2, n);
                if (mpz_cmp_ui(y, 1) == 0) {
                    mpz_clears(r, s, nz, nrand, a, y, j, pm2, NULL);
                    return false;
                }
                mpz_add_ui(j, j, 1);
            }
            if (mpz_cmp(y, nz) != 0) {
                mpz_clears(r, s, nz, nrand, a, y, j, pm2, NULL);
                return false;
            }
        }
    }
    //If neither above condition for false it met in the loop, return true, the number is computed to be prime.
    mpz_clears(r, s, nz, nrand, a, y, j, pm2, NULL);
    return true;
}

//The below function takes three arguments, p, bits, and a number of iterations
//This function generates a new prime number of length in bits bits using the miller rabin method with iters iterations
//It then stores this value in p
//The below function inspired by the pseudocode provided in the assignment document by Professor Long(2021 Professor Long)
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    //This function first creates a number of all 1 bits of length n-1 bits, which will act as the floor - 1 for the generated
    //random number.
    mpz_t generated, rangeflr;
    mpz_init_set_ui(rangeflr, 1);
    mpz_mul_2exp(rangeflr, rangeflr, bits);
    mpz_sub_ui(rangeflr, rangeflr, 1);
    mpz_init(generated);
    bool primefound = false;
    //This iteratively generates a number from 0 to 2^(n-1), adds it the the given floor of (2^n)-1, and adds one.
    //This generates a random number of n bits.
    //It then checks if it is prime and continues this process until a prime number is found.
    while (!primefound) {
        mpz_urandomb(generated, state, bits);
        mpz_add(generated, generated, rangeflr);
        mpz_add_ui(generated, generated, 1);

        primefound = is_prime(generated, iters);
    }
    mpz_set(p, generated);
    mpz_clears(generated, rangeflr, NULL);
    return;
}
