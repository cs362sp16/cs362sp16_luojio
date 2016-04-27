#include "../dominion.c"
#include "../rngs.c"
#include "../myassert.h"

/*************************************
Test for "numHandCards()" function
*************************************/

int main(){
	printf("\n*********************************************************\n\n");
	printf("                      Unit Test 4\n\n");
	printf("*********************************************************\n");
//	Test Initialization
	int i, temp1,temp2;
	srand (time(NULL));
	struct gameState game;
	int cards[10] = {estate, duchy, adventurer, embargo, sea_hag, feast, gardens, mine, tribute, outpost}; 
	int playerNum = 4;
	int theplayer = 2;

// Random settings
	int ramdomSeed = rand() % 99999 + 1;	
	int bonus = rand() % 10;
	int handNum = rand() % MAX_HAND;
	//initializeGame(playerNum, cards, ramdomSeed, &game);

	check_functions(initializeGame(playerNum, cards, ramdomSeed, &game));

	// should equal since drawCard from player
	temp1 = numHandCards(&game);
	drawCard(game.whoseTurn, &game);
	check_equal(temp1, numHandCards(&game)-1);


	printf("Function 'numHandCards()': TEST SUCCESSFULLY COMPLETED\n\n");
	return 0;
}
