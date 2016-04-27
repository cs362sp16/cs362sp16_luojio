#include "../dominion.c"
#include "../rngs.c"
#include "../myassert.h"

/*************************************
Test for "adventurer" card
*************************************/

int main(){
	printf("\n*********************************************************\n\n");
	printf("                      Card Test 2\n\n");
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

	temp1 = game.handCount[theplayer];
	temp3 = game.deckCount[theplayer];

	check_functions(cardEffect(adventurer, 0, 0, 0, &game, 0, 0));
	temp2 = game.handCount[theplayer];
	temp4 = game.deckCount[theplayer];

	check_equal(temp1, temp2);
	check_equal(temp3, temp4);

	printf("Card 'adventurer': TEST SUCCESSFULLY COMPLETED\n\n");
	return 0;
}
