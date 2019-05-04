/*
	Software Enginnering II 			Nadia M Viscovich
	CS-362-400							Assignment-3
	
	UNITTEST2.C: Testing council_room function
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
	int c, draw, handNum;
	int numPlayers = 2;
	int maxHandCount=5;
	int currentPlayertestState;
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
	
	memset(&testState, 23, sizeof(struct gameState));   		// clear the game state
    initializeGame(numPlayers, k, seed, &testState); 				// initialize a new game  
	memcpy(testState.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand	
	
	currentPlayertestState = whoseTurn(&testState); 

	printf ("-------------     Testing council_room()     -------------\n");
	//------------------------     Test 1     ------------------------------------//
#if (NOISY_TEST == 1)		
	printf("Number of buys BEFORE playing council_rooms = 1.\n"); 
#endif	

	if (testState.numBuys == 1)
		printf("Buys = 1 TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("Buys = 1 TEST FAILED!\n");
	
	//------------------------     Test 2     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test that 4 cards are added to the player's hand.\n");
#endif
	//Get the number of cards in hand before playing card
	pre = numHandCards(&testState);
	
#if (NOISY_TEST == 1)	
	printf("Number of cards on hand BEFORE playing council_room: %d\n",pre); 
#endif
	cardEffect(council_room, choice1, choice2, choice3, &testState, 2, NULL);
	
	//Get the number of cards in hand after playing card
	post = numHandCards(&testState);
	
#if (NOISY_TEST == 1)		
	printf("Number of cards on hand AFTER playing council_room: %d\n",post); 
#endif	

	if (post == pre + 3)
		printf("+4 Cards TEST SUCCESSFULLY COMPLETED.\n");
	else
		printf("+4 Cards TEST FAILED!\n");
		
	//------------------------     Test 3     ------------------------------------//
#if (NOISY_TEST == 1)		
	printf("Number of buys AFTER playing council_rooms increased = 2.\n"); 
#endif	

	if (testState.numBuys == 2)
		printf("+1 Buys TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("+1 Buys TEST FAILED!\n");
	
	//------------------------     Test 4     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test that council_room Card (8) has been discarded and is no longer in players hand.\n");
#endif	
	handNum=2;
	c = handCard(handNum, &testState);
#if (NOISY_TEST == 1)
	printf("Card %d value: %d. Expected value != 8.\n" ,handNum+1,c);
#endif
	if (c == 8) 
		printf("Council_room discarded TEST FAILED!\n");
	else 
		printf("Council_room discarded TEST SUCCESSFULLY COMPLETED.\n");

	//------------------------     Test 5     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test that player 2 drew one card to its hand.\n");
#endif	
	testState.whoseTurn = 1;			//Move turn to player 2
	draw = numHandCards(&testState);	//Get the number of cards on player's 2 hand
	if (draw != 1)
		printf("+1 Card other players TEST FAILED!\n");
	else 
		printf("+1 Card other players TEST SUCCESSFULLY COMPLETED.\n");

  return 0;
}















