//header guard for this header file
#ifndef TABLE_H 
#define TABLE_H

#include <player.h>

#define START_CHIPS 500
#define MAX_PLAYERS 4

typedef struct Table{
    int numPlayers;
    struct Player** players; 
}Table;

/* Maybe a Card struct if array of ints wont work for card values? */
/* Also, How will I make the Ace work to be both 10 and 1? */
/* check to see if adding 10 would bust?  How to check on next draw?*/

//Create table (add parameters)
Table* createTable(int counter);

// Create deck of 52 cards (return array or structs array?)
int *createDeck();

//draws card from 52 int value array
int drawCard(int cards[]);

// "shuffle" deck (frees old deck and creates new one)
int *resetDeck(int cards[]);

//Free table at the end of the program
void freeTable(Table *aTable);

#endif