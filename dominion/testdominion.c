#include "dominion.c"
#include "rngs.c"

#define TEST_LOOP 50

void getKindomCard(int *k);
void getInitGameInfo(int *k, int p);
int checkAction(struct gameState *g);
void play_card(struct gameState *g);
void getGameResult(struct gameState *g);
void buy_card(struct gameState *g);

int main(int argc, char* argv[]){

	srand (time(NULL));

	int i,j,randomseed,playerNum,test_kindomcard[10];
	
	if(argv[1] != NULL){
		randomseed = atoi(argv[1]);		// allow taking randomseed argv from command line
	}else{
		printf("ERROT: Please Enter Seed Number\n");
		exit(-1);
	}


	for(i = 0; i < TEST_LOOP; i++){
		struct gameState game;
		getKindomCard(test_kindomcard);
		playerNum = rand()%3+2; //randomly get between 2-4 players
		getInitGameInfo(test_kindomcard,playerNum);
		int check = initializeGame(playerNum, test_kindomcard, randomseed, &game);
		if(check == -1){	// check initilization error 
			printf("TEST FAILED: initializeGame()\n");
			return 1;	//failed initilization
		}

		while(!isGameOver(&game)){
			int cur_player = whoseTurn(&game);
			printf("\n--------- Player %d's Turn ---------\n", cur_player+1);

			// play card
			if(checkAction(&game) > 0){	
				play_card(&game);
			}else{	// no action
				printf("PLAY SkIPPED: No Action Card\n");
			}

			// buy card
			if(game.numBuys > 0){
				buy_card(&game);
			}else{
				printf("BUY SKIPPED: No valid buying\n");
			}

			//end turn
			endTurn(&game); 
			printf("-----------------------------------\n");
		}
		getGameResult(&game);
	}
	return 0;
}

/********************************************************
						FUNCTIOND
/********************************************************/

void getKindomCard(int *k){
	int i=0,j=0,same=0;
	
	while(i < 10){
		k[i] = rand()%27;
		for(j = 0; j < i; j++){
			if(k[i] == k[j]){
				same = 1;
				break;
			}
		}
		if(same != 1){
			i++;
		}
		same = 0;
	}
}


void play_card(struct gameState *g){
	int getcard,hand_pos;
	int choice1, choice2, choice3;
	int cur_player = whoseTurn(g);
	
	// recall playcard function
	do{
		hand_pos = rand()%numHandCards(g);	
		getcard = handCard(hand_pos, g);	// randomly select an ACTION card from hand
	}while(!(getcard >= adventurer && getcard <= treasure_map));

	if(getcard >= adventurer && getcard <= treasure_map){	//double check
		if(getcard == feast){
			choice1 = rand()%27; // choice1 is supply # of card gained)
			choice2 = -1;
			choice3 = -1;
			printf("Player %d played card 'feast'\n", cur_player+1);
			playCard(hand_pos, choice1, choice2, choice3, g);
		}else if(getcard == mine){
			choice1 = rand()%numHandCards(g); // choice1 hand#
			choice2 = rand()%numHandCards(g);	// choice2 hand#
			choice3 = -1;
			printf("Player %d played card 'mine'\n", cur_player+1);
			playCard(hand_pos, choice1, choice2, choice3, g);
		}else if(getcard == remodel){
			choice1 = rand()%numHandCards(g); // choice1 hand#
			choice2 = rand()%numHandCards(g);	// choice2 hand#
			choice3 = -1;
			printf("Player %d played card 'remodel'\n", cur_player+1);
			playCard(hand_pos, choice1, choice2, choice3, g);
		}else if(getcard == baron){
			choice1 = rand()%2; // choice1: boolean for discard of estate
			choice2 = -1;
			choice3 = -1;
			printf("Player %d played card 'baron'\n", cur_player+1);
			playCard(hand_pos, choice1, choice2, choice3, g);
		}else if(getcard == minion){
			choice1 = rand()%2; // choice1:  1 = +2 coin, 2 = redraw
			if(choice1 == 0){
				choice2 = rand()%2;
			}else{
				choice2 = 0;
			}
			choice3 = -1;
			printf("Player %d played card 'minion'\n", cur_player+1);
			playCard(hand_pos, choice1, choice2, choice3, g);
		}else if(getcard == steward){
			choice1 = rand()%3; // choice1: 1 = +2 card, 2 = +2 coin, 3 = trash 2 (choice2,3)
			if(choice1 == 0){
				choice2 = rand()%numHandCards(g);
				do{
					choice3 = rand()%numHandCards(g);
				}while(choice3 == choice2);
			}else{
				choice2 == -1;
				choice3 == -1;
			}
			printf("Player %d played card 'steward'\n", cur_player+1);
			playCard(hand_pos, choice1, choice2, choice3, g);
		}else if(getcard == ambassador){
			choice1 = rand()%numHandCards(g); // choice1 = hand#, choice2 = number to return to supply
			choice2 = rand()%numHandCards(g);
			choice3 = -1;
			printf("Player %d played card 'ambassador'\n", cur_player+1);
			playCard(hand_pos, choice1, choice2, choice3, g);
		}else if(getcard == embargo){
			choice1 = rand()%27; // choice1 = supply#
			choice2 = -1;
			choice3 = -1;
			printf("Player %d played card 'embargo'\n", cur_player+1);
			playCard(hand_pos, choice1, choice2, choice3, g);
		}else if(getcard == salvager){
			choice1 = rand()%27; // choice1 = supply#
			choice2 = -1;
			choice3 = -1;
			printf("Player %d played card 'salvager'\n", cur_player+1);
			playCard(hand_pos, choice1, choice2, choice3, g);
		}else{
			choice1 = -1;
			choice2 = -1;
			choice3 = -1;
			printf("Player %d played card 'WITHOUT CHOICE'\n", cur_player+1);
			playCard(hand_pos, choice1, choice2, choice3, g);
		}
	}else
		printf("ERROR: Selected non-action card\n");	//error
}


void buy_card(struct gameState *g){
	int gainCard, i, index, size=0, money;
	int validcard[treasure_map+1];
	int cur_player = whoseTurn(g);
	for(i = 0; i < numHandCards(g); i++){	// check total money in hand for current player
    	if(handCard(i, g)==copper)
   	 		money++;
   	   	else if(handCard(i, g)==silver)
    		money += 2;
    	else if(handCard(i, g)==gold)
    		money += 3;
    	else
   	 		money += 0;
   	}
	
	for(i=0; i<treasure_map+1; i++){
		if(money >= getCost(i) && supplyCount(i, g)>0){
			validcard[size] = i;
			size++;
		}
	}

	if(size>0){
		index = rand()%size;
		gainCard = validcard[index];
		if(buyCard(gainCard, g) == 0){
			printf("Player %d bought card '%d'\n", cur_player+1, gainCard);
		}else{
			printf("BUY SKIPPED: No valid buying\n");
		}
	}else{
		printf("BUY SKIPPED: No valid buying\n");
	}
}


void getInitGameInfo(int *k, int p){
	int i;
	printf("------------ GAME INFO ------------\n\n");
	printf("Picked KindomCards:\n");
	for(i=0; i<10; i++){
		printf("%d ", k[i]);
	}
	printf("\n");
	printf("\nPicked Player Number: ");
	printf("%d\n", p);
	printf("\n-----------------------------------\n");
}


void getGameResult(struct gameState *g){
	int i, players[g->numPlayers];

	printf("\n------------ GAME OVER ------------\n");

	for(i=0; i<g->numPlayers; i++){
		printf("Player %d Score: %d\n", i+1, scoreFor(i, g));
	}
	printf("\n");

	getWinners(players, g);
	for(i=0; i<g->numPlayers; i++){
		if(players[i]==1)
			printf("Winner is Player %d\n", i+1);
	}
	printf("-----------------------------------\n");
}


int checkAction(struct gameState *g){
	int i;
	int ActionCnt=0;
	int cur_player = whoseTurn(g);

	for(i=0; i <numHandCards(g); i++){		//check valid action of current player
		if(g->hand[cur_player][i] >= adventurer && g->hand[cur_player][i] <= treasure_map){
			ActionCnt++;
		}
	}
	return ActionCnt;
}