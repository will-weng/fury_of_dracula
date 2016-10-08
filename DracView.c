// DracView.c ... DracView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "DracView.h"
#include "Places.h"
#include "Globals.h"
#include "Map.h"

// #include "Map.h" ... if you decide to use the Map ADT

#define TURN_SIZE 8
#define ROUND_SIZE 40     
struct dracView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	GameView gameview;
	
	Round roundNum;
    PlayerID player;
    int currLocation[NUM_PLAYERS];
    int score; 
    int health[NUM_PLAYERS];  
    char *pastPlays;
    int pastPos[NUM_PLAYERS][TRAIL_SIZE];
    
	int traps[NUM_MAP_LOCATIONS];
	int vampires[NUM_MAP_LOCATIONS];
};
     
static LocationID findID (char *pastPlays, int turnNum);

// Creates a new DracView to summarise the current state of the game
// newDracView() creates a new game view to summarise the current state of
// the game.
// pastPlays is a string of all the plays made in the game so far by all
// players (including Dracula) from earliest to most recent.
// For Dracula
// * the pastPlays string should contain full details of all moves
// * the last move should always be by Mina Harker
// messages is an array containing a playerMessage for each play in the game
// so far. It will have exactly the same number of elements as there are plays
// in pastPlays. The message from the first play will be at index 0, and so on.
// The contents of each playerMessage will be exactly as provided by the player.
// The "PlayerMessage" type is defined in Game.h.
// You are free to ignore messages if you wish.
DracView newDracView(char *pastPlays, PlayerMessage messages[])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    DracView dracView = malloc(sizeof(struct dracView));
	//copy everything=
	dracView->gameview = newGameView(pastPlays,messages);
	dracView->roundNum = getRound(dracView->gameview);
	dracView->player = getCurrentPlayer(dracView->gameview);
	
	dracView->score = getScore(dracView->gameview );
	
	int i = 0;
	while(i<NUM_PLAYERS) {
	dracView->health[i] = getHealth(dracView->gameview, i);
	dracView->currLocation[i] = getLocation(dracView->gameview,dracView->currLocation[i]);
	i++;
	}	
	//traps
	i = 0;
	while(i<NUM_MAP_LOCATIONS) {
		dracView->traps[i] = 0;	
		i++;
	}
	i = 0;
	while(i<NUM_MAP_LOCATIONS) {
		dracView->vampires[i] = 0;
		i++;
	}
    int turn = 0;    
    while (turn < strlen(pastPlays)) {
        //locate the first action of the turn in the string
        int action = turn+3;
        
        LocationID currentLocation = findID(pastPlays, turn+1);
        
        //update health points, locations of traps etc based on action
        if (pastPlays[turn] == 'D') {
           if (pastPlays[action] == 'T') {
				dracView->traps[currentLocation]++;
            }
            
            if (pastPlays[action+1] == 'V') {
				dracView->vampires[currentLocation]++;
            }
            
            if (pastPlays[action+2] == 'M') {
				dracView->traps[findID(pastPlays,(turn+1-ROUND_SIZE*6))]--;
            }
            
            // If vampire matured (not placed)
            if (pastPlays[action+2]== 'V') {
				dracView->vampires[findID(pastPlays,(turn+1-ROUND_SIZE*6))]--;
            }
        } else {
			while(action % TURN_SIZE != 0) {
				if(pastPlays[action] == 'T') {
					dracView->traps[currentLocation]--;				
				} else if (pastPlays[action] == 'V'){
					dracView->vampires[currentLocation]--;
				}
			action++;			
			}
        }
        turn = turn + TURN_SIZE;
    }
    
    return dracView;
}

static LocationID findID (char *pastPlays, int turnNum) {
	char abbrev[3] = {pastPlays[turnNum],pastPlays[turnNum+1],'\0'};	
	if (strcmp(abbrev, "HI") == 0 ||
        strcmp(abbrev, "D1") == 0) {        
        return findID(pastPlays, turnNum-ROUND_SIZE);        
    } else if (strcmp(abbrev, "D2") == 0) {        
        return findID(pastPlays,turnNum-ROUND_SIZE*2);        
    } else if (strcmp(abbrev, "D3") == 0) {        
        return findID(pastPlays,
                                turnNum-ROUND_SIZE*3);        
    } else if (strcmp(abbrev, "D4") == 0) {        
        return findID(pastPlays,turnNum-ROUND_SIZE*4);        
    } else if (strcmp(abbrev, "D5") == 0) {        
        return findID(pastPlays,turnNum-ROUND_SIZE*5);        
    } else {        
        return abbrevToID(abbrev);
}  
}
     
     
// Frees all memory previously allocated for the DracView toBeDeleted
void disposeDracView(DracView toBeDeleted)
{
    //COMPLETE THIS IMPLEMENTATION
    free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(DracView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->roundNum;
}

// Get the current score
int giveMeTheScore(DracView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->score;
}

// Get the current health points for a given player
int howHealthyIs(DracView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return getHealth(currentView->gameview, player);
}

// Get the current location id of a given player
LocationID whereIs(DracView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return getLocation(currentView->gameview, player);
}

// Get the most recent move of a given player
// Returns the start location and end location of that move
// Since Dracula moves last, the end location for other players is always known,
//   but the start location may be UNKNOWN_LOCATION (for a hunter's first move)
// The start and end locations can be the same
void lastMove(DracView currentView, PlayerID player,
                 LocationID *start, LocationID *end)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	LocationID pastMoves[TRAIL_SIZE];
	getHistory(currentView->gameview, player, pastMoves);
	*start = pastMoves[1];
	*end = pastMoves[0];
    return;	
}


// Find out what minions are placed at the specified location
void whatsThere(DracView currentView, LocationID where,
                         int *numTraps, int *numVamps)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	*numTraps = currentView->traps[where];
	*numVamps = currentView->vampires[where];
    return;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(DracView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	getHistory(currentView->gameview, player, trail);
}

//// Functions that query the map to find information about connectivity

// What are my (Dracula's) possible next moves (locations)
LocationID *whereCanIgo(DracView currentView, int *numLocations, int road, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
	
    return connectedLocations(currentView->gameview, numLocations,getLocation(currentView->gameview,PLAYER_DRACULA),PLAYER_DRACULA, getRound(currentView->gameview),road,FALSE,sea);
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(DracView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return connectedLocations(currentView->gameview, numLocations,getLocation(currentView->gameview,player),player,getRound(currentView->gameview),road,rail,sea);
}




