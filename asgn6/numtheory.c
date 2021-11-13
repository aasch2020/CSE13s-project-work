#include "numtheory.h"

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
    return;
}

void mod_inverse(mpz_t i, mpz_t a, mpz_t n){
	mpz_t r, rz, t, tz, q, rtemp, ttemp;
	mpz_init_set(r, n);
	mpz_init_set(rz, a);
	mpz_init_set_ui(t, 0);
	mpz_init_set_ui(tz, 1);
	mpz_init_set_ui(q, 0);
	mpz_init_set_ui(rtemp, 0);
	mpz_init_set_ui(ttemp, 0);
	while((mpz_cmp_ui(rz, 0) != 0)){
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
	if((mpz_cmp_ui(r, 1) > 0)){
		mpz_set_ui(i, 0);
		return;
	}	
	if((mpz_cmp_ui(t, 0) < 0)){
		mpz_add(t, t, n);
	}
	mpz_set(i, t);



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
    return;
}
/*
bool is_prime(mpz_t n, uint64_t iters){


}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters){

}

*/

int main() {
    //	printf("main");
    mpz_t a, d, b, c, f;
    mpz_inits(a, d, b,c,f, NULL);
    mpz_set_ui(a, 64);
    mpz_set_ui(b, 24);
    mpz_set_ui(c, 17);
    gcd(d, a, b);
    gmp_printf("The thing %Zd\n", d);
    pow_mod(d, a, b, c);
    gmp_printf("The thing pow %Zd\n", d);
	mpz_set_ui(d, 9);
	mpz_set_ui(c, 64);
    mod_inverse(f, d, c);
     gmp_printf("The thing modinv %Zd\n", f);

}
