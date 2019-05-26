/*
	Software Enginnering II 			Nadia M Viscovich
	CS-362-400							Assignment-3
	
	UNITTEST3.C: Testing village function
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
	struct gameState testState;
	int c, handNum;
	int numPlayers = 2;
	int maxHandCount=5;
	//int currentPlayertestState;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int pre=0,post=0, pre1=0, post1=0;
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
	
	//currentPlayertestState = whoseTurn(&testState);  

	printf ("-------------     Testing village()     -------------\n");
	//------------------------     Test 1     ------------------------------------//
#if (NOISY_TEST == 1)		
	printf("Number of actions BEFORE playing village = 1.\n"); 
#endif	
	pre1 = testState.numActions; 
	if (testState.numActions == 1)
		printf("Actions = 1 TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("Actions = 1 TEST FAILED!\n");

	//------------------------     Test 2     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test that 1 card is added to the player's hand.\n");
#endif
	//Get the number of cards in hand before playing card
	pre = numHandCards(&testState);
	
#if (NOISY_TEST == 1)	
	printf("Number of cards on hand BEFORE playing village: %d\n",pre); 
#endif
	cardEffect(village, choice1, choice2, choice3, &testState, 3, NULL);
	
	//Get the number of cards in hand after playing card
	post = numHandCards(&testState);
	
#if (NOISY_TEST == 1)		
	printf("Number of cards on hand AFTER playing village: %d\n",post); 
#endif	

	if (post == pre)
		printf("+1 Card TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("+1 Card TEST FAILED!\n");

	//------------------------     Test 3     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Actions before playing Village = %d.\n", pre1);
	printf("Number of actions AFTER playing village increased = 3.\n"); 
#endif	
	post1 = testState.numActions; 
	printf("Actions after playing Village = %d.\n", post1);
	if (testState.numActions == 3)
		printf("+2 Actions TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("+2 Actions TEST FAILED!\n");	

	//------------------------     Test 4     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test that village Card (14) has been discarded and is no longer in players hand.\n");
#endif	
	handNum=3;
	c = handCard(handNum, &testState);
#if (NOISY_TEST == 1)
	printf("Card %d value: %d. Expected value != 14.\n" ,handNum+1,c);
#endif
	if (c == 14) 
		printf("Village discarded TEST FAILED!\n");
	else 
		printf("Village discarded TEST SUCCESSFULLY COMPLETED.\n");
	
	return 0;
}