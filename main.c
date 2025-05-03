#include <player.h>
#include <table.h>

//dealer behavior?
//string concatanate function for color texts
//function to check for aces and calculate hand total

//function for player input and trimming
char* playerInput(){
    char buffer[256];
    fgets(buffer, sizeof(buffer),stdin);

    // start at the buffer memory, then move strlen spaces forward
    char *ptr = buffer + strlen(buffer)-1;  //strlen gives length of string

    // continue to step backwards until we reach a real character
    while(isspace(*ptr))ptr--;
    
    // look at memory addr of ptr, step one further follow that memory, change char to 0
    *(ptr+1)= 0;
    
    ptr = buffer; //move ptr to start of buffer
    
    while(isspace(*ptr)) ptr++; //move forward until you reach a real character
    
    char *newStr = malloc(sizeof(char)*256);
    
    // copy over the ptr version of string into memory of newStr
    strcpy(newStr,ptr);

    return newStr;
}

int main(){
    printf("Welcome to the Blackjack Table, how many players?  This table can seat up to 4.\n");
    char *numPlayers = playerInput();
    int count = atoi(numPlayers);
    free(numPlayers);

    if(count < 1 || count > 4){
        printf("Invalid number of players.  Enter between 1 and 4 players\n");
        return 1;
    }
    //create game table
    Table *game = createTable(count);

    //add players to table
    for(int i = 0 ; i < count ; i++){
        printf("Player name?\n");
        //use playerInput function for trimming and fgets
        char *newStr = playerInput();
        //create player
        Player *p = createPlayer(newStr);

        //check for player allocation
        if(p == NULL){
            printf("New Player Allocation Failed\n");
            return 1;
        }
        //print player for verification
        printPlayer(p);
        //add players to array in table struct
        game->players[i] = p;
        //free temp variable newStr
        free(newStr);
    }

    while(game->numPlayers > 0){
        //zero all hand totals
        game->dealerHand = 0;
        game->secondCard = 0;
        for(int i = 0; i < game->numPlayers ; i++){
            game->players[i]->handTotal=0;
        }

        // create game deck for current hand
        int *Deck = createDeck();

        //placing bets from each player  *****add cash out here?*****
        for(int i = 0 ; i < game->numPlayers ; i++){
            printf("Bet for this hand, %s? \n", game->players[i]->name);
            char *inputBet = playerInput();
            //check if player has enough chips for bet
            if(game->players[i]->chipCount - atoi(inputBet) < 0){
                printf("Not enough Chips\n");
            }
            else{
                //set bet into player struct
                game->players[i]->bet = atoi(inputBet);
            }
            free(inputBet);
        }

        //draw first card for dealer
        game->dealerHand += drawCard(Deck);
        //draw second card for dealer but hidden till later
        game->secondCard += drawCard(Deck);

        //outer loop twice for each card draw (2 cards per player)
        for(int i = 0 ; i < 2 ; i++){
            //card draw for each player
            for(int k = 0 ; k < game->numPlayers ; k++){
                game->players[k]->handTotal += drawCard(Deck);
            }
        }

        //reveal second card from dealer
        game->dealerHand += game->secondCard;
        //guidelines for dealer behavior
        switch(game->dealerHand){
            case 0: 
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
                game->dealerHand += drawCard(Deck);
                break;
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:

        }

        


    }
}