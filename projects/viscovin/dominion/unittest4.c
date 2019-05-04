/*
	Software Enginnering II 			Nadia M Viscovich
	CS-362-400							Assignment-3
	
	UNITTEST4.C: Testing great_hall function
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
	int currentPlayertestState;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int pre,post;
	int prePoints,postPoints;
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
	
	currentPlayertestState = whoseTurn(&testState); 

	printf ("-------------     Testing great_hall()     -------------\n");
	//------------------------     Test 1     ------------------------------------//
#if (NOISY_TEST == 1)		
	printf("Number of actions BEFORE playing great_hall = 1.\n"); 
#endif	

	if (testState.numActions == 1)
		printf("Actions = 1 TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("Actions = 1 TEST FAILED!\n");

	//------------------------     Test 2     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test that 1 card is added to the player's hand.\n");
#endif
	//Get the number of cards in hand and victory points before playing card
	pre = numHandCards(&testState);
	prePoints = scoreFor (0, &testState);
	
#if (NOISY_TEST == 1)	
	printf("Number of cards on hand BEFORE playing great_hall: %d\n",pre); 
#endif
	
	cardEffect(great_hall, choice1, choice2, choice3, &testState, 4, NULL);
	
	//Get the number of cards and victory points in hand after playing card
	post = numHandCards(&testState);
	postPoints = scoreFor (0, &testState);
	
#if (NOISY_TEST == 1)		
	printf("Number of cards on hand AFTER playing great_hall: %d\n",post); 
#endif	

	if (post == pre)
		printf("+1 Card TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("+1 Card TEST FAILED!\n");
	
	//------------------------     Test 3     ------------------------------------//
#if (NOISY_TEST == 1)		
	printf("Number of actions AFTER playing great_hall increased = 2.\n"); 
#endif	

	if (testState.numActions == 2)
		printf("+1 Action TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("+1 Action TEST FAILED!\n");	

	//------------------------     Test 4     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test that 1 point is added to the player's victory points.\n");
#endif

#if (NOISY_TEST == 1)	
	printf("Number of points on hand BEFORE playing great_hall: %d\n",prePoints); 
#endif

#if (NOISY_TEST == 1)		
	printf("Number of points on hand AFTER playing great_hall: %d\n",postPoints); 
#endif	
	
	if (postPoints == prePoints+1)
		printf("+1 Point TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("+1 Point TEST FAILED!\n");

	//------------------------     Test 5     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test that great_hall Card (16) has been discarded and is no longer in players hand.\n");
#endif	
	handNum=4;
	c = handCard(handNum, &testState);
#if (NOISY_TEST == 1)
	printf("Card %d value: %d. Expected value != 16.\n" ,handNum+1,c);
#endif
	if (c == 16) 
		printf("Great_hall discarded TEST FAILED!\n");
	else 
		printf("Great_hall discarded TEST SUCCESSFULLY COMPLETED.\n");
	
	
	return 0;
}
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	