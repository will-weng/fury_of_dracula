// Map.h ... interface to Map data type

#ifndef MAP_H
#define MAP_H

#include "Places.h"
#include "Queue.h"

typedef struct edge{
    LocationID  start;
    LocationID  end;
    TransportID type;
} Edge;

// graph representation is hidden 
typedef struct MapRep *Map; 

// operations on graphs 
Map newMap();
void disposeMap(Map g); 
void showMap(Map g); 
int numV(Map g);
int numE(Map g, TransportID t);

//Custom Functions
LocationID *Locations(Map g, GameView currentView, int *numLocations, LocationID from, PlayerID player, Round round, int road, int rail, int sea);

#endif
