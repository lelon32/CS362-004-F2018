/************************************************************************* 
 * Program: unittest1 
 * Author: Long Le
 * Date: 28-Oct-2018 
 * Class: CS362
 * Instructor: Jaki Shaik
 * Assignment 3 
 * Description: Unit test program for function fullDeckCount().
 * 1. Test initial count
 * 2. Test by drawing two cards
 * 3. Test by adding 2 cards to discard pile
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
    int p=0, handCount=20;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    //int maxHandCount = 5;
    int maxDeckCount = 5;

    int cards[MAX_HAND]; 
    
    int card = copper;
    for (i = 0; i < handCount; i++)
    {
        cards[i] = card;
    }

    printf ("TESTING fullDeckCount():\n\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[p] = handCount;                 // set the number of cards on hand
    memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to copper 


/***************************TEST 1*******************************/
         /**Check if intial count for cards are accurate*/

#if (NOISY_TEST == 1)
    printf("Test 1 - check initial count.\nShould be deck = %d, hand = %d, and discard = %d\n\n", maxDeckCount, handCount, 0);
#endif

    fullDeckCount(p, card, &G); 

    if(G.deckCount[p] != maxDeckCount){
        testsPassed = 0;
        printf("Deck count should be = %d, but is %d\n\n", maxDeckCount, G.deckCount[p]);
    } else if (G.handCount[p] != handCount) {
        testsPassed = 0;
        printf("Hand count should be = %d, but is %d\n\n", handCount, G.handCount[p]);
    } else if (G.discardCount[p] != 0) {
        testsPassed = 0;
        printf("Discard count should be = %d, but is %d\n\n", 0, G.discardCount[p]); 
    }

/***************************TEST 2*******************************/
         /**Draw 3 cards and check if count is accurate*/

#if (NOISY_TEST == 1)
    printf("Test 2 - draw 3 cards.\nShould be deck = %d, hand = %d, and discard = %d\n\n", maxDeckCount-3, handCount+3, 0);
#endif
    drawCard(p, &G);
    drawCard(p, &G);
    drawCard(p, &G);

    fullDeckCount(p, card, &G); 

    if(G.deckCount[p] != maxDeckCount-3){
        testsPassed = 0;
        printf("Deck count should be = %d, but is %d\n\n", maxDeckCount-3, G.deckCount[p]);
    } else if (G.handCount[p] != handCount+3) {
        testsPassed = 0;
        printf("Hand count should be = %d, but is %d\n\n", handCount+3, G.handCount[p]);
    } else if (G.discardCount[p] != 0) {
        testsPassed = 0;
        printf("Discard count should be = %d, but is %d\n\n", 0, G.discardCount[p]); 
    }

/***************************TEST 3*******************************/
         /**Discard 2 cards and check if count is accurate*/

#if (NOISY_TEST == 1)
    printf("Test 3 - add 2 cards to discard pile.\nShould be deck = %d, hand = %d, and discard = %d\n\n", maxDeckCount-3, handCount+3, 2);
#endif
    gainCard(0, &G, 0, p);
    gainCard(1, &G, 0, p);

    fullDeckCount(p, card, &G); 

    if(G.deckCount[p] != maxDeckCount-3){
        testsPassed = 0;
        printf("ERROR: Deck count should be = %d, but is %d\n\n", maxDeckCount-3, G.deckCount[p]);
    } else if (G.handCount[p] != handCount+3) {
        testsPassed = 0;
        printf("ERROR: Hand count should be = %d, but is %d\n\n", handCount+3, G.handCount[p]);
    } else if (G.discardCount[p] != 2) {
        testsPassed = 0;
        printf("ERROR: Discard count should be = %d, but is %d\n\n", 2, G.discardCount[p]); 
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
    printf("TEST PASSED\n\n");    
#endif
    return 1;
}
