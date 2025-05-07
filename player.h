// Header Guard
#ifndef PLAYER_H
#define PLAYER_H

#define MAX_NAME_LENGTH 100

//colors for text prints
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player{
    char name[MAX_NAME_LENGTH];
    int chipCount;
    int bet;
    int handTotal;
    int winTotal;
    int aceCount;
}Player;

//create Player function
Player* createPlayer(const char *name);

// adds or subtracts chips based on this hand's win or loss
void changeChips(Player *p, int change);

// Free player when info has been saved and they lose all chips
void freePlayer(Player *p);

// player info printing function
void printPlayer(const Player *p);

void savePlayerInfo(Player *p);
    


#endif