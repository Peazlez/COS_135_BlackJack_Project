#include <player.h>
#include <table.h>

//dealer behavior?

int main(){
    char buffer[256];
    printf("Welcome to the Blackjack Table, how many players?  This table can seat up to 4.\n");
    fgets(buffer, sizeof(buffer),stdin);
    int count = atoi(buffer);

    if(count < 1 || count > 4){
        printf("Invalid number of players.  Enter between 1 and 4 players\n");
        return 1;
    }

    //need to add a trim for newline character and place in table struct
    for(int i = 0 ; i < count ; i++){
        printf("Player name?\n");
        fgets(buffer, sizeof(buffer),stdin);
        Player *p = createPlayer(buffer);

        //check for player allocation
        if(p == NULL){
            printf("New Player Allocation Failed\n");
            return 1;
        }
        //print player for verification
        printPlayer(p);
    }
}