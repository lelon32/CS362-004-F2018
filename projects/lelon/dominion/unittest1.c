/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int assertion(int a); 

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int testsPassed=0;
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p=1, r, handCount=0;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    int cards[MAX_HAND]; 
    
    for (i = 0; i < handCount; i++)
    {
        cards[i] = adventurer;
    }

    printf ("TESTING adventurerCard():\n\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[p] = handCount;                 // set the number of cards on hand
    memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to adventurer 

    G.deckCount[p] = 2; // reset

    
    // Clear all treasure cards.
    int count;
    for(count=0; count<4; count++) {
        G.deck[p][count] = adventurer; 
    }

    G.deckCount[p] = 4; // reset
   
    // Put 1 treasure cards in deck
    G.deck[p][0] = copper;

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
    G.deckCount[p] = 4; // reset

#if (NOISY_TEST == 1)
    printf("Testing with 2 treasure cards in deck.\n2 cards should be added to hand.\n");
#endif
    // Put 2 treasure cards in deck
    G.deck[p][0] = copper; 
    G.deck[p][1] = copper; 
    adventurerCard(&G, p);

#if (NOISY_TEST == 1)
    testsPassed = assertion(G.handCount[p]==origCardsInHand+2);
    if(!testsPassed) {
        printf("%d card(s) were added.\n", G.handCount[p]-origCardsInHand);
    }
#endif

    origCardsInHand = G.handCount[p];
    G.deckCount[p] = 4; // reset

#if (NOISY_TEST == 1)
    printf("Testing with 3 treasure cards in deck.\nOnly 2 cards should be added to hand.\n");
#endif
    // Put 3 treasure cards in deck
    G.deck[p][0] = copper; 
    G.deck[p][1] = copper;
    G.deck[p][2] = copper; 
    adventurerCard(&G, p);

#if (NOISY_TEST == 1)
    testsPassed = assertion(G.handCount[p]==origCardsInHand+2);
    if(!testsPassed) {
        printf("%d card(s) were added.\n", G.handCount[p]-origCardsInHand);
    }
#endif

//#if (NOISY_TEST == 1)
//    printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
//#endif
//    assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct

//    memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
//    updateCoins(p, &G, bonus);
//#if (NOISY_TEST == 1)
//    printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
//#endif
//    assert(G.coins == handCount * 2 + bonus); // check if the number of coins is correct
//
//    memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
//    updateCoins(p, &G, bonus);
//#if (NOISY_TEST == 1)
//    printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
//#endif
//    assert(G.coins == handCount * 3 + bonus); // check if the number of coins is correct

    if(testsPassed) {
        printf("\nALL TESTS SUCCESSFULLY PASSED!\n");
    } else {
        printf("\nTEST FAILURES DETECTED\n");
    } 

    return 0;
}

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
