#include "../dominion.c"
#include "../rngs.c"
#include "../myassert.h"

#define TEST_LOOP 1

void checker(struct gameState*, int);

int main(int argc, char* argv[]){

	srand (time(NULL));
	printf("\n*********************************************************\n\n");
	printf("               Random Test card 'adventurer'\n\n");
	printf("*********************************************************\n");

//	Test Initialization
	struct gameState game;
	int i,j,randomSeed,playerNum, cur_player;
	int cards[10] = {estate, duchy, adventurer, embargo, sea_hag, feast, gardens, mine, tribute, outpost}; 
	

	for(i=0; i<TEST_LOOP; i++){		// take TEST_LOOP rounds of test
		playerNum = rand()%MAX_PLAYERS+1; //generate 1-4 players	randomly 

		if(argv[1] != NULL){
			randomSeed = atoi(argv[1]);		// allow taking randomseed argv from command line
		}else{
			randomSeed = rand()%100+1;
		}
		initializeGame(playerNum, cards, randomSeed, &game);

	//initialize for card card_adventurer conditions
		cur_player = rand()%playerNum; 
		game.whoseTurn = cur_player;	// get a random current player

		game.deckCount[cur_player] = rand()%(MAX_DECK + 1);
        for(j=0; j<game.deckCount[cur_player]; j++)
        game.deck[cur_player][j] = rand()% treasure_map;

        game.discardCount[cur_player] = floor(Random() * MAX_DECK);
        for (j = 0; j < game.discardCount[cur_player]; j++)
        game.discard[cur_player][j] = rand() % treasure_map;
        
        game.handCount[cur_player] = floor(Random() * MAX_HAND);
        game.hand[cur_player][0] = adventurer;
        for (j = 1; j < game.handCount[cur_player]; j++)
        game.hand[cur_player][j] = rand()%treasure_map;

		checker(&game, cur_player);
	}

	printf("Card 'adventurer': TEST SUCCESSFULLY COMPLETED\n\n");
	return 0;
}


void checker(struct gameState *state, int player){
	int temp1, temp2, temp3, result1, result2, result3;

	temp1 = state->handCount[player];
	temp2 = state->discardCount[player];
	temp3 = state->deckCount[player];

	check_functions(cardEffect(adventurer, 0, 0, 0, state, 0, 0));

	result1 = state->handCount[player];
	result2 = state->discardCount[player];
	result3 = state->deckCount[player];

	printf("1: %d %d\n", temp1, result1);
	printf("2: %d %d\n", temp2, result2);
	printf("3: %d %d\n", temp3, result3);
	//temp4 = temp3 - state->deckCount[player] - 2;
}