//header guard for this header file
#ifndef TABLE_H 
#define TABLE_H

#define START_CHIPS 500
#define MAX_PLAYERS 4

typedef struct Table{
    int max_players;
    struct Player** players;
};

/* Maybe a Card struct if array of ints wont work for card values? */
/* Also, How will I make the Ace work to be both 10 and 1? */
/* check to see if adding 10 would bust?  How to check on next draw?*/

//Create table (add parameters)
Table* createTable();

// Create deck of 52 cards
void createDeck();

//draws card from 52 int value array
int drawCard();

//Free table at the end of the program
void freeTable();


#endif