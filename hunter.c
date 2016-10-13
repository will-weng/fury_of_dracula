// hunter.c
// Implementation of your "Fury of Dracula" hunter AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "HunterView.h"
#include "Places.h"


void decideHunterMove(HunterView gameState)
{
    // initializes variables
    char *play = "CD";
    char message[MESSAGE_SIZE] = "";
    int numLocations, me;
    LocationID *places = whereCanIgo(gameState, &numLocations, TRUE, TRUE, TRUE);

    // find out which hunters turn it is
    me = whoAmI(gameState);
    
    // individual decisions of hunters
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

    // chooses a random place to go
    if(giveMeTheRound(gameState) > 0) play = idToAbbrev(places[numLocations/2]);
    // if hunter is lower than 5 health, it would rest
    if(howHealthyIs(gameState, me) < 5) play = idToAbbrev(whereIs(gameState, me));

    registerBestPlay(play, message);
}
