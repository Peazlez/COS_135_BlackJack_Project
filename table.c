
#include "table.h"


//create game table, takes count only as parameter which comes from command line input
Table* createTable(int count){
    Table *game = malloc(sizeof(Table));
    if(game == NULL){
        printf("Table Memory Allocation Failed\n");
        return NULL;
    }
    game->numPlayers = count;
    game->players = malloc(sizeof(Player*) * count);
    game->dealerHand = 0;
    game->secondCard = 0;
    game->dealerAces = 0;
    return game;
}

//Create deck of cards
int *createDeck(){
    //create card array
    int *cards = malloc(sizeof(int) * 52);
    //check if memory allocation successful
    if(cards == NULL){
        printf("Deck Memory Allocation Failed\n");
        return NULL;
    }
    //card values in an array
    int values[] = {2,3,4,5,6,7,8,9,10,10,10,10,11};
    // iterates through array adding each card the proper number of times to simulate a deck
    for(int i = 0 , v = 0; i < 52 ; ++i){
        cards[i] = values[v];
        if ((i + 1) % 4 == 0) v++;
    }
    return cards;
}

//uses rand() to draw randomly from array of 52 cards
int drawCard(int cards[]){
    //value for saving random number 
    int index;
    //counter for draws in case deck is empty
    int draws = 0;
    //takes random number to sift through array for card value
    while(draws < 52){
        //number between 0 and 52
        index = rand() % 52;
        //check to see if card value is 0
        if(cards[index] != 0){
            //adds card value to saved variable
            int value = cards[index];
            //empties value so it cant be redrawn
            cards[index] = 0;
            //returns card
            return value;
        }
        //counter for draws so you cant draw all 52 cards
        draws++;
    }
    //deck is empty
    return -1;
}

//"Shuffle" function for new hands
int *resetDeck(int cards[]){
    if (cards != NULL){
        free(cards);
    }

    int* newDeck = createDeck();
    if(newDeck == NULL){
        printf("New Deck Allocation Failed\n");
        return NULL;
    }
    return newDeck;
}

//frees table and players after game concludes
void freeTable(Table *aTable){
    //free players
    for(int i = 0 ; i < aTable->numPlayers ; i++){
        free(aTable->players[i]);
    }
    free(aTable->players);
    free(aTable);
}