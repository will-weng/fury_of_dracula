// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"
#include "Places.h"
#include <string.h>

#define LENGTH_OF_PLAY 3
#define NUM_OF_PLAYERS 4

static struct
{
    LocationID currLocation[NUM_OF_PLAYERS];
    LocationID lastLocation[NUM_OF_PLAYERS];
} player;

void decideDraculaMove(DracView gameState)
{
    // initializes all used vairables
    char *play = "KL";
//    char message[MESSAGE_SIZE] = "";
    int numLocations, counter, counter1, start, end;
    LocationID *path, trail[TRAIL_SIZE];
    
    path = whereCanIgo(gameState, &numLocations, TRUE, TRUE);
    giveMeTheTrail(gameState, PLAYER_DRACULA, trail);

    // initializes the player struct
    for(counter = 0; counter < NUM_OF_PLAYERS; counter++) 
    {
        lastMove(gameState, counter, &start, &end);
        player.currLocation[counter] = end;
        player.lastLocation[counter] = start;
    }

    // remove places in trail from path
    for(counter = numLocations - 1; counter >= 0; counter--)
    {
        for(start = 0; start < TRAIL_SIZE; start++)
        {
            if(trail[start] == path[counter])
            {
                for(counter1 = counter; counter1 < numLocations - 1; counter1++)
                {
                    path[counter1] = path[counter1 + 1];
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
        // move to where the hunter last position was if possible
        for(counter = 0; counter < numLocations; counter++)
        {
            for(counter1 = 0; counter1 + 1< NUM_OF_PLAYERS; counter1++)
            {
                if(path[counter] == player.lastLocation[counter1])
                    play = idToAbbrev(path[counter]);
            }
        }

        // move to different place if chosen one has a hunter on it
        for(counter = 0; counter + 1 < NUM_OF_PLAYERS; counter++)
        {
            if(strcmp(play, idToAbbrev(player.currLocation[counter])) == 0)
                play = idToAbbrev(path[rand() % numLocations]);
        }

        // if there is no path then go back
        if(numLocations == 0) play = "D1";
        if(player.currLocation[PLAYER_DRACULA] == player.lastLocation[PLAYER_DRACULA]) play ="HIDE";
    }

    registerBestPlay(play, play);
}

