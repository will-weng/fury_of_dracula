// hunter.c
// Implementation of your "Fury of Dracula" hunter AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "HunterView.h"
#include "Places.h"

static struct
{
    LocationID currLocation[NUM_PLAYERS];
    LocationID *places;
    int round;
    int me;
} gameInfo;

void decideHunterMove(HunterView gameState)
{
    // initializes variables
    char *play = "CD";
    char message[MESSAGE_SIZE] = "";
    int numLocations, counter;

    // fills out the game info struct
    gameInfo.me = whoAmI(gameState);
    gameInfo.round = giveMeTheRound(gameState);
    gameInfo.places = whereCanIgo(gameState, &numLocations, TRUE, TRUE, TRUE);
    for(counter = 0; counter < NUM_PLAYERS; counter++) {
        gameInfo.currLocation[counter] = whereIs(gameState, counter);
    }


    // individual decisions of hunters
    if(gameInfo.me == PLAYER_LORD_GODALMING)
    {
    }
    else if(gameInfo.me == PLAYER_DR_SEWARD)
    {
        play = "FR";
    }
    else if(gameInfo.me == PLAYER_VAN_HELSING)
    {
        play = "MN";
    }
    else if(gameInfo.me == PLAYER_MINA_HARKER)
    {
        play = "SR";
    }

    // chooses a random place to go
    if(gameInfo.round == 7) {
        play = idToAbbrev(gameInfo.currLocation[gameInfo.me]);
    } else if(gameInfo.round > 0) {
        play = idToAbbrev(gameInfo.places[numLocations/2]);
    }

    // if hunter is lower than 5 health, it would rest
    if(howHealthyIs(gameState, gameInfo.me) < 5) play = idToAbbrev(whereIs(gameState, gameInfo.me));

    registerBestPlay(play, message);
}
