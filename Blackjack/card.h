/* This file should contain prototypes for all card/deck-related functions (see card.c) as well as the 'card' structure.
 * a 'card' structure has an (int) rank, a (char) suit, and a pointer to card (next in the pile; 0 for end of the list). 
 */

typedef struct Card {
    int rank;
    char suit;
    struct Card *next; /* have to use struct Card because the typedef isnt "ready" yet */
} card;

/* Prototype all functions below */

int count_deck(card *deck);
card* shuffle(card *deck);
card* make_deck(); // returns to the head of the list
void destroy_deck(card *deck); //free memory of all cards in deck
card* deal(card *top); //expected to get head of deck for input
int total(card *hand); // returns sum of values of cards
void show(card *hand); // prints rank & suite
void print_deck(card *deck); // prints every rank & suit in deck
