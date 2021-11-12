#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void gcd(int a, int b, int *c){
	int temp = 0;
	while( b != 0){
		temp = b;
		b = a % b;
		a = temp;
	}
	*c = a;
	return;

}

void pow_mod(int *out, int base, int exponent, int modulus){
	int v = 1;
	int p = base;
	while(exponent > 0){
		if((exponent % 2 == 1)){
			v = (v * p) % modulus;

		}
		p = (p * p) % modulus;
		exponent = exponent / 2;

	}
        *out = v;

}

void mod_inverse(int *i, int a, int n){
	int r = n;
	int rz = a;
	int t = 0;
	int tz = 1;
	int q = 0;
	int rtemp = 0;
	int ttemp = 0;
	while(rz != 0){
		q = r/rz;
		rtemp = rz;
		rz = r - (q * rz);
		r = rtemp;
		ttemp = tz;
		tz = t - (q*tz);
		t = ttemp;
	}
	if (r > 1){
		*i = 0;

	}
	if (t < 0){
		t = t + n;

	}
	*i = t;


}


bool is_prime(int n, int iters){
	int r = n - 1;
	int s = 0;
        while((r % 2) == 0){
		r = r >> 1;
		s++;
	}
	printf("found %d in %d  also iters %d\n", r, s, iters);
	return true;


}
int main(){
	int a = 169;
	int b = 13;
	int x = 0;
	gcd(a, b, &x);
	printf("gcd %d\n", x);
        int base = 11;
	int exp = 14;
	int modulo = 222;
	int out = 0;
	pow_mod(&out, base, exp, modulo);
	printf("pow_mod %d\n", out);
	int i = -2;
	mod_inverse(&i, 9, 52);
	printf("mod inv is %d\n", i);
	is_prime(13, 15);
}
