
#include "../lib/bib.h"
#include <stdio.h>

void readUINT(unsigned int *i){
    char c;
    while(scanf("%u",i)!=1){
        while((c=fgetc(stdin))!=EOF && (c!='\n'));
        printf("%sEnter a valid number: %s",RED,RESET);
    }
}
typedef struct {
    int playerId;                // Unique identifier for the player
    char pseudonym[50];          // Player's nickname
    char preferredDomains[100];  // Preferred domains for playing
    int gamesPlayed;             // Number of games played
    int totalScore;              // Total score across all games
} Player; // Define the Player structure 