
#include "player.h"

Player* createPlayer(const char *name){
    //player pointer
    Player *p = malloc(sizeof(Player));
    if(p == NULL){ 
        printf("Memory allocation failed\n");
        return NULL;
    }
    // copy name into Player
    strncpy(p->name, name, MAX_NAME_LENGTH-1);
    // initial chip count
    p->chipCount = 500;
    //bet amount
    p->bet = 0;
    //hand total and win total initialized at 0 for now
    p->handTotal = 0;
    p->winTotal = 0;
    p->aceCount = 0;

    //return player pointer
    return p;
}

void changeChips(Player *p, int change){
    p->chipCount += change;
}

void freePlayer(Player *p){
    free(p);
}

void printPlayer(const Player *p){
    printf("Name: %s \nChips: %d \n Hand: %d \n Wins: %d\n", p->name,p->chipCount,p->handTotal,p->winTotal);
}

void savePlayerInfo(Player *p){
        //open file to write, have pointer look at file
        FILE *fp = fopen("Scores.txt","a");

        // Can't find file
        if (fp == NULL){
            printf("Could not open file");
            exit(1);
        }
    
        // make a buffer to hold info
        char buffer[1024];

        //write to Scores File
        fprintf(fp , "Name: %s \nChips: %d \n Hand: %d \n Wins: %d\n\n", p->name,p->chipCount,p->handTotal,p->winTotal);
        //close file
        fclose(fp);
}