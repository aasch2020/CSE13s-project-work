#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#define OPTIONS "aemr : "

int main(int argc, char **argv) {
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': printf("-a option \n"); break;
        case 'e':
            printf("e is equal %16.15lf \n", e());
            printf("in %d \n", e_terms());
            break;
        case 'm':
            printf("pi equal %16.15lf \n ", pi_madhava());
            printf("in %d \n", pi_madhava_terms());
            break;
        case 'r':
            printf("euler pi %16.15lf \n", pi_euler());
            printf("in %d \n", pi_euler_terms());
            break;
        default: printf("really?");
        }
    }
    return 0;
}
