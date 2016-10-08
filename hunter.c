// hunter.c
// Implementation of your "Fury of Dracula" hunter AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "HunterView.h"
#include "Places.h"


void decideHunterMove(HunterView gameState)
{
    char *play = "CD";
    char message[MESSAGE_SIZE] = "I'M GONNA GET YOU";
    int numLocations;
    if(whoAmI(gameState) == PLAYER_LORD_GODALMING) {

        if(giveMeTheRound(gameState) > 0) {
            LocationID *places = whereCanIgo(gameState, &numLocations, TRUE, TRUE, TRUE);
            play = idToAbbrev(places[rand() % numLocations]);

        }
    } else if(whoAmI(gameState) == PLAYER_DR_SEWARD) {
        play = "FR";
        if(giveMeTheRound(gameState) > 0) {
            LocationID *places = whereCanIgo(gameState, &numLocations, TRUE, TRUE, TRUE);
            play = idToAbbrev(places[rand() % numLocations]);
        }
    } else if(whoAmI(gameState) == PLAYER_VAN_HELSING) {
        play = "MN";
        if(giveMeTheRound(gameState) > 0) {
            LocationID *places = whereCanIgo(gameState, &numLocations, TRUE, TRUE, TRUE);
            play = idToAbbrev(places[rand() % numLocations]);
        }
    } else if(whoAmI(gameState) == PLAYER_MINA_HARKER) {
        play = "SR";
        if(giveMeTheRound(gameState) > 0) {
            LocationID *places = whereCanIgo(gameState, &numLocations, TRUE, TRUE, TRUE);
            play = idToAbbrev(places[rand() % numLocations]);
        }
    }
    registerBestPlay(play, message);
}
