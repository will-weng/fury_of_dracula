// set.c ... simple, inefficient Set of Strings
// Written by John Shepherd, September 2015

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "set.h"

typedef struct Node *Link;

typedef struct Node {
	LocationID val;
	Link  next;
} Node;
	
typedef struct SetRep {
	int   nelems;
	Link  elems;
} SetRep;

// Function signatures

Set newSet();
void disposeSet(Set);
void insertInto(Set,LocationID);
void dropFrom(Set,LocationID);
int  isElem(Set,LocationID);
int  nElems(Set);

static Link newNode(LocationID);
static void disposeNode(Link);
static int  findNode(Link,LocationID);


// newSet()
// - create an initially empty Set
Set newSet()
{
	Set new = malloc(sizeof(SetRep));
	assert(new != NULL);
	new->nelems = 0;
	new->elems = NULL;
	return new;
}

// disposeSet(Set)
// - clean up memory associated with Set
void disposeSet(Set s)
{
	if (s == NULL) return;
	Link next, curr = s->elems;
	while (curr != NULL) {
		next = curr->next;
		disposeNode(curr);	
		curr = next;
	}
}

// insertInto(Set,Str)
// - ensure that Str is in Set
void insertInto(Set s, LocationID id)
{
    assert(s != NULL);
    Link curr = s->elems;

    //If the list is empty
    if(s->elems == NULL) {
        s->elems = newNode(id);
    } else {
        if (findNode(s->elems,id)) return; // already in Set
        Link new = newNode(id);
        while (curr->next != NULL) {
            curr = curr->next; 
        }
        curr->next = new;
    }
    s->nelems++;
}
/*
// dropFrom(Set,Str)
// - ensure that Str is not in Set
void dropFrom(Set s, LocationID id)
{
	assert(s != NULL);
	Link curr, prev;
	int found = findNode(s->elems,id);
	if (!found) return;
	s->nelems--;
	if (prev == NULL)
		s->elems = curr->next;
	else
		prev->next = curr->next;
	disposeNode(curr);
}*/

// isElem(Set,Str)
// - check whether Str is contained in Set
int isElem(Set s, LocationID id)
{
	assert(s != NULL);
	return findNode(s->elems,id);
}

// nElems(Set)
// - return # elements in Set
int  nElems(Set s)
{
	assert(s != NULL);
	return s->nelems;
}

// showSet(Set)
// - display Set (for debugging)
void showSet(Set s)
{
	Link curr;
	if (s->nelems == 0)
		printf("Set is empty\n");
	else {
		printf("Set has %d elements:\n",s->nelems);
		int id = 0;
		curr = s->elems;
		while (curr != NULL) {
			printf("[%03d] %d\n", id, curr->val);
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
	new->val = id;
	new->next = NULL;
	return new;
}

static void disposeNode(Link curr)
{
	assert(curr != NULL);
	free(curr);
}

static int findNode(Link list, LocationID id)
{
    int num  = id;
    Link curr = list;
    while (curr->next != NULL) {
        if(curr->val == num) return TRUE;
        curr = curr->next;
    }
    return FALSE;
}

//Function that converts a set (linked list) to an array
 int *setToArray (Set s) {
     int i = 0;
     int *array = malloc(sizeof(int) * s->nelems);
     Link curr = s->elems;
     while(curr!= NULL) {
        array[i] = curr->val;
        curr = curr->next;
        i++;
     }
     return array;
 }
