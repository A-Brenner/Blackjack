/* Define all card/deck related functions as follows:
 * make_deck: generates a new list of 52 unique cards with ranks 1-13 and suits CDHS. Returns a pointer to the head of the list. 
 *            Note: you must use malloc to create all 52 cards.
 * destroy_deck: consumes a pointer to a card. Free memory for all cards in the list.
 * shuffle: consumes a pointer to a card (expected to be the head of a list of cards). Returns a pointer to a card (the possibly new head).
 *          Randomly re-orders the cards in the list. Note; this function has been provided for you.
 * deal: consumes a pointer to a card (expected to be the head of a list of cards). Finds the last card in the list, prints its values, removes it
 *       from the list, and returns it (pointer to card). 
 * total: consumes a pointer to card. Returns the sum of the values in the list headed by the given card (note: 10,11,12, and 13 all value as 10).
 * show: consumes a pointer to card. Prints the rank and suit of all cards in the list (this may be one card) on one line. For example:
 *       11H 9S 3D 1C 1S
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "card.h"

/* consumes pointer to a card "deck" which is assumed to be the head of the deck
 * counts the number of cards in the list headed by "deck"
 * returns an integer representing that # */
int count_deck(card *deck) {
    int count=0;
    /* No initialization required. When "deck" is NULL (zero), it's at the end. Otherwise, move to the
    next card and increment the count. No body of the for loop! */
    for(;deck;deck=deck->next,count++);
    return count;
}

/* Consumes pointer to a card "deck" assumed to be head of the deck
 * Emulates a "riffle shuffle" of "deck". 
 * returns a card which is the new head of given deck */
card *shuffle(card *deck) {
    int size = count_deck(deck);
    card *cut=deck;
    srand48(time(NULL)); // randomize seed
    for(int i=0; i<size/2; i++){
        cut=cut->next;
    }
    /* cut is now the card 1/2 way through the deck */
    card *riffle=cut->next;
    cut->next = 0; /* deck and riffle now head separate lists */
    /* Shuffle the deck by randomly pulling a card from the head of "deck" or "riffle"
       and make it the new head of "retdeck" */
    card *retdeck=0;
    for(;deck || riffle;) { /* just like a while loop */
        card *temp;
        if(deck && (!riffle || drand48()<0.5)) {    
	/* next card comes from the top of 'deck' */
            temp=deck;
            deck=deck->next;
        } else {
            /* next card comes from the top of 'riffle' */
            temp=riffle;
            riffle=riffle->next;
        }
        /* put the card at the top of the "retdeck" */
        temp->next=retdeck;
        retdeck=temp;
    }
    return retdeck;
}

 // consumes nothing
 // make_deck: generates a new list of 52 unique cards with ranks 1-13 and suits CDHS. Returns a pointer to the head of the list.
card* make_deck(){
    card* head = NULL;
    char suites[4] = {"HDCS"}; // hearts, diamonds, clubs, spades
    for(int s = 0; s < 4; s++){ // each suite
      for(int i = 1; i < 14; i++){ //Ace(1) to King (13)
      	    card *c=malloc(sizeof(card));
            c->rank = i;
            c->suit = suites[s];
            c->next = head;
            head = c;
	    printf("%d%c\n",c->rank, c->suit);
        }
    }
 return head;   
    
}

// consumes a pointer to card "deck" (expected to be head of deck), returns nothing
// frees memory of every card in deck
void destroy_deck(card *deck){
  
	card *tmp;

	while(deck != NULL){
	tmp = deck;
	deck = deck->next;
	free(tmp);
	}	
}


// consumes a pointer to card "deck" (expected to be the head of deck)
// finds LAST card in deckin the list, prints its values, removes it
//      from the list, and returns it (pointer to card). 
card* deal(card* deck){
   card *last = deck;
   deck = deck->next;
   
  for(;deck->next != NULL; deck = deck->next){
	last = deck;
  }

  printf("Card dealt: %d%c\n", deck->rank, deck->suit); // print card values
  last->next = NULL; // remove last card 'deck' from list 
  return deck;
}


// consumes pointer to a card (assumed to be head of list) 
// adds up the ranks of each card in hand
// ranks 10-13 are all treated as having the value 10
// returns the sum of all ranks as integer
int total(card *hand){
	int total = 0;
	for(; hand != NULL; hand = hand->next){
		if(hand->rank >= 10){
			total = total + 10;
		} else{
			total = total + hand->rank;
		}
	}
	return total;
}


// consumes a pointer to card (head of hand), returns nothing
// displays rank & suit of each card in list
// EX:   11D 9H 2C 
void show(card *hand){
	for(; hand != NULL; hand = hand->next){
		printf("%d%c ", hand->rank, hand->suit);
	}
	printf("\n");
}

// consumes pointer to a card (assumed to head of the deck), returns nothing
// prints each rank & suit of each card in deck
// TESTING purposes, slightly tweaked version of show(), visibility of deck
void print_deck(card *deck){
	for(;deck != NULL; deck = deck->next){
		printf("%d%c\n", deck->rank, deck->suit);
	}
}