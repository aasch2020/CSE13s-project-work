#include "numtheory.h"
#include "randstate.h"
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

void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    mpz_t r, rz, t, tz, q, rtemp, ttemp;
    mpz_init_set(r, n);
    mpz_init_set(rz, a);
    mpz_init_set_ui(t, 0);
    mpz_init_set_ui(tz, 1);
    mpz_init_set_ui(q, 0);
    mpz_init_set_ui(rtemp, 0);
    mpz_init_set_ui(ttemp, 0);
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
    if ((mpz_cmp_ui(r, 1) > 0)) {
        mpz_set_ui(i, 0);
        mpz_clears(r, rz, t, tz, q, rtemp, ttemp, NULL);
        return;
    }
    if ((mpz_cmp_ui(t, 0) < 0)) {
        mpz_add(t, t, n);
    }
    mpz_set(i, t);
    mpz_clears(r, rz, t, tz, q, rtemp, ttemp, NULL);
    return;
}

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
    mpz_clears(v, p,exp ,NULL);
    return;
}

bool is_prime(mpz_t n, uint64_t iters) {
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
    while (mpz_divisible_2exp_p(r, 2) != 0) {
        mpz_tdiv_q_2exp(r, r, 1);
        mpz_add_ui(s, s, 1);
    }

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
    mpz_clears(r, s, nz, nrand, a, y, j, pm2, NULL);
    return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    //   printf("making prime");
    mpz_t generated;
    mpz_init(generated);
    bool primefound = false;
    while (!primefound) {
        //	printf("stuck here");
        mpz_rrandomb(generated, state, bits);
        primefound = is_prime(generated, iters);
    }
    mpz_set(p, generated);
    mpz_clear(generated);
    return;
}
