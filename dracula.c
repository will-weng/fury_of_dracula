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
	// TODO ...
	// Replace the line below by something better
    char *play = "CD";
    char message[MESSAGE_SIZE] = "YOU CAN'T CATCH ME";
    int numLocations, hunters[NUM_OF_HUNTERS], counter = 0;
    LocationID *places;

    while(counter < NUM_OF_HUNTERS) {
        hunters[counter] = whereIs(gameState, counter);
        counter++;
    }

    if(giveMeTheRound(gameState) > 0) {
        places = whereCanIgo(gameState, &numLocations, TRUE, FALSE);
        play = idToAbbrev(places[numLocations/2]);
    }

    if(strcmp(play, "AT") == 0 || strcmp(play, "CA") == 0 ||
        strcmp(play, "BI") == 0) play = "TP";

    if(play == idToAbbrev(hunters[0]) || play == idToAbbrev(hunters[1]) 
        || play == idToAbbrev(hunters[2]) || play == idToAbbrev(hunters[3])) {
        play = idToAbbrev(places[rand() % numLocations]);
    }

    registerBestPlay(play, message);
}

