#include "names.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
int turn(int currentscore) {
    typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
    const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };
    bool turnend = false;
    while (currentscore < 100 && !(turnend)) {
        switch (pig[random() % 7]) {
        case SIDE:
            printf(" pig lands on side");
            turnend = true;
            break;
        case RAZORBACK:
            printf(" pig lands on back");
            currentscore += 10;
            break;
        case TROTTER:
            printf(" pig lands upright");
            currentscore += 10;
            break;
        case SNOUTER:
            printf(" pig lands on snout");
            currentscore += 15;
            break;
        case JOWLER:
            printf(" pig lands on ears");
            currentscore += 5;
            break;
        default: printf("This shouldn't happen, ever."); break;
        }
    }
    return currentscore;
}
int main() {
    printf("%s", "How many players? ");
    int playercount;
    scanf("%d", &playercount);
    if ((playercount < 2) || (playercount > 10)) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        playercount = 2;
    }
    printf("%s", "Random Seed: ");
    long int seed = -1;
    scanf("%ld", &seed);
    if ((seed < 0) || (seed > UINT_MAX)) {
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        seed = 2021;
    }
    srandom(seed);
    int currentnum = 0;
    int scores[10] = { 0 };
    do {
        printf("%s rolls the pig...", names[currentnum]);
        scores[currentnum] = turn(scores[currentnum]);
        if (currentnum == playercount - 1) {
            currentnum = 0;
        } else {
            currentnum++;
        }
        printf("\n");
    } while (scores[currentnum] < 100);
    printf("%s wins with %d points\n", names[currentnum], scores[currentnum]);
    return 0;
}
