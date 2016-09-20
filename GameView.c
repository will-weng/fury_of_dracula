// GameView.c ... GameView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
// #include "Map.h" ... if you decide to use the Map ADT
     
static int score(char *pastPlays);
static int hospital(char *pastPlays);
static int matured(char *pastPlays);

static int rounds;

#define STRING_OF_ROUND 40
#define STRING_OF_MOVE 8
#define PERIOD_OF_VAMPIRE_SPAWN 13

struct gameView {
    Round roundNum;
    PlayerID player;
    int currLocation[NUM_PLAYERS];
    int score; 
    int health[NUM_PLAYERS];  
    char *pastPlays;
    int pastPos[NUM_PLAYERS][TRAIL_SIZE];
};


// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    GameView gameView = malloc(sizeof(struct gameView));
    gameView->roundNum = (sizeof(pastPlays)/(STRING_OF_ROUND*sizeof(char)));
    rounds = gameView->roundNum;
    gameView->player = (rounds % 5);
    //gameView->health = 
    gameView->score = score(gameView->pastPlays);
    return gameView;
}
     
     
// Frees all memory previously allocated for the GameView toBeDeleted
void disposeGameView(GameView toBeDeleted)
{
    //COMPLETE THIS IMPLEMENTATION
    free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round getRound(GameView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->roundNum;
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->player;
}

// Get the current score
int getScore(GameView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->score;
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->health[player];
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->currLocation[player];
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void getHistory(GameView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
  int i;
  for(i=0; i<TRAIL_SIZE; i++){
    trail[i] = currentView->pastPos[player][i];
  }
}

//// Functions that query the map to find information about connectivity

// Returns an array of LocationIDs for all directly connected locations

LocationID *connectedLocations(GameView currentView, int *numLocations,
                               LocationID from, PlayerID player, Round round,
                               int road, int rail, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return NULL;
}

// static function to calculate current score of the game
static int score(char *pastPlays) {
    // initialzing total score to 366
    int totalScore = GAME_START_SCORE;

    // decreasing score by hospital visits
    totalScore = totalScore - (SCORE_LOSS_HUNTER_HOSPITAL * hospital(pastPlays));

    // decreasing score by vampires matured
    totalScore = totalScore - (SCORE_LOSS_VAMPIRE_MATURES * matured(pastPlays));

    // decrease score by the rounds played
    totalScore = totalScore - rounds;
    
    return totalScore;
}

// static function to calculate hospital visits used to calculate score
static int hospital(char *pastPlays) {
    int visits = 0;

//    char moveRead[STRING_OF_MOVES] = {};

    return visits;
}

// static function to calculate vampires matured used to calculate score
static int matured(char *pastPlays) {

    int vampires = 0;
    int counter;
    int firstMature = 6 * STRING_OF_ROUND + 37;

    // reads for if a vampire matures
    for(counter = 0; counter * PERIOD_OF_VAMPIRE_SPAWN + 6 < rounds; counter++) {
        if(pastPlays[firstMature + STRING_OF_ROUND * PERIOD_OF_VAMPIRE_SPAWN * counter] == 'V') {
            vampires++;
        }
    }

    return vampires;
}