/*
	Software Enginnering II 			Nadia M Viscovich
	CS-362-400							Assignment-3
	
	CARDTEST2.C: Testing Adventurer function
-------------------------------------------------------------*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
// set NOISY_TEST to 1 to see printfs on output
#define NOISY_TEST 0

int main (int argc, char** argv) {
	int seed = 1000;
	struct gameState testState;
	int c, handNum;
	int numPlayers = 2;
	int maxHandCount=7;
	int currentPlayertestState;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int controlHand[maxHandCount];
	int controlDeck[5];
	
	// Cards being tested and their values are: adventurer = 7 ,smithy = 13, steward = 18, salvager = 24, curse = 0
	controlHand[0]= adventurer;
	controlHand[1]= smithy;
	controlHand[2]= steward;
	controlHand[3]= salvager;
	controlHand[4]= curse;
	
	//set player decks to only have 2 treasures and 8 estates.
    controlDeck[0]= estate;
	controlDeck[1]= estate;
	controlDeck[2]= estate;
	controlDeck[3]= copper;
	controlDeck[4]= copper; 
	
	memset(&testState, 23, sizeof(struct gameState));   			// clear the game state
    initializeGame(numPlayers, k, seed, &testState); 				// initialize a new game  
	memcpy(testState.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand	
	memcpy(testState.deck[0], controlDeck, sizeof(int) * MAX_HAND); // set cards according to controlHand


	printf ("-------------     Testing adventurer()     -------------\n");
	//------------------------     Test 1     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test the amount of treasure on hand before and after playing Adventrer card.\n");
#endif

	currentPlayertestState = whoseTurn(&testState); 

#if (NOISY_TEST == 1)	
	for (handNum =0; handNum<maxHandCount; handNum++){
		d=testState.hand[currentPlayertestState][handNum];
		printf ("Hand card %d is %d.  \n",handNum+1,d);
	}
#endif

	c=testState.discardCount[currentPlayertestState];

#if (NOISY_TEST == 1)
	printf ("Discard Count before is %d.  \n",c);
#endif	
	
	cardEffect(adventurer, choice1, choice2, choice3, &testState, 1, NULL);

#if (NOISY_TEST == 1)		
	for (handNum =0; handNum<maxHandCount; handNum++){
		d=testState.hand[currentPlayertestState][handNum];
		printf ("Hand card %d is %d.  \n",handNum+1,d);
	}		
#endif		

	c=testState.discardCount[currentPlayertestState];

#if (NOISY_TEST ==1)
	printf ("Discard Count is after is %d.  \n",c);
#endif

	if (testState.hand[currentPlayertestState][5]==4 && testState.hand[currentPlayertestState][6]==4)
		printf("+2 Treasure TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("+2  TEST FAILED!\n");

	//------------------------     Test 2     ------------------------------------//	
#if (NOISY_TEST == 1)	
	printf("Test the number of cards on discard pile after playing Adventurer.\n"); 
#endif

	if (c != 0)
		printf("Cards discarded TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("Cards discarded TEST FAILED!\n");
	
	//------------------------     Test 3     ------------------------------------//	
#if (NOISY_TEST == 1)
	printf("Test that Adventurer Card (7) has been discarded and is no longer in players hand.\n");
#endif	

	handNum=0;
	c = handCard(handNum, &testState);
	
#if (NOISY_TEST == 1)
	printf("Card %d value: %d. Expected value != 7.\n" ,handNum+1,c);
#endif

	if (c == 7) 
		printf("Adventurer discarded TEST FAILED!\n");
	else 
		printf("Adventurer discarded TEST SUCCESSFULLY COMPLETED.\n");
	
  return 0;
}
