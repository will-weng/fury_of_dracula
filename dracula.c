// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"
#include "Places.h"
#include <string.h>

#define LENGTH_OF_PLAY 3
#define NUM_OF_HUNTERS 4

void decideDraculaMove(DracView gameState)
{
    // initializes all used vairables
    char *play = "KL";
    char message[MESSAGE_SIZE] = "YOU CAN'T CATCH ME";
    int numLocations, hunters[NUM_OF_HUNTERS], counter;
    LocationID *path;

    // stores where hunteres are for easy access
    for(counter = 0; counter < NUM_OF_HUNTERS; counter++)
        hunters[counter] = whereIs(gameState, counter);

    // move into castle after round 1;
    if(giveMeTheRound(gameState) == 2) play = "CD";

    // move randomly after initial rounds
    if(giveMeTheRound(gameState) > 2) {
        path = whereCanIgo(gameState, &numLocations, TRUE, FALSE);
        play = idToAbbrev(path[numLocations/2]);
    }

    // if reaches some far places hopefully would tp to castle
    if(strcmp(play, "AT") == 0 || strcmp(play, "CA") == 0 ||
        strcmp(play, "BI") == 0) play = "TP";

    // move to different place if chosen one has a hunter on it
    for(counter = 0; counter < NUM_OF_HUNTERS; counter++) {
        if(strcmp(play, idToAbbrev(hunters[counter])) == 0)
            play = idToAbbrev(path[rand() % numLocations]);
    }

    registerBestPlay(play, message);
}

