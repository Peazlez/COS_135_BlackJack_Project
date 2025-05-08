#include "player.h"

//create players taking name and text color as "constant" parameters
Player* createPlayer(const char *name, const char *textColor){
    //player pointer
    Player *p = malloc(sizeof(Player));
    if(p == NULL){ 
        printf("Memory allocation failed\n");
        return NULL;
    }
    // copy name into Player
    strncpy(p->name, name, MAX_NAME_LENGTH-1);
    //copy text color
    strncpy(p->textColor, textColor, MAX_COLOR_LENGTH-1);
    // initial chip count
    p->chipCount = 500;
    //bet amount
    p->bet = 0;
    //hand total and win total initialized at 0 for now
    p->handTotal = 0;
    p->winTotal = 0;
    //ace count used for math during deals in main function
    p->aceCount = 0;

    //return player pointer
    return p;
}

//returns correct chip total after each hand
void changeChips(Player *p, int change){
    p->chipCount += change;
}

//free individual player
void freePlayer(Player *p){
    free(p);
}

//print player info for testing purposes
void printPlayer(const Player *p){
    printf("%sName: %s%s \nChips: %d \n Hand: %d \n Wins: %d\n",p->textColor, p->name, RESET, p->chipCount,p->handTotal,p->winTotal);
}

//saves player info to Scores.txt
void savePlayerInfo(Player *p){
        //open file to append, have pointer look at file
        FILE *fp = fopen("Scores.txt","a");

        // Can't find file
        if (fp == NULL){
            printf("Could not open file\n");
            exit(1);
        }

        //write to Scores File
        fprintf(fp , "Name: %s \nChips: %d \n Hand: %d \n Wins: %d\n\n", p->name,p->chipCount,p->handTotal,p->winTotal);
        //close file
        fclose(fp);
}