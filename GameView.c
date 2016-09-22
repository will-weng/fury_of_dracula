// GameView.c ... GameView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Places.h"
#include "Map.h"
     
static void readPlay(GameView currentView);
static void draculaPlays(char *play, GameView currentView);
static void hunterPlays(char *play, GameView currentView);
static void score(GameView currentView);
static int charToID(char playerChar);
static char iDToChar(int playerID);

// global variables that is useful for newGameView
static int rounds;
static int hospital;
static int matured;
static int draculaHealth;

// some #defines to use
#define STRING_OF_ROUND 40
#define STRING_OF_MOVE 8
#define PERIOD_OF_VAMPIRE_SPAWN 13

struct gameView {
    Map map;
    Round roundNum;
    PlayerID player;
    int currLocation[NUM_PLAYERS];
    int score; 
    int health[NUM_PLAYERS];  
    char *pastPlays;
};


// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    GameView gameView = malloc(sizeof(struct gameView));
    gameView->pastPlays = pastPlays;
    gameView->roundNum = (sizeof(pastPlays)/(STRING_OF_ROUND*sizeof(char)));
    rounds = gameView->roundNum;
    gameView->player = (rounds % 5);

    // initialises all hunters health and location, dracs health is updated later
    int counter;
    for(counter = 0; counter < 5; counter++) {
        gameView->health[counter] = GAME_START_HUNTER_LIFE_POINTS;
        gameView->currLocation[counter] = NOWHERE;
    }

    // reads the past plays string and updates location and health of players
    readPlay(gameView);
    gameView->health[PLAYER_DRACULA] = draculaHealth;
    
    // updates score of the game
    score(gameView);

    //Initialise game map
    gameView->map = newMap();

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
    return currentView->currLocation[player];
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void getHistory(GameView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
  int counter = 0; 
  int i, j;
  
  for(i = 0; i < TRAIL_SIZE; counter++, i++) {
    while(currentView->pastPlays[counter] != 0) {
      trail[i] = currentView->pastPlays[counter];
      if(i==6){
	for(j=0; j<6; j++){
	  trail[j] = trail[j+1];
	}
	i=0;
	trail[7] = 0;
      }
      
    }
  }
  
  // for(i=0; i<TRAIL_SIZE; i++){
  //  trail[i] = currentView->pastPos[player][i];
  // }
}

//// Functions that query the map to find information about connectivity

// Returns an array of LocationIDs for all directly connected locations

LocationID *connectedLocations(GameView currentView, int *numLocations,
                               LocationID from, PlayerID player, Round round,
                               int road, int rail, int sea)
{
    return Locations(currentView->map, currentView, numLocations, from, player, round, road, rail, sea);
}

// static function that reads the pastplay string
static void readPlay(GameView currentView) {
    
    // initialises some global variables and variables to be used
    draculaHealth = GAME_START_BLOOD_POINTS;
    hospital = 0;
    matured = 0;
    char play[STRING_OF_MOVE] = {0};
    int string, counter = 0;

    // while loop that reads until the end off the pastplay string
    while(currentView->pastPlays[counter] != 0) {
        // loop that reads every 8 char of the past plays
        for(string = 0; string < STRING_OF_MOVE; counter++, string++) {
            play[string] = currentView->pastPlays[counter];
        }

        // pass the "play" string into functions depending on player
        if(play[0] == iDToChar(PLAYER_DRACULA)) {
            draculaPlays(play, currentView);
        } else {
            hunterPlays(play, currentView);
        }

        // loop to check for when a hunter dies
        int i = 0;
        while(i < 4) {
            if(currentView->health[i] < 1) {
                hospital++;
                currentView->health[i] = 0;
                currentView->currLocation[i] = ST_JOSEPH_AND_ST_MARYS;
            }
            i++;
        }
    }
}

// static function to read the dracula's move
static void draculaPlays(char *play, GameView currentView) {

    // a terrible way to keep track of location
    char abbrev[3] = {0};
    abbrev[0] = play[1];
    abbrev[1] = play[2];
    abbrev[2] = 0;

    // updates the global variable of how many vampires matured
    if(play[6] == 'V') {
        matured++;
    }

    // updates the latest location of dracula
    currentView->currLocation[PLAYER_DRACULA] = abbrevToID(abbrev);

    // updates health of dracula depending on the location
    if(idToType(currentView->currLocation[PLAYER_DRACULA]) == SEA) {
        draculaHealth =- LIFE_LOSS_SEA;
    } else if(currentView->currLocation[PLAYER_DRACULA] == CASTLE_DRACULA ||
            (abbrev[0] == 'T' && abbrev[1] == 'P')) {
        draculaHealth =+ LIFE_GAIN_CASTLE_DRACULA;
    }
}

// static funciton that read the hunters move
static void hunterPlays(char *play, GameView currentView) {

    // similar terrible way to keep track of location
    char abbrev[3] = {0};
    abbrev[0] = play[1];
    abbrev[1] = play[2];
    abbrev[2] = 0;
    
    // an alright way to keep of which hunter it is
    int player = charToID(play[0]);
    
    // if the hunters last location was resting or the hospital
    if(currentView->currLocation[player] == abbrevToID(abbrev)) {
        currentView->health[player] =+ LIFE_GAIN_REST;
    } else if(currentView->currLocation[player] == ST_JOSEPH_AND_ST_MARYS
            && currentView->health[player] < 1) {
        currentView->health[player] = GAME_START_HUNTER_LIFE_POINTS;
    }

    currentView->currLocation[player] = abbrevToID(abbrev);

    // loss of health from encounters
    if(play[3] == 'T' || play[4] == 'T' || play[5] == 'T') {
        currentView->health[player] =- LIFE_LOSS_TRAP_ENCOUNTER;
    } else if(play[3] == 'D' || play[4] == 'D' || play[5] == 'D') {
        currentView->health[player] =- LIFE_LOSS_DRACULA_ENCOUNTER;
        draculaHealth=- LIFE_LOSS_HUNTER_ENCOUNTER;      
    }
}

// static function to calculate current score of the game
static void score(GameView currentView) {
    // initialzing total score to 366
    int totalScore = GAME_START_SCORE;

    // decreasing score by hospital visits
    totalScore = totalScore - (SCORE_LOSS_HUNTER_HOSPITAL * hospital);

    // decreasing score by vampires matured
    totalScore = totalScore - (SCORE_LOSS_VAMPIRE_MATURES * matured);

    // decrease score by the rounds played
    totalScore = totalScore - rounds;
    
    currentView->score = totalScore;
}

// changes a character to an id number
static int charToID(char playerChar) {

    PlayerID player = 0;

    if(playerChar == 'G') {
        player = PLAYER_LORD_GODALMING;
    } else if(playerChar == 'S') {
        player = PLAYER_DR_SEWARD;
    } else if(playerChar == 'H') {
        player = PLAYER_VAN_HELSING;
    } else if(playerChar == 'M') {
        player = PLAYER_MINA_HARKER;
    } else if(playerChar == 'D') {
        player = PLAYER_DRACULA;
    }
    return player;
}

// changes an id number to a character
static char iDToChar(int playerID) {

    char playerChar = '\0';

    if(playerID == PLAYER_LORD_GODALMING) {
        playerChar = 'G';
    } else if(playerID == PLAYER_DR_SEWARD) {
        playerChar = 'S';
    } else if(playerID == PLAYER_VAN_HELSING) {
        playerChar = 'H';
    } else if(playerID == PLAYER_MINA_HARKER) {
        playerChar = 'M';
    } else if(playerID == PLAYER_DRACULA) {
        playerChar = 'D';
    }
    return playerChar;
}
