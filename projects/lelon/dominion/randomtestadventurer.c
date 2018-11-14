/************************************************************************* 
 * Program: randomtestadventurer 
 * Author: Long Le
 * Date: 13-Nov-2018 
 * Class: CS362
 * Instructor: Jaki Shaik
 * Assignment 4 
 * Description: Random testing program for the adventurer card. 
 * There are n number of test runs. Each test run consists of randomly
 * inserted cards. The goal of the test is to see if the effects of the
 * adventurer card is still consistent with a large number of runs. There
 * are 3 assertions that are verified after each card call.
 * 1. asserts a maximum of 2 cards drawn. 
 * 2. asserts that the number of cards drawn cannot be more than the number
 * of treasure cards in the deck. 
 * 3. asserts that if there are no treasure cards in the deck, no cards
 * should be drawn.
 * NOTE: testUpdateCoins.c was used as a base template.
 *************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

int assertion(int statement);  // custom assert statement

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


    printf ("\nStart Random TESTING adventurer card effects:\n\n");

    // start of random testing 
    const int timesToTest = 100; 

    for(int i=0; i<timesToTest; i++) {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.handCount[p] = handCount;                 // set the number of cards on hand
        memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to adventurer 

        // Clear all treasure cards
        int count;
        for(count=0; count<maxDeckCount; count++) {
            G.deck[p][count] = adventurer; 
        }

        G.deckCount[p] = maxDeckCount; // reset

        int treasureCount = 0;

        // add random cards to deck
        for(int j=0; j<maxDeckCount; j++) {
            enum CARD c = rand() % 27; 
            G.deck[p][j] = c;
            if(c == copper || c == silver || c == gold) {
                ++treasureCount; 
            }
        }

        int origHandCount = G.handCount[p]; 

        cardEffect(adventurer, 0, 0, 0, &G, 0, 0); // play adventurer card

        // check if any cards were drawn
        if(origHandCount < G.handCount[p]) {
            int cardsDrawn = G.handCount[p] - origHandCount;
            if(!assertion(cardsDrawn < 3)) {     // should only draw up to 2 cards
                printf("\nERROR during TEST %d: more than 2 cards were drawn.\n", i+1);
                testsPassed = 0;
            } 
            if(!assertion(cardsDrawn <= treasureCount)) {    // cards drawn should not exceed number of treasure cards
                printf("\nERROR during TEST %d: %d card(s) drawn but %d treasure cards in deck.\n", i+1, cardsDrawn, treasureCount);
                if(cardsDrawn == 3) {
                    printf("  ->The cards drawn were %d, %d, and %d\n", G.deck[p][G.handCount[p]-1], G.deck[p][G.handCount[p]-2], G.deck[p][G.handCount[p]-3]);
                } else if(cardsDrawn == 2) {
                    printf("  ->The cards drawn were %d and %d\n", G.deck[p][G.handCount[p]-1], G.deck[p][G.handCount[p]-2]);
                } else if(cardsDrawn == 1) {
                    printf("  ->The card drawn was %d\n", G.deck[p][G.handCount[p]-1]);
                }
                testsPassed = 0;
            } 
        } else {
            if(!assertion(treasureCount == 0)) {     // If no cards are drawn, there should be no treasure cards in deck
                printf("\nERROR during TEST %d: there were no cards drawn but there are %d treasure cards in deck.\n", i+1, treasureCount);
                testsPassed = 0;
            } 
        }
    }
   
///***************************TEST 1*******************************/
//         /**Check how many treasure cards are added*/
//
//    // Put 1 treasure cards in deck
//    G.deck[p][0] = copper;
//#if (NOISY_TEST == 1)
//    printf("Test 1 - check how many treasure cards are added.\n\n");
//#endif
//
//#if (NOISY_TEST == 1)
//    printf("Testing with 1 treasure card in deck.\nOnly 1 card should be added to hand.\n");
//#endif
//    int origCardsInHand = G.handCount[p];
//
//    cardEffect(adventurer, 0, 0, 0, &G, 0, 0);
//
//#if (NOISY_TEST == 1)
//    testsPassed = assertion(G.handCount[p]==origCardsInHand+1);
//    if(!testsPassed) {
//        printf("%d card(s) were added.\n", G.handCount[p]-origCardsInHand);
//    }
//#endif
//
//    origCardsInHand = G.handCount[p];
//    G.deckCount[p] = maxDeckCount; // reset
//
//#if (NOISY_TEST == 1)
//    printf("Testing with 2 treasure cards in deck.\n2 cards should be added to hand.\n");
//#endif
//    // Put 2 treasure cards in deck
//    G.deck[p][0] = copper; 
//    G.deck[p][1] = silver; 
//    cardEffect(adventurer, 0, 0, 0, &G, 0, 0);
//
//#if (NOISY_TEST == 1)
//    testsPassed = assertion(G.handCount[p]==origCardsInHand+2);
//    if(!testsPassed) {
//        printf("%d card(s) were added.\n", G.handCount[p]-origCardsInHand);
//    }
//#endif
//
//    origCardsInHand = G.handCount[p];
//    G.deckCount[p] = maxDeckCount; // reset
//
//#if (NOISY_TEST == 1)
//    printf("Testing with 3 treasure cards in deck.\nOnly 2 cards should be added to hand.\n");
//#endif
//    // Put 3 treasure cards in deck
//    G.deck[p][0] = copper; 
//    G.deck[p][1] = silver;
//    G.deck[p][2] = gold; 
//    cardEffect(adventurer, 0, 0, 0, &G, 0, 0);
//
//#if (NOISY_TEST == 1)
//    testsPassed = assertion(G.handCount[p]==origCardsInHand+2);
//    if(!testsPassed) {
//        printf("%d card(s) were added.\n", G.handCount[p]-origCardsInHand);
//    }
//#endif

/***************************TEST 2*******************************/
/**Check if cards other than treasure cards are counted as treasure cards*/
//#if (NOISY_TEST == 1)
//    printf("\nTest 3 - check if other cards are counted as a treasure card.\n\n");
//#endif
//    int maxCardTypes = 27;
//    int passing = 1;
//    int j;
//    G.deckCount[p] = maxDeckCount;
//
//
//    // Check every card in the game.
//    for(i=0; i<maxCardTypes && passing == 1; i++) {
//        // reset
//        G.handCount[p] = 0;
//        G.deckCount[p] = maxDeckCount;
//
//#if (NOISY_TEST == 1)
//        printf("\nChecking card %d\n", i);
//#endif
//        if(i < 4 || i > 6) { // only test on non-treasure cards.
//            for(j=0; j<maxDeckCount; j++) {
//                G.deck[p][0] = i;    
//            }
//
//            cardEffect(adventurer, 0, 0, 0, &G, 0, 0);
//            passing = assertion(G.handCount[p]>1);
//
//            if(!passing) {
//                printf("ERROR: Card %d counted as a treasure card!\n", i);
//                testsPassed = 0;
//            }
//
//        }
//    }
//
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
int assertion(int statement) {
    if(statement<=0) { // if test statement is false
#if (NOISY_TEST == 1)
        printf("TEST FAILED! ");    
#endif
        return 0;
    }

#if (NOISY_TEST == 1)
    printf("TEST PASSED\n\n");    
#endif
    return 1;
}
