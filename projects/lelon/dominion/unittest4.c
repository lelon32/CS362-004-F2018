/************************************************************************* 
 * Program: unittest4
 * Author: Long Le
 * Date: 28-Oct-2018 
 * Class: CS362
 * Instructor: Jaki Shaik
 * Assignment 3 
 * Description: Unit test program for function drawCard().
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

    printf ("TESTING drawCard():\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[p] = handCount;                 // set the number of cards on hand
    memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to adventurer 

    // Clear all treasure cards.
    int count;
    for(count=0; count<maxDeckCount; count++) {
        G.deck[p][count] = adventurer; 
    }

/***************************TEST 1*******************************/
      /**Check how many cards were drawn by each player*/

#if (NOISY_TEST == 1)
    printf("\nTest 1 - verify cards are drawn from the player's deck to the player's hand\n");
    printf("Testing with 5 cards in the deck\n");
#endif
     
    for(i=0; i<maxDeckCount; i++) {
        int count = G.deckCount[p];
        int hcount = G.handCount[p];
        //printf("\nCount: %d\n", count);
        drawCard(p, &G);
        if(!assertion(G.deckCount[p] == count-1)) {
#if (NOISY_TEST == 1)
            printf("\nERROR: deck did not decrement count!\n");
#endif
            testsPassed = 0;
        }
        if(!assertion(G.handCount[p] == hcount+1)) {
#if (NOISY_TEST == 1)
            printf("\nERROR: hand did not increment count!\n");
#endif
            testsPassed = 0;
        }
    }   

#if (NOISY_TEST == 1)
    printf("\nTest 2 - verify cards once deck is empty, discarded cards are shuffled into deck\n");
    printf("5 cards are added to the discard pile\n");
#endif
    G.discardCount[p] = 4;

    // add cards to discard pile
    for(count=0; count<4; count++) {
        G.discard[p][count] = copper; 
    }

    int dcount = G.discardCount[p];
    int hcount = G.handCount[p];
    drawCard(p, &G);
    if(!assertion(G.deckCount[p] > 0 && G.discardCount !=0)) {
#if (NOISY_TEST == 1)
        printf("\nERROR: discard pile did not get shuffled into deck!\n");
#endif
        testsPassed = 0;
    }
    if(!assertion(G.deckCount[p] == dcount-1)) {
#if (NOISY_TEST == 1)
        printf("\nERROR: discard pile did not decrement!\n");
#endif
        testsPassed = 0;
    }
    if(!assertion(G.handCount[p] == hcount+1)) {
#if (NOISY_TEST == 1)
        printf("\nERROR: hand did not increment count!\n");
#endif
        testsPassed = 0;
    }
    

    if(testsPassed) {
        printf("\nALL TESTS SUCCESSFULLY PASSED!\n");
    } else {
        printf("\nTEST FAILURES DETECTED\n");
    }
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
