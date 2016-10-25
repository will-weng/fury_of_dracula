// hunter.c
// Implementation of your "Fury of Dracula" hunter AI

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Game.h"
#include "HunterView.h"
#include "Places.h"
#include "queue.h"
#include "Map.h"

#define MAX_PATH_LENGTH 20
#define NOT_SEEN -1

static LocationID *randMove(int numLocations);


//  =====   UNFINISHED  =====
//static int *shotestPath(LocationID start, LocationID end, int *path);

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
    
    //  =====   UNFINISHED  =====
    // used to record the shortest path to destination 
    // int path[MAX_PATH_LENGTH];

    // fills out the game info struct
    gameInfo.me = whoAmI(gameState);
    gameInfo.round = giveMeTheRound(gameState);
    gameInfo.places = whereCanIgo(gameState, &numLocations, TRUE, TRUE, TRUE);
    for(counter = 0; counter < NUM_PLAYERS; counter++) {
        gameInfo.currLocation[counter] = whereIs(gameState, counter);
    }

    // *****algorithm to decide where to go*****
        // TODO
        /* 
            try and make decisions depending on the player
            eg. player 1 go to where dracula might be heading,
                player 2 go to where dracula was
                player 3 go to where dracula is
                player 4 stay around DC
            this pretty much decides our AI's intelligence
         */
    // ***** any one can work on this *****

    //  =====   UNFINISHED  =====
    // find shortest path to where we want to go
    // don't know how to do it just yet
    //shotestPath(gameInfo.currLocation[gameInfo.me], gameInfo.currLocation[PLAYER_DRACULA], path);

    // individual decisions of hunters
    if(gameInfo.me == PLAYER_LORD_GODALMING)
    {
        play = randMove(numLocations);
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

/*
=====   UNFINISHED  =====
static int *shotestPath(LocationID start, LocationID end, int *path) {

    int seen[NUM_MAP_LOCATIONS], counter = 0;

    // initialises seen array;
    while(counter < NUM_MAP_LOCATIONS) {
        seen[counter] = NOT_SEEN;
        counter++;
    }

    Queue locations = newQueue();
    enterQueue(locations, start);
    LocationID *places;

    while(!emptyQueue(locations)) {
        
        LocationID distance = 0, j = leaveQueue(locations);
        
        if(seen[j] != NOT_SEEN)
            continue;

        places = Locations();
        seen[j] = distance;

    }

    return path;
}
*/

/*** Make a random move ***/
/* Players will choose a random location to move to from the 
   get *connectedLocations array */

static LocationID *randMove(int numLocations) {
    LocationID *moves = gameInfo.places;
    //Pick a random location from within this array
    
    srand(time(NULL));  //set seed by using system time
    int i = rand()%&numLocations;
    return moves[i];
}
