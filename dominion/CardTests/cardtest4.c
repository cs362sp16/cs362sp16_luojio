#include "../dominion.c"
#include "../rngs.c"
#include "../myassert.h"

/*************************************
Test for "steward" card
*************************************/

int main(){
	printf("\n*********************************************************\n\n");
	printf("                      Card Test 4\n\n");
	printf("*********************************************************\n");
//	Test Initialization
	int i, temp1, temp2, temp3, temp4;
	srand (time(NULL));
	struct gameState game1;
	struct gameState game2;
	struct gameState game3;
	int cards[10] = {estate, duchy, adventurer, embargo, sea_hag, feast, gardens, mine, tribute, outpost}; 
	int playerNum = 4;
	int theplayer;

// Random settings
	int ramdomSeed = rand() % 99999 + 1;	
	int bonus = rand() % 10;
	int handNum = rand() % MAX_HAND;

	check_functions(initializeGame(playerNum, cards, ramdomSeed, &game1));
	check_functions(initializeGame(playerNum, cards, ramdomSeed, &game2));
	check_functions(initializeGame(playerNum, cards, ramdomSeed, &game3));
	
// Test of choice 1: draw 2 cards but discard 1;
	theplayer = whoseTurn(&game1);
	temp1 = game1.handCount[theplayer];
	check_functions(cardEffect(steward, 1, 0, 0, &game1, 0, 0));
	temp2 = game1.handCount[theplayer];
	check_equal(temp1,temp2-1);	

// Test of choice 2: add 2 coins
	theplayer = whoseTurn(&game2);
	temp1 = game2.coins;
	check_functions(cardEffect(steward, 2, 0, 0, &game2, 0, 0));
	temp2 = game2.coins;
	check_equal(temp1,temp2-2);	

// Test of choice 3: trash 2 cards in hand, so sum up 3 cards in hand are discarded
	theplayer = whoseTurn(&game3);
	temp1 = game3.handCount[theplayer];
	check_functions(cardEffect(steward, 3, 2, 2, &game3, 0, 0));
	temp2 = game3.handCount[theplayer];
	check_equal(temp1,temp2+3);	

	printf("Card 'steward': TEST SUCCESSFULLY COMPLETED\n\n");
	return 0;
}
