/*
	Software Enginnering II 			Nadia M Viscovich
	CS-362-400							Assignment-3
	
	CARDTEST3.C: Testing Steward function
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
	int pre,post;
	int currentPlayertestState;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int controlHand[maxHandCount];
	
	// Cards being tested and their values are: adventurer = 7 ,smithy = 13, steward = 18, salvager = 24, curse = 0
	controlHand[0]= adventurer;
	controlHand[1]= smithy;
	controlHand[2]= steward;
	controlHand[3]= curse;
	controlHand[4]= curse;
	
	memset(&testState, 23, sizeof(struct gameState));   			// clear the game state
    initializeGame(numPlayers, k, seed, &testState); 				// initialize a new game  
	memcpy(testState.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand	
	memcpy(&state, &testState, sizeof(struct gameState));			// copy state 
	
	testState.whoseTurn =  0;	
	currentPlayertestState = whoseTurn(&testState); 


	printf ("-------------     Testing steward()     -------------\n");
	//------------------------     Test 1     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("CHOICE 1 = +2 Cards.\n");
#endif
	choice1 = 1;
	pre = numHandCards(&testState);
	cardEffect(steward, choice1, choice2, choice3, &testState, 2, NULL);
	post = numHandCards(&testState);

	if (post == pre + 1)
		printf("+2 Cards TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("+2 Cards TEST FAILED!\n");


	//------------------------     Test 2     ------------------------------------//
	initializeGame(numPlayers, k, seed, &testState); 				// initialize a new game  
	memcpy(testState.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand
#if (NOISY_TEST == 1) 
	printf("CHOICE 2 = +2 Coins.\n");
#endif
	choice1 = 2;
	pre = testState.coins;
	cardEffect(steward, choice1, choice2, choice3, &testState, 2, NULL);
	post = testState.coins; 

	
	if (post == pre + 2)
		printf("+2 Coins TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("+2 Coins TEST FAILED!\n");

	//------------------------     Test 3     ------------------------------------//
	initializeGame(numPlayers, k, seed, &testState); 				// initialize a new game  
	memcpy(testState.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand
#if (NOISY_TEST == 1)
	printf("CHOICE 3 = Trash 2 Cards.\n");
#endif
	initializeGame(numPlayers, k, seed, &testState); 				// initialize a new game  
	memcpy(testState.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand
	choice1 = 3;
	choice2 = 3; 	//Trash curse 
	choice3 = 4; 	//Trash curse
	cardEffect(steward, choice1, choice2, choice3, &testState, 2, NULL);

	if (testState.hand[currentPlayertestState][3] == -1 &&  testState.hand[currentPlayertestState][3] == -1)
		printf("Trash correct cards TEST SUCCESSFULLY COMPLETED.\n"); 
	else 
		printf("Trash correct cards TEST FAILED!\n");
		

	//------------------------     Test 4     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test that Steward Card (18) has been discarded and is no longer in players hand.\n");
#endif	
	
	handNum=2;
	c = handCard(handNum, &testState);
	
#if (NOISY_TEST == 1)
	printf("Card %d value: %d. Expected value != 18.\n" ,handNum+1,c);
#endif

	if (c == 18) 
		printf("Steward discarded TEST FAILED!\n");
	else 
		printf("Steward discarded TEST SUCCESSFULLY COMPLETED.\n");
	
	return 0;
}