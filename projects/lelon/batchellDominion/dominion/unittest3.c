/************************************************************************* 
 * Program: unittest3
 * Author: Long Le
 * Date: 28-Oct-2018 
 * Class: CS362
 * Instructor: Jaki Shaik
 * Assignment 3 
 * Description: Unit test program for function isGameOver().
 * NOTE: testUpdateCoins.c was used as a base template.
 *************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int assertion(int a); 

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int testsPassed=1;
    int i;
    int seed = 1000;
    int numPlayer = 2;
    //int maxBonus = 10;
    int p=0, handCount=0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    //int maxHandCount = 5;
    int maxDeckCount = 5;

    int cards[MAX_HAND]; 
    
    for (i = 0; i < handCount; i++)
    {
        cards[i] = adventurer;
    }

    printf ("TESTING isGameOver():\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
//    G.handCount[p] = handCount;                 // set the number of cards on hand
//    memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to adventurer 
    
/***************************TEST 1*******************************/
      /**Check how many cards were drawn by player*/

#if (NOISY_TEST == 1)
    printf("\nTest 1 - verify the game ends if there are no more province cards\n");
#endif
    G.supplyCount[province] = 0;
    if(!assertion(isGameOver(&G))) {
        printf("\nERROR: Failed to end game when province cards = 0\n");    
        testsPassed = 0;
    }

    G.supplyCount[province] = 1;
    G.supplyCount[0] = 0;
    G.supplyCount[1] = 0;
    G.supplyCount[2] = 0;
#if (NOISY_TEST == 1)
    printf("\nTest 2 - verify the game ends if there are 3 empty supply piles\n");
#endif
    if(!assertion(isGameOver(&G))) {
        printf("\nERROR: Failed to end game when 3 supply piles are empty!\n");    
        testsPassed = 0;
    }

    G.supplyCount[2] = 1;
#if (NOISY_TEST == 1)
    printf("\nTest 3 - verify the game continues if there are province cards\n and if there are less than 3 supply piles empty. \n");
#endif
    if(!assertion(!isGameOver(&G))) {
        printf("\nERROR: Game ended when it was not supposed to!\n");    
        testsPassed = 0;
    }

    if(testsPassed) {
        printf("\nALL TESTS SUCCESSFULLY PASSED!\n");
    } else {
        printf("\nTEST FAILURES DETECTED\n");
    } 

    return 0;
}

/************************************************************************* 
 * Description: Custom assertion function to be able to use with coverage
 * programs (does not stop program).
 * @param a - test conditional statement; false == 0, true >= 1.
 *************************************************************************/
int assertion(int a) {
    if(a<=0) {
        printf("TEST FAILED! ");    
        return 0;
    }

#if (NOISY_TEST == 1)
    printf("TEST PASSED\n");    
#endif
    return 1;
}
