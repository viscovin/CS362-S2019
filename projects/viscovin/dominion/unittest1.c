/*
	Software Enginnering II 			Nadia M Viscovich
	CS-362-400							Assignment-3
	
	UNITTEST1.C: Testing Smithy function
--------------------------------------------------------------*/
			
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
	struct gameState state, testState;
	int c, handNum;
	int numPlayers = 2;
	int maxHandCount=7;
	int currentPlayerstate, currentPlayertestState;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int pre,post;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int controlHand[maxHandCount];
	
	// Cards being tested and their values are: adventurer = 7 ,smithy = 13, council_room = 8, village = 14, great_hall = 16
	controlHand[0]= adventurer;
	controlHand[1]= smithy;
	controlHand[2]= council_room;
	controlHand[3]= village;
	controlHand[4]= great_hall;
	
	memset(&testState, 23, sizeof(struct gameState));   			// clear the game state
    initializeGame(numPlayers, k, seed, &testState); 				// initialize a new game  
	memcpy(testState.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand	
	

	printf ("-------------     Testing smithy()     -------------\n");
	//------------------------     Test 1     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test that it is the turn of player 1 for both state and testState.\n");
#endif
	currentPlayerstate = whoseTurn(&state);	
	currentPlayertestState = whoseTurn(&testState); 
	
	if (currentPlayerstate != currentPlayertestState)
		printf("whose turn TEST FAILED!\n");
	else 
		printf("whose turn TEST SUCCESSFULLY COMPLETED.\n");
	
#if (NOISY_TEST == 1)
	printf("PLAYER %d\n", currentPlayertestState);
#endif
	//------------------------     Test 2     ------------------------------------//	
	//Get the number of cards in hand before playing card
	pre = numHandCards(&testState);
	
#if (NOISY_TEST == 1)	
	printf("Number of cards on hand BEFORE playing Smithy: %d\n",pre); 
#endif
	cardEffect(smithy, choice1, choice2, choice3, &testState, 1, NULL);
	
	//Get the number of cards in hand after playing card
	post = numHandCards(&testState);
	
#if (NOISY_TEST == 1)		
	printf("Number of cards on hand AFTER playing Smithy: %d\n",post); 
#endif	

#if (NOISY_TEST == 1)
	printf("Test that 3 cards were drawn and added to current players hand.\n");
#endif
	if (post == pre + 2)
		printf("+3 Cards TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("+3 Cards TEST FAILED!\n");
	
	//------------------------     Test 3     ------------------------------------//	
#if (NOISY_TEST == 1)
	printf("Test that Smithy Card (13) has been discarded and is no longer in players hand.\n");
#endif	
	handNum=1;
	c = handCard(handNum, &testState);
#if (NOISY_TEST == 1)
	printf("Card %d value: %d. Expected value != 13.\n" ,handNum+1,c);
#endif
	if (c == 13) 
		printf("Smithy discarded TEST FAILED!\n");
	else 
		printf("Smithy discarded TEST SUCCESSFULLY COMPLETED.\n");
	
  return 0;
}
