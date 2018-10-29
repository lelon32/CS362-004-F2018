/************************************************************************* 
 * Program: cardtest3 
 * Author: Long Le
 * Date: 27-Oct-2018 
 * Class: CS362
 * Instructor: Jaki Shaik
 * Assignment 3 
 * Description: Test program for treasure map card.
 * Test 1 - Tests the effects of using the treasureMapCard function.
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

    printf ("TESTING treasureMapCard():\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
//    G.handCount[p] = handCount;                 // set the number of cards on hand
//    memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to adventurer 
    
/***************************TEST 1*******************************/
      /**Check how many cards were drawn by player*/

#if (NOISY_TEST == 1)
        printf("\nTest 1a - only 1 treasure map in player's hand\n");
#endif
    int playerBeingTested = 0;
    int goldCount = 0;;
    
    const int setDeckCount = 5;
    
    // set all player's cards in hand to 0 and decks.
    for(i=0; i<numPlayer; i++) {
        G.handCount[i] = 0;
        G.deckCount[i] = setDeckCount;

        // all cards in decks will be smithy
        for(int j=0; j<setDeckCount; j++) {
            G.deck[i][j] = smithy;
        }
    }

    // count gold cards in deck
    for(i=0; i<G.deckCount[playerBeingTested]; i++) {
        if(G.deck[playerBeingTested][i] == gold) {
            ++goldCount;
        }
    }

    printf("\n");
    for(i=0; i<G.handCount[playerBeingTested]; i++) {
        printf("cards: %d ", i);
    }

    G.handCount[playerBeingTested]++;
    G.hand[playerBeingTested][0] = treasure_map;

    int goldCount2nd = 0;

    treasureMapCard(&G, playerBeingTested, 0);
    
    // count gold cards in deck
    for(i=0; i<G.deckCount[playerBeingTested]; i++) {
        if(G.deck[playerBeingTested][i] == gold) {
            ++goldCount2nd;
        }
    }

    int testResults = assertion(goldCount == goldCount2nd); 

    if(!testResults) {
        printf("\nERROR: original gold count is %d and current gold count is %d\n", goldCount, goldCount2nd);
        printf("ERROR: NO GOLD SHOULD BE ADDED TO DECK\n");
        testsPassed = 0;
    }


    // Test with 2 treasure map cards
#if (NOISY_TEST == 1)
        printf("\nTest 1b - 2 treasure map cards in player's hand\n");
#endif
    G.handCount[playerBeingTested] = 0;
    G.deckCount[playerBeingTested] = setDeckCount;

    // all cards in decks will be smithy
    for(int j=0; j<setDeckCount; j++) {
        G.deck[playerBeingTested][j] = smithy;
    }

    // count gold cards in deck
    for(i=0; i<G.deckCount[playerBeingTested]; i++) {
        if(G.deck[playerBeingTested][i] == gold) {
            ++goldCount;
        }
    }

    // add 2 treasure maps card to hand 
    G.deck[playerBeingTested][0] = treasure_map;
    G.deck[playerBeingTested][1] = treasure_map;
    G.handCount[playerBeingTested] += 2;

    goldCount2nd = 0;

    treasureMapCard(&G, playerBeingTested, 0);
    
    // count gold cards in deck
    for(i=0; i<G.deckCount[playerBeingTested]; i++) {
        if(G.deck[playerBeingTested][i] == gold) {
            ++goldCount2nd;
        }
    }

    testResults = assertion(goldCount2nd == goldCount+4); 

    if(!testResults) {
        printf("\nERROR: original gold count is %d and current gold count is %d\n", goldCount, goldCount2nd);
        printf("ERROR: 4 gold cards should be received into deck\n");
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
