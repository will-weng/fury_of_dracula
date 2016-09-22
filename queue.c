// queue.c ... simple Queue of Strings
// Written by John Shepherd, September 2015

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "queue.h"

typedef struct Node *Link;

typedef struct Node {
	LocationID id;
	Link  next;
} Node;
	
typedef struct QueueRep {
	Link  front;
	Link  back;
} QueueRep;

// Function signatures

Queue newQueue();
void disposeQueue(Queue);
void enterQueue(Queue,LocationID);
LocationID leaveQueue(Queue);
int  emptyQueue(Queue);
void showQueue(Queue q);

static Link newNode(LocationID);
static void disposeNode(Link);


// newQueue()
// - create an initially empty Queue
Queue newQueue()
{
	Queue new = malloc(sizeof(QueueRep));
	assert(new != NULL);
	new->front = NULL;
	new->back = NULL;
	return new;
}

// disposeQueue(Queue)
// - clean up memory associated with Queue
void disposeQueue(Queue q)
{
	if (q == NULL) return;
	Link next, curr = q->front;
	while (curr != NULL) {
		next = curr->next;
		disposeNode(curr);	
		curr = next;
	}
}

// enterQueue(Queue,Str)
void enterQueue(Queue q, LocationID id)
{
	Link new = newNode(id);
	if (q->front == NULL)
		q->front = q->back = new;
	else {
		// add into list of elems
		q->back->next = new;
		q->back = new;
	}
}

// leaveQueue(Queue)
// - return string at front of Queue
LocationID leaveQueue(Queue q)
{
	assert (q->front != NULL);
    LocationID id = q->front->id;
	Link old = q->front;
	q->front = old->next;
	if (q->front == NULL)
		q->back = NULL;
	free(old);
	return id;
}

// emptyQueue(Queue)
// - check whether Queue is empty
int emptyQueue(Queue q)
{
	return (q->front == NULL);
}

// showQueue(Queue)
// - display Queue (for debugging)
void showQueue(Queue q)
{
	Link curr;
	if (q->front == NULL)
		printf("Queue is empty\n");
	else {
		printf("Queue (front-to-back):\n");
		int id = 0;
		curr = q->front;
		while (curr != NULL) {
			printf("[%03d] %d\n", id, curr->id);
			id++;
			curr = curr->next;
		}
	}
}

// Helper functions

static Link newNode(LocationID id)
{
	Link new = malloc(sizeof(Node));
	assert(new != NULL);
	new->id = id;
	new->next = NULL;
	return new;
}

static void disposeNode(Link curr)
{
	assert(curr != NULL);
	free(curr);
}

