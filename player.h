// Header Guard
#ifndef PLAYER_H
#define PLAYER_H

#define MAX_NAME_LENGTH 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player{
    char name[MAX_NAME_LENGTH];
    int chipCount;
    int handTotal;
    int winTotal;
}Player;

//create Player function
Player* createPlayer(char *name, int chipCount, int handTotal, int winTotal);

// adds or subtracts chips based on this hand's win or loss
void changeChips();

// Free player when info has been saved and they lose all chips
void freePlayer();

// player info printing function
void printPlayer(Player *p);
    


#endif