// HunterView.c ... HunterView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "HunterView.h"
// #include "Map.h" ... if you decide to use the Map ADT
#include "string.h"
     
struct hunterView {
    GameView game;
};

// Creates a new HunterView to summarise the current state of the game
HunterView newHunterView(char *pastPlays, PlayerMessage messages[])
{
    //Make a new GameView
    GameView newGame = newGameView(pastPlays, messages);

    //cast a GameView pointer to hunterView
    HunterView newHunterView = malloc(sizeof(struct hunterView));
    newHunterView->game = newGame;
    return newHunterView;
}
     
// Frees all memory previously allocated for the HunterView toBeDeleted
void disposeHunterView(HunterView toBeDeleted)
{
    free( toBeDeleted );
}

//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(HunterView currentView)
{
    return getRound(currentView->game);
}

// Get the id of current player
PlayerID whoAmI(HunterView currentView)
{
    return getCurrentPlayer(currentView->game);
}

// Get the current score
int giveMeTheScore(HunterView currentView)
{
    return getScore(currentView->game);
}

// Get the current health points for a given player
int howHealthyIs(HunterView currentView, PlayerID player)
{
    return getHealth(currentView->game,player);
}

// Get the current location id of a given player
LocationID whereIs(HunterView currentView, PlayerID player)
{
    return getLocation(currentView->game,player);
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(HunterView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    getHistory(currentView->game, player, trail);
}

//// Functions that query the map to find information about connectivity

// What are my possible next moves (locations)
LocationID *whereCanIgo(HunterView currentView, int *numLocations,
                        int road, int rail, int sea)
{
    
    LocationID from = whereIs(currentView, whoAmI(currentView));
    return connectedLocations(currentView->game, numLocations, from, whoAmI(currentView), giveMeTheRound(currentView), road, rail, sea);
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(HunterView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea)
{

    return connectedLocations(currentView->game, numLocations, whereIs(currentView,player),player,giveMeTheRound(currentView),road,rail,sea);
}
