
#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#define OPTIONS "aebmrvnsh : "

int main(int argc, char **argv) {
    int opt = 0;
    bool eul = false, b = false, m = false, r = false, v = false, n = false, s = false, h = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        //Loop through all of the command line args and check if they are any of the important values
        switch (opt) {
        case 'a': eul = b = m = r = v = n = true; break;
        case 'e': eul = true; break;
        case 'm': m = true; break;
        case 'r': r = true; break;
        case 'b': b = true; break;
        case 'v': v = true; break;
        case 's': s = true; break;
        case 'n': n = true; break;
        case 'h': h = true; break;
        default: break;
        }
    }
    //The below if statements call appropriate functions and print values from the switch cases above
    //the s bool is for the term count and is thus evaluated on a case by case basis
    if (h) {
        eul = b = m = r = v = n = false;
    }
    if (eul) {
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(e() - M_E));
        if (s) {
            printf("e() terms = %d\n", e_terms());
        }
    }
    if (m) {
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        if (s) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }
    if (r) {
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        if (s) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }
    if (b) {
        printf("pi_bbp = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
            absolute(pi_bbp() - M_PI));
        if (s) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }
    if (v) {
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
            absolute(pi_viete() - M_PI));

        if (s) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }
    if (n) {
        for (double i = 0.0; i <= 10.0; i += 0.1) {
            printf("sqrt_newton(%f) = %16.15lf, sqrt(%f) = %16.15lf, diff = %16.15lf\n", i,
                sqrt_newton(i), i, sqrt(i), absolute(sqrt_newton(i) - sqrt(i)));

            if (s) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }
    if (!(eul || b || m || r || v || n)) {
        printf("SYNOPSIS\n  A test harness for the small numerical library.\n"
               "USAGE\n  ./mathlib-test [-aebmrvnsh]\n"
               "OPTIONS\n"
               "  -a   Runs all tests.\n"
               "  -e   Runs e test.\n"
               "  -b   Runs BBP pi test.\n"
               "  -m   Runs Madhava pi test.\n"
               "  -r   Runs Euler pi test.\n"
               "  -v   Runs Viete pi test.\n"
               "  -n   Runs Newton sqaure root tests.\n"
               "  -s   Print Verbose statistics.\n"
               "  -h   Display program synopsis and usage.\n");
    }
    return 0;
}
