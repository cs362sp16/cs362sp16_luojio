#include "../dominion.c"
#include "../rngs.c"
#include "../myassert.h"

#define TEST_LOOP 100

void checker(struct gameState*, int);

int main(int argc, char* argv[]){

	srand (time(NULL));
	printf("\n*********************************************************\n\n");
	printf("               Random Test card 'smithy'\n\n");
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

	//initialize for card conditions
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

	printf("Card 'smithy': TEST SUCCESSFULLY COMPLETED\n\n");
	return 0;
}


void checker(struct gameState *state, int player){
	int temp1, temp2, temp3, temp4, result;

	temp1 = state->handCount[player];
	temp3 = state->deckCount[player];

	check_functions(cardEffect(smithy, 0, 0, 0, state, 0, 0));

	temp2 = state->handCount[player];
	temp4 = state->deckCount[player];

	//printf("check correct handcount...\n");
	check_equal(temp1, temp2-3+1);
}
