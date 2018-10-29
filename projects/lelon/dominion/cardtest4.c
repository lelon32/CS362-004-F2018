/************************************************************************* 
 * Program: cardtest4 
 * Author: Long Le
 * Date: 28-Oct-2018 
 * Class: CS362
 * Instructor: Jaki Shaik
 * Assignment 3 
 * Description: Unit test program for function Council Room Card.
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
    int maxDeckCount = 4;

    int cards[MAX_HAND]; 
    
    for (i = 0; i < handCount; i++)
    {
        cards[i] = adventurer;
    }

    printf ("TESTING Council Room Card:\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[p] = handCount;                 // set the number of cards on hand
    memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to adventurer 

    // For Test 3
    int victoryCardPileCount = G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province];
    int kingdom[10];
    for(i=0; i<10; i++) {
        kingdom[i] = k[i];
    }
    
    // Clear all treasure cards.
    int count;
    for(count=0; count<maxDeckCount; count++) {
        G.deck[p][count] = adventurer; 
    }

    G.deckCount[p] = maxDeckCount; // reset
   
/***************************TEST 1*******************************/
      /**Check how many cards were drawn by each player*/

#if (NOISY_TEST == 1)
        printf("\nTest 1 - verify players' drawn cards");
#endif
    const int setDeckCount = 5;
    
    // set all player's cards in hand to 0 and decks to 3.
    for(i=0; i<numPlayer; i++) {
        G.handCount[i] = 0;
        G.deckCount[i] = setDeckCount;

        // all cards in decks will be smithy
        for(int j=0; j<5; j++) {
            G.deck[i][j] = smithy;
        }
    }
    
    int playerBeingTested = 0;
    // test player 0
    G.handCount[0] = 1;
    G.hand[playerBeingTested][0] = council_room;
    //councilRoomCard(&G, playerBeingTested, 0); 
    cardEffect(council_room, 0, 0, 0, &G, 0, 0);

    int testResults;
    // test how many cards each player has
    for(i=0; i<numPlayer; i++) {
#if (NOISY_TEST == 1)
        printf("\nPlayer %d card on hand count is: %d\n", i, G.handCount[i]);
#endif
        if(i==playerBeingTested) {
            testResults = assertion(G.handCount[playerBeingTested] == 4);

            if(!testResults) {
                printf("\nERROR: Player %d should have drawn 4 cards!\n", playerBeingTested);
                testsPassed = 0;
            }
        } else {
            testResults = assertion(G.handCount[i] == 1);

            if(!testResults) {
                printf("\nERROR: Player %d should have drawn 1 card!\n", i);
                testsPassed = 0;
            }
        }
    }


/***************************TEST 2*******************************/
      /**Check if card was drawn from current player's deck.*/
#if (NOISY_TEST == 1)
        printf("\nTest 2 - verify if the user's deck was drawn from\n");
#endif
    testResults = assertion(G.deckCount[playerBeingTested] < setDeckCount );

    if(!testResults) {
        printf("\nERROR: Player %d's deck was not drawn from!\n", playerBeingTested);
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
