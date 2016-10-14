// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"
#include "Places.h"
#include <string.h>

#define LENGTH_OF_PLAY 3
#define NUM_OF_PLAYERS 5
#define ARRAY_SIZE 9

char *LoopMove (DracView gameState);
/*
static struct
{
    LocationID currLocation[NUM_OF_PLAYERS];
    LocationID lastLocation[NUM_OF_PLAYERS];
} player;

static int *legalMoves(DracView gameState, int *path, int *numLocations, LocationID trail[TRAIL_SIZE], LocationID start);
*/
void decideDraculaMove(DracView gameState)
{
    // initializes all used vairables
    char *play = "KL";
    char message[MESSAGE_SIZE] = "Run away!";

    //Move around in a loop
    play = LoopMove(gameState);
    registerBestPlay(play, message);
/*
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

    path = legalMoves(gameState, path, &numLocations, trail, start);

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
        if(numLocations == 0 && player.currLocation[PLAYER_DRACULA] != HIDE) play = "D1";
        if(player.currLocation[PLAYER_DRACULA] == DOUBLE_BACK_1) play ="HIDE";
    }

    registerBestPlay(play, play);
*/
}
/*
static int *legalMoves(DracView gameState, int *path, int *numLocations, LocationID trail[TRAIL_SIZE], LocationID start) {
    // remove places in trail from path
    int counter, counter1;
    for(counter = numLocations[0] - 1; counter >= 0; counter--)
    {
        for(start = 0; start < TRAIL_SIZE; start++)
        {
            if(trail[start] == path[counter])
            {
                for(counter1 = counter; counter1 < numLocations[0] - 1; counter1++)
                {
                    path[counter1] = path[counter1 + 1];
                }
                numLocations[0]--;
            }
        }
    }
    return path;
}
*/
char *LoopMove(DracView gameState) {
    char* moves[ARRAY_SIZE]={"GA","CN","BS","IO","AT","VA","SA","SO","BC"};
    int i = giveMeTheRound(gameState)%ARRAY_SIZE;
    return moves[i];
}
