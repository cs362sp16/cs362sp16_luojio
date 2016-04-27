#include "../dominion.c"
#include "../rngs.c"
#include "../myassert.h"

/*************************************
Test for "great_hall" card
*************************************/

int main(){
	printf("\n*********************************************************\n\n");
	printf("                      Card Test 3\n\n");
	printf("*********************************************************\n");
	
//	Test Initialization
	int i, temp1, temp2, temp3, temp4;
	srand (time(NULL));
	struct gameState game;
	int cards[10] = {estate, duchy, adventurer, embargo, sea_hag, feast, gardens, mine, tribute, outpost}; 
	int playerNum = 4;

// Random settings
	int ramdomSeed = rand() % 99999 + 1;	
	int bonus = rand() % 10;
	int handNum = rand() % MAX_HAND;

	check_functions(initializeGame(playerNum, cards, ramdomSeed, &game));
	int theplayer = whoseTurn(&game);

	// check card effect is to add 1 cards to hand and discard a card, so handCound shoud not be changed
	temp1 = game.handCount[theplayer];
	check_functions(cardEffect(great_hall, 0, 0, 0, &game, 0, 0));
	temp2 = game.handCount[theplayer];
	check_equal(temp1, temp2);

	printf("Card 'great_hall': TEST SUCCESSFULLY COMPLETED\n\n");
	return 0;
}
