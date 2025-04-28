
#include "player.h"

struct Player* createPlayer(char *name, int chipCount, int handTotal, int winTotal){
    //player pointer
    Player *p = malloc(sizeof(Player));
    // copy name into Player
    strncpy(p->name, name, MAX_NAME_LENGTH-1);
    // initial chip count
    p->chipCount = 500;
    //hand total and win total initialized at 0 for now
    p->handTotal = 0;
    p->winTotal = 0;

    //return player pointer
    return p;
}

void changeChips(Player *p, int change){
    p->chipCount += change;
}

void freePlayer(Player *player){
    free(player);
}

void printPlayer(Player *p){
    printf("Name: %s \nChips: %d \n Hand: %d \n Wins: %d", p->name,p->chipCount,p->handTotal,p->winTotal);
}