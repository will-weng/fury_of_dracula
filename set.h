// set.h ... interface to simple Set of Strings
// Written by John Shepherd, September 2015

#ifndef SET_H
#define SET_H

#include "GameView.h"

typedef struct SetRep *Set;

// Function signatures

Set newSet();
void disposeSet(Set s);
void insertInto(Set s, LocationID id);
void dropFrom(Set s, LocationID id);
int  isElem(Set s, LocationID id);
int  nElems(Set s);
void showSet(Set s);

#endif
