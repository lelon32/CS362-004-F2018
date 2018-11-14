/************************************************************************* 
 * Program: randomtestsmithy 
 * Author: Long Le
 * Date: 13-Nov-2018 
 * Class: CS362
 * Instructor: Jaki Shaik
 * Assignment 4 
 * Description: Random testing program for the smithy card. There are n
 * number of test runs. Each test run consists of a random deck size from 1
 * to 5. Since this is a very simple card, the randomized testing will be
 * checking if the result is as intended, over a large number of runs.
 * 1. Tests how many cards were drawn by each player. 
 * 2. Tests minimum edge cases - deck = 2, 1, and 0. 
 * 3. Check if cards were drawn from the user's deck. 
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
    int maxDeckCount = 4;

    int cards[MAX_HAND]; 
    
    for (i = 0; i < handCount; i++)
    {
        cards[i] = adventurer;
    }

    const int numTests = 100;

    printf ("\nStart random TESTING smithy card effects:\n");
    for(int n=0; n<numTests; n++) {
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
        int setDeckCount = rand() % 6;
        
        // set all player's cards in hand to 0 and decks to random number between 0 and 5. 
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
        G.hand[playerBeingTested][0] = smithy;
        cardEffect(smithy, 0, 0, 0, &G, 0, 0);

        int testResults;
        // test how many cards each player has
        for(i=0; i<numPlayer; i++) {
    #if (NOISY_TEST == 1)
            printf("\nPlayer %d card on hand count is: %d\n", i, G.handCount[i]);
    #endif
            if(i==playerBeingTested) {
                if(setDeckCount >= 3) { 
                    testResults = assertion(G.handCount[playerBeingTested] == 3);

                    if(!testResults) {
                        printf("\nTest %d ERROR: Player %d should have drawn 3 cards!\n", n+1, playerBeingTested);
                        testsPassed = 0;
                    }
                } else if(setDeckCount == 2){
                    testResults = assertion(G.handCount[playerBeingTested] == 2);

                    if(!testResults) {
                        printf("\nTest %d ERROR: 2 cards in deck! Player %d should have drawn 2 cards!\n", n+1, playerBeingTested);
                        testsPassed = 0;
                    }
                } else if(setDeckCount == 1) {
                    testResults = assertion(G.handCount[playerBeingTested] == 1);

                    if(!testResults) {
                        printf("\nTest %d ERROR: Only 1 card in deck! Player %d should have drawn 1 card!\n", n+1, playerBeingTested);
                        testsPassed = 0;
                    }
                } else if(setDeckCount < 1) {
                    testResults = assertion(G.handCount[playerBeingTested] == 0);

                    if(!testResults) {
                        printf("\nTest %d ERROR: 0 cards in deck! Player %d should have drawn 0 cards!\n", n+1, playerBeingTested);
                        testsPassed = 0;
                    }
                }
            } else {
                testResults = assertion(G.handCount[i] == 0);

                if(!testResults) {
                    printf("Test %d ERROR: Player %d should not have drawn any cards!\n", n+1, i);
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
            printf("Test %d ERROR: Player %d's deck was not drawn from!\n", n+1, playerBeingTested);
            testsPassed = 0;
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
