//header guard for this header file
#ifndef TABLE_H 
#define TABLE_H

#include "player.h"

#define START_CHIPS 500
#define MAX_PLAYERS 4

//color text for dealer
#define BLK "\e[0;30m"

//game table struct
typedef struct Table{
    int numPlayers;
    Player** players;
    int dealerHand;
    int secondCard; 
    int dealerAces;
}Table;

//Create table
Table* createTable(int count);

// Create deck of 52 cards
int *createDeck();

//draws card from 52 int value array
int drawCard(int cards[]);

// "shuffle" deck (frees old deck and creates new one)
int *resetDeck(int cards[]);

//Free table (and players) at the end of the program
void freeTable(Table *aTable);

#endif