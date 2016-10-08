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

static struct
{
    LocationID currLocation[NUM_OF_HUNTERS];
    LocationID lastLocation[NUM_OF_HUNTERS];
} hunter;

void decideDraculaMove(DracView gameState)
{
    // initializes all used vairables
    char *play = "KL";
//    char message[MESSAGE_SIZE] = "";
    int numLocations, counter, counter1, start, end;
    LocationID *path, trail[TRAIL_SIZE];
    
    path = whereCanIgo(gameState, &numLocations, TRUE, FALSE);
    giveMeTheTrail(gameState, PLAYER_DRACULA, trail);

    // initializes the hunter struct
    for(counter = 0; counter < NUM_OF_HUNTERS; counter++) 
    {
        lastMove(gameState, counter, &start, &end);
        hunter.currLocation[counter] = end;
        hunter.lastLocation[counter] = start;
    }

    // remove places in trail from path
    for(counter = 0, counter1 = numLocations; counter < counter1; counter++)
    {
        for(start = 0; start < TRAIL_SIZE; start++)
        {
            if(trail[start] == path[counter])
            {
                for(end = counter; end + 1 < counter1; end++)
                {
                    path[end] = path[end + 1];
                }
                numLocations--;
            }
        }
    }
    // move into castle after round 1;
    if(giveMeTheRound(gameState) == 1) play = "CD";

    
    if(giveMeTheRound(gameState) > 1)
    {
        // move randomly after initial rounds
        play = idToAbbrev(path[numLocations/2]);

        // if reaches some far places hopefully would tp to castle
        if(strcmp(play, "AT") == 0 || strcmp(play, "CA") == 0 ||
            strcmp(play, "BI") == 0) play = "TP";

        // move to where the hunter last position was if possible
        for(counter = 0; counter < numLocations; counter++)
        {
            for(counter1 = 0; counter1 < NUM_OF_HUNTERS; counter1++)
            {
                if(path[counter] == hunter.lastLocation[counter1])
                    play = idToAbbrev(path[counter]);
            }
        }

        // move to different place if chosen one has a hunter on it
        for(counter = 0; counter < NUM_OF_HUNTERS; counter++)
        {
            if(strcmp(play, idToAbbrev(hunter.currLocation[counter])) == 0)
                play = idToAbbrev(path[rand() % numLocations]);
        }
    }
    registerBestPlay(play, play);
}

