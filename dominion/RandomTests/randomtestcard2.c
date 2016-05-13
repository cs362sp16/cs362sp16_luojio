#include "../dominion.c"
#include "../rngs.c"
#include "../myassert.h"

#define TEST_LOOP 100

void check_choice1(struct gameState*, int);
void check_choice2(struct gameState*, int);
void check_choice3(struct gameState*, int);
void gameInitializer(struct gameState*, int);


int main(int argc, char* argv[]){

	srand (time(NULL));
	printf("\n*********************************************************\n\n");
	printf("               Random Test card 'steward'\n\n");
	printf("*********************************************************\n");

//	Test Initialization
	struct gameState game1;
	struct gameState game2;
	struct gameState game3;

	int i,j,randomSeed,playerNum, cur_player;
	int cards[10] = {estate, duchy, adventurer, embargo, sea_hag, feast, gardens, mine, tribute, outpost}; 
	

	for(i=0; i<TEST_LOOP; i++){		// take TEST_LOOP rounds of test
		playerNum = rand()%MAX_PLAYERS+1; //generate 1-4 players	randomly 

		if(argv[1] != NULL){
			randomSeed = atoi(argv[1]);		// allow taking randomseed argv from command line
		}else{
			randomSeed = rand()%100+1;
		}
		initializeGame(playerNum, cards, randomSeed, &game1);
		initializeGame(playerNum, cards, randomSeed, &game2);
		initializeGame(playerNum, cards, randomSeed, &game3);

	//initialize for card conditions
		cur_player = rand()%playerNum; 
		
		gameInitializer(&game1, cur_player);
		gameInitializer(&game2, cur_player);
		gameInitializer(&game3, cur_player);

		check_choice1(&game1, cur_player);
		check_choice2(&game2, cur_player);
		check_choice3(&game3, cur_player);
	
	}

	printf("Card 'steward': TEST SUCCESSFULLY COMPLETED\n\n");
	return 0;
}


void gameInitializer(struct gameState* game, int cur_player){
	int j;

	game->whoseTurn = cur_player;	// get a random current player

	game->deckCount[cur_player] = rand()%(MAX_DECK + 1);
    for(j=0; j<game->deckCount[cur_player]; j++)
    game->deck[cur_player][j] = rand()% treasure_map;

    game->discardCount[cur_player] = floor(Random() * MAX_DECK);
    for (j = 0; j < game->discardCount[cur_player]; j++)
    game->discard[cur_player][j] = rand() % treasure_map;
    
    game->handCount[cur_player] = floor(Random() * MAX_HAND);
    game->hand[cur_player][0] = adventurer;
    for (j = 1; j < game->handCount[cur_player]; j++)
    game->hand[cur_player][j] = rand()%treasure_map;
}

void check_choice1(struct gameState *state, int player){
// Test of choice 1: draw 2 cards but discard 1;
	int temp1, temp2;

	temp1 = state->handCount[player];
	check_functions(cardEffect(steward, 1, 0, 0, state, 0, 0));
	temp2 = state->handCount[player];
	check_equal(temp1,temp2-1);	
}

void check_choice2(struct gameState *state, int player){
// Test of choice 1: draw 2 cards but discard 1;
	int temp1, temp2;

	temp1 = state->coins;
	check_functions(cardEffect(steward, 2, 0, 0, state, 0, 0));
	temp2 = state->coins;
	check_equal(temp1,temp2-2);
}

void check_choice3(struct gameState *state, int player){
// Test of choice 1: draw 2 cards but discard 1;
	int temp1, temp2;

	temp1 = state->handCount[player];
	check_functions(cardEffect(steward, 3, 2, 2, state, 0, 0));
	temp2 = state->handCount[player];
	check_equal(temp1,temp2+3);	
}
