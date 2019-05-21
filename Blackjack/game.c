/* Contains main() and any desired helper functions to play the game as described in the instructions. Must not _define_ any of the 
 * card-related helper functions but must use thm at least as frequently as indicated below (hit means either player or dealer hit):
 * make_deck:1; shuffle:1; deal: 3+1/hit; append: 1+1/hit; total: 2+1/hit; destroy_deck: 1
 */
#include "card.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

 int main(void) {
	card *deck;
	card *dealerHand;
	card *playerHand;
	char play = 'y';
	

// PLAY (AGAIN)
while(play == 'y' || play == 'Y'){
	play = 'n'; // default set to play one round & end program;

	deck = NULL; // safekeeping 
	playerHand = NULL;
	dealerHand = NULL;
	deck = make_deck(); // new deck
	int player_tot = 0; // 
        int dealer_tot = 0;
	deck = shuffle(deck);
	char keep; // keep shuffling?
	printf("Shuffle again?('y'/'Y' or 'n'/'N')\n");
        scanf(" %c", &keep);
	
	while(keep == 'y' || keep == 'Y'){ 
		// continuous shuffling until user decides to stop
		deck = shuffle(deck);
		printf("Shuffle again?('y'/'Y' or 'n'/'N')\n");
                scanf(" %c", &keep);
	} // end while


	// GAME BEGINS 
	// Player is dealt two cards
	// Dealer is dealt one card
	playerHand = deal(deck);
	playerHand->next = deal(deck);
	
	dealerHand = deal(deck);
	char move;
	printf("Dealer's hand: ");
	show(dealerHand);
	printf("Player's hand: ");
	show(playerHand);
	printf("hit('h'/'H') or stand('s'/'S')?\n");
	scanf(" %c", &move);



	while(move != 's' && move != 'S' && total(playerHand) <= 21){
		if(move == 'h' || move == 'H'){ //Player hits
			card *p2c = playerHand;
        		for(; p2c->next != NULL; p2c = p2c->next);
        		p2c->next = deal(deck);	
			 if(total(playerHand) >= 21){
			      break;
       			 }
		} // end if
	printf("Player's hand: "); 
	show(playerHand);
	printf("hit('h'/'H') or stand('s'/'S')?\n");
        scanf(" %c", &move);


	} // end while 	
 

	if(total(playerHand) > 21){ // player busts
		printf("Lost!\n");
	} else{

		card *p2c = dealerHand;
		while(total(dealerHand) < 17){
		// dealer keeps getting cards until hand is 17 or greater
                        for(; p2c->next != NULL; p2c = p2c->next);
                        p2c->next = deal(deck);
		} // end while


// DONE DEALING CARDS
// WINNER is determined now
		player_tot = total(playerHand);
		dealer_tot = total(dealerHand);

		printf("Dealer's hand: ");
        	show(dealerHand);
     		printf("Player's hand: ");
      		show(playerHand);
		if(dealer_tot > 21){ // dealer busts
			printf("Win!\n");
		} else if (dealer_tot >= player_tot){
			printf("Lost!\n");
		} else { // player's hand is greater
			printf("Win!\n");
		}
	}


	printf("Another round? ('y'/'Y' or 'n'/'N')\n");
	scanf(" %c", &play);

	// free card memory
	destroy_deck(deck);
	destroy_deck(playerHand);
	destroy_deck(dealerHand);
} // end while 
	
	return 0;
} // main