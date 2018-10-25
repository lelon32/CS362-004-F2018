/************************************************************************* 
 * Program: unittest1 
 * Author: Long Le
 * Date: 24-Oct-2018 
 * Class: CS362
 * Instructor: Jaki Shaik
 * Assignment 3 
 * Description: Unit test program for function adventurerCard().
 * 1. Tests how many treasure cards can be drawn.
 * 2. Tests if other cards count as treasure cards.
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
    int p=1, handCount=0;
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

    printf ("TESTING adventurerCard():\n\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[p] = handCount;                 // set the number of cards on hand
    memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to adventurer 

    
    // Clear all treasure cards.
    int count;
    for(count=0; count<maxDeckCount; count++) {
        G.deck[p][count] = adventurer; 
    }

    G.deckCount[p] = maxDeckCount; // reset
   
/***************************TEST 1*******************************/
         /**Check how many treasure cards are added*/

    // Put 1 treasure cards in deck
    G.deck[p][0] = copper;
#if (NOISY_TEST == 1)
    printf("Test 1 - check how many treasure cards are added.\n\n");
#endif

#if (NOISY_TEST == 1)
    printf("Testing with 1 treasure card in deck.\nOnly 1 card should be added to hand.\n");
#endif
    int origCardsInHand = G.handCount[p];

    adventurerCard(&G, p);

#if (NOISY_TEST == 1)
    testsPassed = assertion(G.handCount[p]==origCardsInHand+1);
    if(!testsPassed) {
        printf("%d card(s) were added.\n", G.handCount[p]-origCardsInHand);
    }
#endif

    origCardsInHand = G.handCount[p];
    G.deckCount[p] = maxDeckCount; // reset

#if (NOISY_TEST == 1)
    printf("Testing with 2 treasure cards in deck.\n2 cards should be added to hand.\n");
#endif
    // Put 2 treasure cards in deck
    G.deck[p][0] = copper; 
    G.deck[p][1] = silver; 
    adventurerCard(&G, p);

#if (NOISY_TEST == 1)
    testsPassed = assertion(G.handCount[p]==origCardsInHand+2);
    if(!testsPassed) {
        printf("%d card(s) were added.\n", G.handCount[p]-origCardsInHand);
    }
#endif

    origCardsInHand = G.handCount[p];
    G.deckCount[p] = maxDeckCount; // reset

#if (NOISY_TEST == 1)
    printf("Testing with 3 treasure cards in deck.\nOnly 2 cards should be added to hand.\n");
#endif
    // Put 3 treasure cards in deck
    G.deck[p][0] = copper; 
    G.deck[p][1] = silver;
    G.deck[p][2] = gold; 
    adventurerCard(&G, p);

#if (NOISY_TEST == 1)
    testsPassed = assertion(G.handCount[p]==origCardsInHand+2);
    if(!testsPassed) {
        printf("%d card(s) were added.\n", G.handCount[p]-origCardsInHand);
    }
#endif

/***************************TEST 2*******************************/
/**Check if cards other than treasure cards are counted as treasure cards*/
#if (NOISY_TEST == 1)
    printf("\nTest 3 - check if other cards are counted as a treasure card.\n\n");
#endif
    int maxCardTypes = 27;
    int passing = 1;
    int j;
    G.deckCount[p] = maxDeckCount;


    // Check every card in the game.
    for(i=0; i<maxCardTypes && passing == 1; i++) {
        // reset
        G.handCount[p] = 0;
        G.deckCount[p] = maxDeckCount;

#if (NOISY_TEST == 1)
        printf("\nChecking card %d\n", i);
#endif
        if(i < 4 || i > 6) { // only test on non-treasure cards.
            for(j=0; j<maxDeckCount; j++) {
                G.deck[p][0] = i;    
            }

            adventurerCard(&G, p);
            passing = assertion(G.handCount[p]>1);

            if(!passing) {
                printf("Card %d counted as a treasure card!\n", i);
                testsPassed = 0;
                break;
            }

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
    printf("TEST PASSED\n\n");    
#endif
    return 1;
}
