#include "mathlib.h"

#include <stdio.h>
#include <unistd.h>
#define OPTIONS "ae : "

int main(int argc, char **argv) {
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': printf("-a option \n"); break;
        case 'e':
            printf("e is equal %16.15lf \n", e());
            printf("in %d \n", e_terms());
            break;
        }
    }
    return 0;
}
