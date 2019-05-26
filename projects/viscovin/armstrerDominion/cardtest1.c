/*
	Software Enginnering II 			Nadia M Viscovich
	CS-362-400							Assignment-3
	
	CARDTEST1.C: Testing Smithy function
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
	int c,d, handNum;
	int numPlayers = 2;
	int maxHandCount=10;
	int currentPlayertestState;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int controlHand[maxHandCount];
	
	// Cards being tested and their values are: adventurer = 7 ,smithy = 13, council_room = 8, village = 14, great_hall = 16
	controlHand[0]= adventurer;
	controlHand[1]= smithy;
	controlHand[2]= steward;
	controlHand[3]= salvager;
	controlHand[4]= curse;
	
	memset(&testState, 23, sizeof(struct gameState));   			// clear the game state
    initializeGame(numPlayers, k, seed, &testState); 				// initialize a new game  
	memcpy(testState.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand	
	memcpy(&state, &testState, sizeof(struct gameState));			// copy state 
	
	printf ("-------------     Testing smithy()     -------------\n");
	//------------------------     Test 1     ------------------------------------//
#if (NOISY_TEST == 1)
	printf("Test that decks are the same for Player 2 before and after Player 1 plays smithy card.\n");
#endif
	//Change whoseTurn to reflect Players 2 cards
	testState.whoseTurn =  1;	
	currentPlayertestState = whoseTurn(&testState); 
	
#if (NOISY_TEST == 1)	
	printf("Whose turn in testState-> %d.\n", currentPlayertestState+1);
	printf("Player 2 deck BEFORE Player 1 plays smithy.\n");
	for (handNum =0; handNum<maxHandCount; handNum++){
		d=testState.deck[currentPlayertestState][handNum];
		printf ("Deck card %d is %d. \n",handNum+1,d);
	}
#endif

	//Change whoseTurn to Player 1 before playing smithy 
	testState.whoseTurn = 0;	
	currentPlayertestState = whoseTurn(&testState); 
	
#if (NOISY_TEST == 1)	
	printf("Whose turn in testState-> %d, before playing smithy.\n", currentPlayertestState+1);
#endif

	cardEffect(smithy, choice1, choice2, choice3, &testState, 1, NULL);

	//Change whoseTurn to reflect Players 2 cards
	testState.whoseTurn =  1;
	currentPlayertestState = whoseTurn(&testState); 	
	
#if (NOISY_TEST == 1)	
	printf("Whose turn in testState-> %d.\n", currentPlayertestState+1);
	printf("Player 2 deck AFTER Player 1 plays smithy.\n");
	
	for (handNum =0; handNum<maxHandCount; handNum++){
		d=testState.deck[currentPlayertestState][handNum];
		printf ("Deck card %d is %d.  \n",handNum+1,d);
	}
#endif
	
	//Compare deck of testState player 2 to deck state player 2	
	for (handNum =0; handNum<maxHandCount; handNum++){
		if (testState.deck[1][handNum] == state.deck[1][handNum])
			printf("Deck for P2 same before and after P1 plays smithy TEST SUCCESSFULLY COMPLETED.\n");
		else 
			printf("Deck for P2 same before and after P1 plays smithy TEST FAILED!\n");
	}
	
	//------------------------     Test 2     ------------------------------------//	
#if (NOISY_TEST == 1)
	printf("Test that the cards added to hand are either coppers(4) or estate(1).\n");
#endif	
	testState.whoseTurn = 0;	
	handNum=1;
	c = handCard(handNum, &testState);
#if (NOISY_TEST == 1)
	printf("Card %d value: %d. Expected value 1 or 4.\n" ,handNum+1,c);
#endif
	if ((c == 1) || (c == 4))
		printf("Drawn card came from deck TEST SUCCESSFULLY COMPLETED.\n");
	else 
		printf("Drawn card came from deck TEST FAILED!\n");
	
  return 0;
}
