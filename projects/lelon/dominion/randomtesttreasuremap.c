/************************************************************************* 
 * Program: randomtesttreasuremap 
 * Author: Long Le
 * Date: 13-Nov-2018 
 * Class: CS362
 * Instructor: Jaki Shaik
 * Assignment 4 
 * Description: Random testing program for the adventurer card. There are
 * n number of test runs. Each test run consists of either 1 or 2 treasure
 * map cards on the player's hand. The goal of the test is to verify 
 * consistent output with a large number of runs. 
 * Test 1 - Tests the effects of using the treasureMapCard function, 1 vs
 * 2 treasure maps.
 * NOTE: testUpdateCoins.c was used as a base template.
 *************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

int assertion(int statement); 

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int main() {
    srand(time(NULL));
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

    printf ("Start random TESTING Treasure Map card effects:\n");

    const int NUM_TESTS = 100;

    for(int n=0; n<NUM_TESTS; n++) {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game
    //    G.handCount[p] = handCount;                 // set the number of cards on hand
    //    memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to adventurer 

        int playerBeingTested = 0;
        int goldCount = 0;;
        const int setDeckCount = 5;
        int numTreasureMapCards = rand() % 2 + 1;

        if(numTreasureMapCards == 1) {
        /***************************TEST 1*******************************/
              /**Check how many cards were drawn by player*/

        #if (NOISY_TEST == 1)
                printf("\nTest 1a - only 1 treasure map in player's hand\n");
        #endif
            
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

            for(i=0; i<G.handCount[playerBeingTested]; i++) {
                printf("cards: %d ", i);
            }

            G.handCount[playerBeingTested]++;
            G.hand[playerBeingTested][0] = treasure_map;

            int goldCount2nd = 0;

            //treasureMapCard(&G, playerBeingTested, 0);
            cardEffect(treasure_map, 0, 0, 0, &G, 0, 0);
            
            // count gold cards in deck
            for(i=0; i<G.deckCount[playerBeingTested]; i++) {
                if(G.deck[playerBeingTested][i] == gold) {
                    ++goldCount2nd;
                }
            }

            int testResults = assertion(goldCount == goldCount2nd); 

            if(!testResults) {
                printf("\nTest %d ERROR: original gold count is %d and current gold count is %d\n", n+1, goldCount, goldCount2nd);
                printf("ERROR: NO GOLD SHOULD BE ADDED TO DECK\n");
                testsPassed = 0;
            }
        } else if(numTreasureMapCards == 2) {
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

            int goldCount2nd = 0;

            //treasureMapCard(&G, playerBeingTested, 0);
            
            cardEffect(treasure_map, 0, 0, 0, &G, 0, 0);

            // count gold cards in deck
            for(i=0; i<G.deckCount[playerBeingTested]; i++) {
                if(G.deck[playerBeingTested][i] == gold) {
                    ++goldCount2nd;
                }
            }

            int testResults = assertion(goldCount2nd == goldCount+4); 

            if(!testResults) {
                printf("\nTest %d ERROR: original gold count is %d and current gold count is %d\n", n+1, goldCount, goldCount2nd);
                printf("ERROR: 4 gold cards should be received into deck\n");
                testsPassed = 0;
            }
        }
        printf("\n");
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
 * @param statement - test conditional statement; false == 0, true >= 1.
 *************************************************************************/
int assertion(int statement) {
    if(statement<=0) {
#if (NOISY_TEST == 1)
        printf("TEST FAILED! ");    
#endif
        return 0;
    }

#if (NOISY_TEST == 1)
    printf("TEST PASSED\n");    
#endif
    return 1;
}
