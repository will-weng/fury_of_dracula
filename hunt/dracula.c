// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"
#include "Places.h"

void decideDraculaMove(DracView gameState)
{
	// TODO ...
	// Replace the line below by something better
    int location = 10;
    int places[10];
    LocationID *array = whereCanIgo(gameState, &location,TRUE,FALSE);  
    int i;
    for(i = 10; i > 1; i--)
    {
        places[i] = array[i];
    }
    
    printf("%s", idToName(places[3]));
	registerBestPlay(idToName(places[3]),"Mwuhahahaha");
}
