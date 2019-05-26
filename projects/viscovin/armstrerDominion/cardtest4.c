/*
	Software Enginnering II 			Nadia M Viscovich
	CS-362-400							Assignment-3
	
	CARDTEST4.C: Testing Salvager function
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
	int maxHandCount=10;
	int pre, post;
	int currentPlayerstate, currentPlayertestState;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int controlHand[maxHandCount];
	
	// Cards being tested and their values are: adventurer = 7 ,smithy = 13, steward = 18, salvager = 24, curse = 0
	controlHand[0]= adventurer;
	controlHand[1]= smithy;
	controlHand[2]= steward;
	controlHand[3]= salvager;
	controlHand[4]= curse;
	
	memset(&testState, 23, sizeof(struct gameState));   			// clear the game state
    initializeGame(numPlayers, k, seed, &testState); 				// initialize a new game  
	memcpy(testState.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand	
	memcpy(&state, &testState, sizeof(struct gameState));			// copy state 
	
	printf ("-------------     Testing salvager()     -------------\n");
	//------------------------     Test 1     ------------------------------------//	
#if (NOISY_TEST == 1)
	printf("Test that +1 Buy was added.\n");
#endif

	pre = testState.numBuys; 
	
#if (NOISY_TEST == 1)
	printf ("Pre NumBuys = %d.\n",pre);
#endif

	cardEffect(salvager, choice1, choice2, choice3, &testState, 3, NULL);
	post = testState.numBuys;

#if (NOISY_TEST == 1)
	printf ("Post NumBuys = %d.\n", post); 
#endif
	
	if (post == pre + 1)
		printf("+1 Buys TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("+1 Buys TEST FAILED!\n");
	
	//------------------------     Test 2     ------------------------------------//
	initializeGame(numPlayers, k, seed, &testState); 				// initialize a new game  
	memcpy(testState.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand	
	memcpy(&state, &testState, sizeof(struct gameState));			// copy state
	testState.whoseTurn =  0;	
	currentPlayertestState = whoseTurn(&testState); 
	state.whoseTurn =  0;	
	currentPlayerstate = whoseTurn(&testState); 
#if (NOISY_TEST == 1)
	printf("Test that hands stays the same when we choose not to trash any cards.\n");
#endif

	cardEffect(salvager, choice1, choice2, choice3, &testState, 3, NULL);
	
	for (handNum =0; handNum<maxHandCount; handNum++){
		if (handNum == 3)  //skipping card player as it will be discarded.
			handNum++;
		if (testState.hand[0][handNum] == state.hand[0][handNum])
			printf("Hand stays the same when choice1=0  TEST SUCCESSFULLY COMPLETED.\n");
		else 
			printf("Hand stays the same when choice1=0 TEST FAILED!\n");
	}
	
		
	//------------------------     Test 3     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test that the correct amount of coins where received when a cards is trashed.\n");
#endif
//------------------------     Test 3A     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Boundary case hand position 0.\n");
#endif
	initializeGame(numPlayers, k, seed, &testState); 				// initialize a new game  
	memcpy(testState.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand	
	choice1=0; 
	pre = testState.coins;
	cardEffect(salvager, choice1, choice2, choice3, &testState, 3, NULL);
	post = testState.coins;
	if (post == pre + 6)
		printf("Trash hand position 0 extra coins TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("Trash hand position 0 extra coins TEST FAILED!\n");
	
//------------------------     Test 3B    ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Boundary case hand position 4.\n");
#endif
	
	initializeGame(numPlayers, k, seed, &testState); 				// initialize a new game  
	memcpy(testState.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand	
	choice1=4; 
	pre = testState.coins;
	cardEffect(salvager, choice1, choice2, choice3, &testState, 3, NULL);
	post = testState.coins;
	if (post == pre )
		printf("Trash hand position 4 extra coins  TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("Trash hand position 4 extra coins TEST FAILED!\n");

	//------------------------     Test 4     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test that Salvager Card (24) has been discarded and is no longer in players hand.\n");
#endif	
	handNum=3;
	c = handCard(handNum, &testState);
#if (NOISY_TEST == 1)
	printf("Card %d value: %d. Expected value != 24.\n" ,handNum+1,c);
#endif
	if (c == 24) 
		printf("Salvager discarded TEST FAILED!\n");
	else 
		printf("Salvager discarded TEST SUCCESSFULLY COMPLETED.\n");
	
	return 0;
}