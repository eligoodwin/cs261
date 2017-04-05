/*
 circularList.c: Implementation of a ciruclar linked list
 CS261 - Assignment 3
 name: Eli Goodwin
 Date: 2017.02.04
 Solution Description: Implementation of a circularly linked list implemented as a deque  
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this
    //make the head pointer
    struct Link* head = malloc(sizeof(struct Link));
    assert(head != NULL);
    
    //set pointers
    head->next = head;
    head->prev = head;
    
    //set list sentinel
    list->sentinel = head;
    
    //set size
    list->size  = 0;
    
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXME: you must write this
    //init a new link
    struct Link* newLink = malloc(sizeof(struct Link));
    
    //make sure it was allocated
    assert(newLink != 0);
    
    //set fields
    newLink->next = NULL;
    newLink->prev = NULL;
    newLink->value = value;
    
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
    
    //new link to insert
    struct Link* newLink = createLink(value);
    
    //point to the next link
    newLink->next = link->next;
    
    //point to the new link
    link->next = newLink;
    
    //have the next link after new point to new
    newLink->prev = link;
    newLink->next->prev = newLink;
    
    //increment list size
    ++list->size;
    
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this
    
    //make sure the list is allocated
    assert(list != NULL);
    //make sure the list is not empty
    assert(list->size != 0);

    //temp list nodes for link removal
    struct Link* prevLink = link->prev;
    struct Link* nextLink = link->next;
    
    //point the pointers to the correct spots
    prevLink->next = nextLink;
    nextLink->prev = prevLink;
    
    //free the node to delete
    link->next = NULL;
    link->prev = NULL;
    free(link);
    
    //decrement size
    list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
    
    //make sure the list is allocated
    assert(list != NULL);
    
    struct Link* temp = NULL;
    
    //while the list is not empty destroy it
    while(!circularListIsEmpty(list)){
        //repeatedly destory the first element, eventually the list is killed
        temp = list->sentinel->next;
        removeLink(list, temp);
    }
    
    //free stuff that was allocated
    free(list->sentinel);
    free(list);
    
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);


    addLinkAfter(list, list->sentinel, value);

}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);
    
    addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);
    
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);
    
    //make sure the list is not empty
    assert(list->size != 0);
    
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);
    
    //make sure the list is not empty
    assert(list->size != 0);
    removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this
    
    //make sure the list is allocated
    assert(list != NULL);
    
    //make sure the list is not empty
    assert(list->size != 0);
    
    removeLink(list, list->sentinel->prev);
    
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this
    int isEmpty = 0; //flag for empty list
    
    //is size == 0?
    if(list->size == 0){
        isEmpty = 1;
    }
    
	return isEmpty;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);

    
    //get the first node
    struct Link* current = list->sentinel->next; //used for traversing the list
    struct Link* endList = list->sentinel; //flag for the end of the list
    int isEmpty = circularListIsEmpty(list); //is the list empty?
    
    //if the list is not empty print its contents
    if(isEmpty != 1){
        //traverse while current does not sentitnel/end of list
        while(current != endList){
            printf("%f, ", current->value);
            current = current->next;
        }
        printf("\n");
    }
    
    else{
        printf("The list is empty, nothing to print.");
    }
    
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
    
    //make sure the list is allocated
    assert(list != NULL);
    
    //make sure the list is not empty
    assert(list->size != 0);
    
    struct Link* current = list->sentinel; //used to temp the list
    struct Link* otherLink = list->sentinel->next; //used for traversing pointers
    
    //traverse the list for it's length and switch the pointers around accordingly
    for(int i = 0; i <= list->size; ++i){
        //switch next and prev in the link in question
        current->next = current->prev;
        current->prev = otherLink;
        current = otherLink;
        
        //move to the next link
        otherLink = otherLink->next;
        
    }
    
    
    
}
