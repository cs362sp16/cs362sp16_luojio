#include "../dominion.c"
#include "../rngs.c"
#include "../myassert.h"
#include <assert.h>
/*************************************
Test for "isGameOver()" function
*************************************/

int main(){
	printf("\n*********************************************************\n\n");
	printf("                      Unit Test 2\n\n");
	printf("*********************************************************\n");
//	Test Initialization
	int i, temp, coin_result=0;
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
	check_functions(isGameOver(&game));

	// should return 0
	temp = isGameOver(&game);		
	check_equal(temp, 0);

	//should return 1 since stack of Province cards is empty
	game.supplyCount[province] = 0;
	temp = isGameOver(&game);		
	check_equal(temp, 1);

	// should return 0 since three supply pile are at 0, which the game ends
	game.supplyCount[province] = 12;
	game.supplyCount[estate] = 0;
	game.supplyCount[adventurer] = 0;
	game.supplyCount[embargo] = 0;
	temp = isGameOver(&game);		
	check_equal(temp, 1);

	// should return 0 since NOT three supply pile are at 0, which the game ends
	game.supplyCount[estate] = 1;
	game.supplyCount[adventurer] = 0;
	game.supplyCount[embargo] = 0;
	temp = isGameOver(&game);		
	check_equal(temp, 0);

	printf("Function 'isGameOver()': TEST SUCCESSFULLY COMPLETED\n\n");
	return 0;
}
