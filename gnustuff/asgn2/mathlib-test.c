
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
        e();
    }
    if (m) {
        pi_madhava();
    }
    if (r) {
        pi_euler();
    }
    if (b) {
        pi_bbp();
    }
    if (v) {
        pi_viete();
    }
    if (n) {

        sqrt_newton(10.00);
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
