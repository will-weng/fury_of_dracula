// GameView.c ... GameView ADT implementation

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Places.h"
#include "Map.h"
#include <string.h>

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
static LocationID roundTrail[TRAIL_SIZE] = {UNKNOWN_LOCATION};

// some #defines to use
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
};


// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
    GameView gameView = malloc(sizeof(struct gameView));
    gameView->pastPlays = pastPlays;
    //strcpy(gameView->pastPlays, pastPlays);
    //Set number of rounds
    //**Using global variable instead of variable in struct
    gameView->roundNum = (strlen(pastPlays) + 1)/STRING_OF_ROUND;
    rounds = gameView->roundNum;

    //Set the Player
    gameView->player = ((strlen(pastPlays) + 1)/STRING_OF_MOVE) % 5;

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

    return gameView;
}
     
// Frees all memory previously allocated for the GameView toBeDeleted
void disposeGameView(GameView toBeDeleted)
{
    free(toBeDeleted);
}

//// Functions to return simple information about the current state of the game

// Get the current round
Round getRound(GameView currentView)
{
    return rounds;
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView)
{
    return currentView->player;
}

// Get the current score
int getScore(GameView currentView)
{
    return currentView->score;
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
    return currentView->health[player];
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
    if (player >= NUM_PLAYERS || player < 0) {
        return UNKNOWN_LOCATION;
    } else {
    	return currentView->currLocation[player];
    }
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns


void getHistory(GameView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    char play[STRING_OF_MOVE] = {0};
    int string, counter = 0;
    for(string = 0; string < TRAIL_SIZE; string++) {
        trail[string] = NOWHERE;
    }

    char playerChar = iDToChar(player);
    
    // while loop that reads until the end off the pastplay string
    while(counter < strlen(currentView->pastPlays)) {
        // loop that reads every 8 char of the past plays
        for(string = 0; string < STRING_OF_MOVE; counter++, string++) {
            play[string] = currentView->pastPlays[counter];
        }

        if(play[0] == playerChar) {

            char abbrev[3] = {0};
            abbrev[0] = play[1];
            abbrev[1] = play[2];
            abbrev[2] = 0;

            int i;
            
            for(i = TRAIL_SIZE; i > 0; i--) {
                trail[i] = trail[i - 1];
            }
            trail[0] = abbrevToID(abbrev);
        }
    }
}

//// Functions that query the map to find information about connectivity

// Returns an array of LocationIDs for all directly connected locations

LocationID *connectedLocations(GameView currentView, int *numLocations,
                               LocationID from, PlayerID player, Round round,
                               int road, int rail, int sea)
{
    return Locations(currentView, numLocations, from, player, round, road, rail, sea);
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
    while(counter < strlen(currentView->pastPlays)) {

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

    // updates the latest location of dracula
    currentView->currLocation[PLAYER_DRACULA] = abbrevToID(abbrev);

    // updates the global variable of how many vampires matured
    if(play[6] == 'V') {
        matured++;
    }

    int i;
    for(i = TRAIL_SIZE; i > 0; i--) {
        roundTrail[i] = roundTrail[i - 1];
    }
    roundTrail[0] = abbrevToID(abbrev);

    // updates health of dracula depending on the location
    if(roundTrail[0] == SEA_UNKNOWN || idToType(currentView->currLocation[PLAYER_DRACULA]) == SEA) {
        draculaHealth =  draculaHealth - LIFE_LOSS_SEA;
    } else if((roundTrail[0] - HIDE) > 0 && (roundTrail[0] - HIDE) < 6) {
        if(roundTrail[roundTrail[0] - HIDE] == SEA_UNKNOWN || idToType(roundTrail[roundTrail[0] - HIDE]) == SEA) {
            draculaHealth =  draculaHealth - LIFE_LOSS_SEA;
        }
    } else if(currentView->currLocation[PLAYER_DRACULA] == CASTLE_DRACULA) {
        draculaHealth = draculaHealth + LIFE_GAIN_CASTLE_DRACULA;
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
    if(currentView->currLocation[player] == ST_JOSEPH_AND_ST_MARYS
            && currentView->health[player] < 1) {
        currentView->health[player] = GAME_START_HUNTER_LIFE_POINTS;
    }
    if(currentView->currLocation[player] == abbrevToID(abbrev)) {
        currentView->health[player] = currentView->health[player] + LIFE_GAIN_REST;
        if(currentView->health[player] > GAME_START_HUNTER_LIFE_POINTS) {
            currentView->health[player] = GAME_START_HUNTER_LIFE_POINTS;
        }
    }
    
    currentView->currLocation[player] = abbrevToID(abbrev);
    // loss of health from encounters
    int i;
    for(i = 3; i < 7; i++) { 
        if(play[i] == 'T') {
            currentView->health[player] = currentView->health[player] - LIFE_LOSS_TRAP_ENCOUNTER;
        }
        if(play[i] == 'D') {
            currentView->health[player] = currentView->health[player] - LIFE_LOSS_DRACULA_ENCOUNTER;
            draculaHealth = draculaHealth - LIFE_LOSS_HUNTER_ENCOUNTER;
        }
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

    PlayerID player = -1;

    switch (playerChar) {
        case 'G':
            player = PLAYER_LORD_GODALMING;
            break;
        case 'S':
            player = PLAYER_DR_SEWARD;
            break;
        case 'H':
            player = PLAYER_VAN_HELSING;
            break;
        case 'M':
            player = PLAYER_MINA_HARKER;
            break;
        case 'D':
            player = PLAYER_DRACULA;
            break;
    }
    return player;
}

// changes an id number to a character
static char iDToChar(int playerID) {

    char playerChar = '\0';
    
    switch (playerID) {
        case PLAYER_LORD_GODALMING:
            playerChar = 'G';
            break;
        case PLAYER_DR_SEWARD:
            playerChar = 'S';
            break;
        case PLAYER_VAN_HELSING:
            playerChar = 'H';
            break;
        case PLAYER_MINA_HARKER:
            playerChar = 'M';
            break;
        case PLAYER_DRACULA:
            playerChar = 'D';
            break;
    }
    return playerChar;
}
