#include "player.h"
#include "table.h"
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

//if players all bust, dealer starts infinite loop
//looping through array by incrementing/decrementing pointer
//read file?
//read.me file
//github repo?

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
    srand(time(NULL));
    //create text file (wipe existing file)
    FILE *fp = fopen("Scores.txt","w");
    fprintf(fp, "Game Scores \n\n");
    fclose(fp);

    //Welcome message plus gets player count
    printf("Welcome to the Blackjack Table, how many players?  This table can seat up to 4.\n");
    char *numPlayers = playerInput();
    int count = atoi(numPlayers);
    free(numPlayers);

    //checks that count is valid
    if(count < 1 || count > 4){
        printf("Invalid number of players.  Enter between 1 and 4 players\n");
        return 1;
    }

    //array for player color text
    const char *colorArray[4] = {RED, BLU, GRN, YEL};

    //create game table
    Table *game = createTable(count);

    //add players to table
    for(int i = 0 ; i < count ; i++){
        printf("Player name?\n");
        //use playerInput function for trimming and fgets
        char *newStr = playerInput();
        //create player, set color for individual player
        Player *p = createPlayer(newStr, colorArray[i]);

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

    // create game deck
    int *Deck = createDeck();
    int activePlayers = game->numPlayers;

    while(activePlayers > 0){
        //zero all hand totals
        game->dealerHand = 0;
        game->secondCard = 0;
        game->dealerAces = 0;

        //value for dealer auto win checking
        int playersInRound = 0;

        for(int i = 0 ; i < game->numPlayers ; i++){
            //skip past cashed out players
            if(game->players[i] ==NULL) continue;
            //reset player hands and ace totals
            game->players[i]->handTotal = 0;
            game->players[i]->aceCount = 0;
        }

        //placing bets from each player
        for(int i = 0 ; i < game->numPlayers ; i++){
            //skips freed players in array
            if(game->players[i] ==NULL) continue;
            while(true){
                //messages with name highlighted with players unique color
                printf("%sChips: %s%d\n", game->players[i]->textColor,RESET, game->players[i]->chipCount);
                printf("Bet for this hand, %s%s%s? \n",game->players[i]->textColor, game->players[i]->name, RESET);
                //player input function call casted to int
                char *inputBet = playerInput();
                int bet = atoi(inputBet);
                free(inputBet);

                //check if bet is larger than 0
                if(bet <= 0){
                    printf("%sBet must be greater than 0.%s\n", game->players[i]->textColor, RESET);
                }
                //check if player has enough chips for bet
                else if(game->players[i]->chipCount < bet){
                    printf("Not enough Chips, you have: %s%d%s Chips left\n",game->players[i]->textColor, game->players[i]->chipCount, RESET);
                }
                else{
                    //set bet into player struct
                    game->players[i]->bet = bet;
                    playersInRound++;
                    break;
                }
            }
        }

        //draw first card for dealer (tracking aces)
        int dealerCard = drawCard(Deck);
        game->dealerHand += dealerCard;
        if(dealerCard == 11) game->dealerAces++;

        //draw second card for dealer but hidden till later (tracking aces)
        dealerCard = drawCard(Deck);
        game->secondCard += dealerCard;
        if(dealerCard == 11) game->dealerAces++;

        //outer loop twice for each card draw (2 cards per player)
        for(int i = 0 ; i < 2 ; i++){
            //card draw for each player (tracking aces)
            for(int k = 0 ; k < game->numPlayers ; k++){
                if(game->players[k] ==NULL) continue;
                int newCard = drawCard(Deck);

                //handle aces
                if (newCard == 11){
                    game->players[k]->aceCount++;
                }
                game->players[k]->handTotal += newCard;

                // Drop ace to "1" if handtotal exceeds 21
                while(game->players[k]->handTotal > 21 && game->players[k]->aceCount > 0){
                    game->players[k]->handTotal -=10;
                    game->players[k]->aceCount--;
                }
            }
        }
        //player bust counter for dealer behavior later
        int playersBust = 0;

        //players hit, stand, or bust here
        for(int i = 0 ; i < game->numPlayers ; i++){
            if(game->players[i] == NULL) continue;
            bool inGame = true;
            while(inGame == true){
                printf("%sYour current hand is: %d%s \n",game->players[i]->textColor, game->players[i]->handTotal, RESET);
                if(game->players[i]->handTotal > 21){
                    printf("BUST!\n\n");
                    game->players[i]->chipCount -= game->players[i]->bet; 
                    game->players[i]->bet = 0;
                    game->players[i]->handTotal = 0;
                    game->players[i]->aceCount = 0;
                    playersBust++;
                    inGame = false;
                    break;
                }
                printf(" 1: Hit\n 2: Stand\n ");
                char *response = playerInput();
                int choice = atoi(response);
                free(response);
                if(choice != 1 && choice != 2){
                    printf("%sInvalid input.  Please enter 1 (Hit) or 2 (Stand).%s\n",game->players[i]->textColor, RESET);
                    continue;
                }
                //switch for player choice (hit or stand)
                switch(choice){
                    case 1:
                        int newCard = drawCard(Deck);
                        //handle aces
                        if (newCard == 11){
                            game->players[i]->aceCount++;
                        }

                        game->players[i]->handTotal += newCard;

                        while(game->players[i]->handTotal > 21 && game->players[i]->aceCount > 0){
                            game->players[i]->handTotal -=10;
                            game->players[i]->aceCount--;
                        }
                        break;
                    case 2:
                        inGame = false;
                        break;
                }
            }
        }

        //edge case where all players bust, dealer auto wins
        if(playersBust >= playersInRound){
            printf("All players Busted.  Dealer Wins automatically.\n\n");
            for(int i = 0 ; i < game->numPlayers ; i++){
                if(game->players[i] == NULL) continue;

                if(game->players[i]->handTotal > 21){
                    printf("%s%s%s, You lost this hand!\n",game->players[i]->textColor, game->players[i]->name, RESET);
                    game->players[i]->chipCount -= game->players[i]->bet;
                    game->players[i]->handTotal = 0;
                    game->players[i]->bet = 0;
                }
            }
        }
        //dealer draws as normal if at least one player still in current hand
        else{
            //reveal second card from dealer
            printf("Dealer Hand: %d\n", game->dealerHand);
            game->dealerHand += game->secondCard;
            printf("After Card Flip: %d\n", game->dealerHand);

            //guidelines for dealer behavior
            bool dealerDraw = true;
            while(dealerDraw == true){
                if(game->dealerHand > 21){
                    dealerDraw = false;
                    break;
                }
                //Switch probably unnecessary here but wanted it in two places for switch requirement
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
                        dealerCard = drawCard(Deck);
                        if(dealerCard == 11){
                            game->dealerAces++;
                        }
                        game->dealerHand += dealerCard;
                        while(game->dealerHand > 21 && game->dealerAces > 0){
                            game->dealerHand -=10;
                            game->dealerAces --;
                        }
                        printf("Dealer Hand: %d\n", game->dealerHand);
                        break;
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    printf("Dealer Hand: %d\n", game->dealerHand);
                        dealerDraw = false;
                        break;
                }
            }
        
            //show who won/lost this hand and allot chips/reset hand and bet totals
            for(int i = 0 ; i < game->numPlayers ; i++){
                //skip players that have cashed out
                if(game->players[i] == NULL) continue;
                //skip busted players
                if(game->players[i]->handTotal > 21) continue;
                
                //check that players havent busted and have a higher value than dealer (You Win!)
                if(game->players[i]->handTotal > game->dealerHand || game->dealerHand > 21){
                    printf("%s%s%s, You won this hand!\n",game->players[i]->textColor, game->players[i]->name, RESET);
                    game->players[i]->chipCount += game->players[i]->bet;
                    printf("%sChip Count: %s%d\n", game->players[i]->textColor, RESET, game->players[i]->chipCount);
                    game->players[i]->handTotal = 0;
                    game->players[i]->bet = 0;
                    game->players[i]->winTotal +=1;
                }
                //Players Tie here (Chips remain the same)
                else if(game->players[i]->handTotal == game->dealerHand){
                    printf("%s%s%s, you tied!\n",game->players[i]->textColor, game->players[i]->name, RESET);
                    printf("%sChip Count: %s%d\n", game->players[i]->textColor, RESET, game->players[i]->chipCount);
                    game->players[i]->handTotal = 0;
                    game->players[i]->bet = 0;
                }
                //Players lose (bet chips deducted from chipcount)
                else{
                    printf("%s%s%s, You lost this hand!\n",game->players[i]->textColor, game->players[i]->name, RESET);
                    game->players[i]->chipCount -= game->players[i]->bet;
                    printf("%sChip Count: %s%d\n", game->players[i]->textColor, RESET, game->players[i]->chipCount);
                    game->players[i]->handTotal = 0;
                    game->players[i]->bet = 0;
                }
            }
        }
        //Checks for players with 0 chips left (Game Over)
        for(int i = 0 ; i < game->numPlayers ; i++){
            if(game->players[i] == NULL) continue;
            if(game->players[i]->chipCount <= 0){
                printf("%s%s%s Lost all chips\nGAME OVER\n\n",game->players[i]->textColor, game->players[i]->name, RESET);
                //call save player function to write final scores
                savePlayerInfo(game->players[i]);
                freePlayer(game->players[i]);
                game->players[i] = NULL;
                activePlayers--;
            }

            //cashout or stay?
            else{
                printf("%s%s%s, would you like to cash out?  Please enter 1 (Cash out) or 2 (Stay)\n",game->players[i]->textColor, game->players[i]->name, RESET);
                char *response = playerInput();
                int decision = atoi(response);
                free(response);
                if(decision != 1 && decision != 2){
                    printf("Invalid input.  Please enter 1 (Cash out) or 2 (Stay).\n");
                    continue;
                }
                //cashout choice writes player info to scores.txt and frees them
                else if(decision == 1){
                    printf("%s%s%s, Cashing out.....\n",game->players[i]->textColor, game->players[i]->name, RESET);
                    savePlayerInfo(game->players[i]);
                    freePlayer(game->players[i]);
                    game->players[i] = NULL;
                    activePlayers--;
                }
                //continue playing
                else if(decision == 2){
                    continue;
                }
                else printf("Invalid input. Try again.\n");
            }
        }
        //reset deck for next hand
        printf("Shuffling and resetting deck....\n");
        Deck = resetDeck(Deck);

    }
    //double check that players have been freed
    for(int i = 0 ; i < count ; i++){
        if(game->players[i] != NULL){
            freePlayer(game->players[i]);
        }
    }

    printf("Final Results in Scores.txt\n");

    //free deck and game
    free(Deck);
    free(game);
}