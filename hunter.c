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
    char message[MESSAGE_SIZE] = "";
    int numLocations, me;
    LocationID *places = whereCanIgo(gameState, &numLocations, TRUE, TRUE, TRUE);

    me = whoAmI(gameState);
    
    if(me == PLAYER_LORD_GODALMING)
    {
    }
    else if(me == PLAYER_DR_SEWARD)
    {
        play = "FR";
    }
    else if(me == PLAYER_VAN_HELSING)
    {
        play = "MN";
    }
    else if(me == PLAYER_MINA_HARKER)
    {
        play = "SR";
    }

    if(giveMeTheRound(gameState) > 0) play = idToAbbrev(places[numLocations-1]);
    if(howHealthyIs(gameState, me) < 5) play = idToAbbrev(whereIs(gameState, me));

    registerBestPlay(play, message);
}
