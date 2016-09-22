// queue.h ... interface to simple Queue of Strings
// Written by John Shepherd, September 2015

#ifndef QUEUE_H
#define QUEUE_H

#include "GameView.h"

typedef struct QueueRep *Queue;

// Function signatures

Queue newQueue();
void disposeQueue(Queue);
void enterQueue(Queue,LocationID);
LocationID leaveQueue(Queue);
int  emptyQueue(Queue);
void showQueue(Queue q);

#endif
