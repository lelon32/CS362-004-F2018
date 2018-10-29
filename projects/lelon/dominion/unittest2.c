/************************************************************************* 
 * Program: unittest2
 * Author: Long Le
 * Date: 26-Oct-2018 
 * Class: CS362
 * Instructor: Jaki Shaik
 * Assignment 3 
 * Description: Unit test program for function shuffle().
 * Test to see if shuffle() function shuffles the deck.
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
    int testsPassed=0;
    int i;
    int seed = 1000;
    int numPlayer = 2;
    //int maxBonus = 10;
    int p=0, handCount=0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    //int maxHandCount = 5;
    const int maxDeckCount = 4;

    int cards[MAX_HAND]; 
    
    for (i = 0; i < handCount; i++)
    {
        cards[i] = smithy;
    }

    printf ("TESTING shuffle():\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[p] = handCount;                 // set the number of cards on hand
    memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to adventurer 
    
    // Clear all treasure cards.
    //int count;
    //for(count=0; count<maxDeckCount; count++) {
    //    G.deck[p][count] = count; 
    //}
     
    G.deck[p][0] = 4; 
    G.deck[p][1] = 6; 
    G.deck[p][2] = 9; 
    G.deck[p][3] = 0; 

    G.deckCount[p] = maxDeckCount; // reset
   
/***************************TEST 1*******************************/
      /**Check to see if cards in deck were shuffled*/

#if (NOISY_TEST == 1)
    printf("\nTest 1 - verify that shuffle will work\n");
#endif
    int ary[maxDeckCount];

#if (NOISY_TEST == 1)
    printf("\nInitial deck:");
#endif
    // copy into temp array.
    for(i=0; i<maxDeckCount; i++) {
        ary[i] = G.deck[p][i];
#if (NOISY_TEST == 1)
        printf("%d ", ary[i]);
#endif
    }

    shuffle(p, &G);

#if (NOISY_TEST == 1)
    printf("\nShuffled deck:");
#endif
    for(i=0; i<maxDeckCount; i++) {
#if (NOISY_TEST == 1)
        printf("%d ", G.deck[p][i]);
#endif
        if(ary[i] != G.deck[p][i]) {
           testsPassed = 1;
        } else {
#if (NOISY_TEST == 1)
           printf("\nFailed! %d\n", G.deck[p][i]);
#endif
        }
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
