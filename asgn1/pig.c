#include "names.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//This function takes an integer of current_score which is the score of the player at the start of
//the turn, and returns the point count of the player at the end of the turn. This function takes
//end of turn as either when the player score is greater than or equal to 100, or rolls SIDE.
int turn(int current_score) {
    typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
    const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };
    bool turn_end = false;
    //This while loop will run the switch statement inside until the current_score hits 100 or 
    //the end of turn is true. This controls the end of the player turn.
    while (current_score < 100 && !(turn_end)) {
	//This switch statement will dictate roll the pig using random()%7, which will provide a value
	//from the pig enum created above. This controls the amount of points added based on side rolled
	//and also sets turn_end to true if side is rolled.
        switch (pig[random() % 7]) {
        case SIDE:
            printf(" pig lands on side");
            turn_end = true;
            break;
        case RAZORBACK:
            printf(" pig lands on back");
            current_score += 10;
            break;
        case TROTTER:
            printf(" pig lands upright");
            current_score += 10;
            break;
        case SNOUTER:
            printf(" pig lands on snout");
            current_score += 15;
            break;
        case JOWLER:
            printf(" pig lands on ear");
            current_score += 5;
            break;
        default:
	    printf("This shouldn't happen, ever.");
	    break;
        }
    }
    return current_score;
}

//The main function begins by taking user input of player count and seed, and makes sure that
//they are valid values. After taking these values, it loops through the players, and calls
//the turn function above to simulate the game of pass the pig.
int main() {
    //This takes the input for player_count and checks if it is between 2 and 10.
    //If invalid value is given, playercount is set to 2.
    printf("%s", "How many players? ");
    int player_count;
    scanf("%d", &player_count);
    if ((player_count < 2) || (player_count > 10)) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        player_count = 2;
    }
    
    //This takes the input for seed and check if it is between 0 and UINT_MAX, which are the range of
    //valid inputs for the srandom function. If invalid value given, seed is set to 2021.
    printf("%s", "Random seed: ");
    long int seed = -1;
    scanf("%ld", &seed);
    if ((seed < 0) || (seed > UINT_MAX)) {
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        seed = 2021;
    }
    srandom(seed);

    //Initializes current_num, which will reflect the number of the current player in the loop,
    //it begins at -1 since the loop begins by incrementing player_count
    int current_num = -1;
    //Initializes array scores, which will be used to store player scores.
    int scores[10] = { 0 };

    //the below do-while loop iterates through the players infinitely until a player reached the
    //winning score of 100. It uses current_num to track the current player. 
    do {
	//This increments current_num in a way that stays within player_count.
        if (current_num == player_count - 1) {
            current_num = 0;
        } else {
            current_num++;
        }

        printf("%s rolls the pig...", names[current_num]);
        scores[current_num] = turn(scores[current_num]);
        printf("\n");
    } while (scores[current_num] < 100);
    //Since the game is over when the code exits the loop, the below statment prints the name and
    //score of the winning player
    printf("%s wins with %d points!\n", names[current_num], scores[current_num]);
    return 0;
}
