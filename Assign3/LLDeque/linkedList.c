/*
 cs261 - Assignment 3
 Name: Eli Goodwin
 Date: 2017.02.04
 Solution Description: Implementation of a doubly linked list as a deque and as a bag. 
 
 
 */


#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
    TYPE value;
    struct Link* next;
    struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
    int size;
    struct Link* frontSentinel;
    struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
    // FIXME: you must write this
    
    
    //allocate sentinels
    struct Link* head = malloc(sizeof(struct Link));
    assert(head != NULL);
    struct Link* tail = malloc(sizeof(struct Link));
    assert(tail != NULL);
    
    //set their respective next and prev
    head->next = tail;
    head->prev = NULL;
    
    tail->prev = head;
    tail->next = NULL;
    
    list->frontSentinel = head;
    list->backSentinel  = tail;
    
    //set size to 0
    list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
    // FIXME: you must write this
    
    //make sure the list is not NULL
    assert(list != NULL);
    
    //allocate a new link
    struct Link* newLink = malloc(sizeof(struct Link));
    
    //set value
    newLink->value = value;
    //set new link pointers
    
    newLink->prev = link->prev;
    newLink->next = link;
    link->prev->next = newLink;
    link->prev = newLink;
    
    
    //increment size
    list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
    // FIXME: you must write this
    //make sure the link does is not null
    assert(link != NULL);
    
    //temp variables for manipulation of the list
    struct Link* deleteLink = link;
    struct Link* prevLink = link->prev;
    struct Link* nextLink = link->next;
    
    //have previous link point to the next link after target link
    prevLink->next = nextLink;
    nextLink->prev = prevLink;
    
    //free removed link
    free(deleteLink);
    
    //decrement size of list
    list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
    struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
    init(newDeque);
    return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
    //make sure the list is not empty
    assert(list != NULL);
    
    //remove links while size is greater than 0
    while (!linkedListIsEmpty(list))
    {
        linkedListRemoveFront(list);
    }
    
    //free all stuff after the list is destroyed
    free(list->frontSentinel);
    free(list->backSentinel);
    free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
    // FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);
    
    //add link to the front of the list following the sentinel pointer
    addLinkBefore(list, list->frontSentinel->next, value);
    
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
    // FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);

    //add to the the link before back sentinel
    addLinkBefore(list, list->backSentinel, value);
    
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
    // FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);

    return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
    // FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);
    
    //make sure the list not empty
    

    return list->backSentinel->prev->value;
    
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
    // FIXME: you must write this
    
    //make sure the list is allocated
    assert(list != NULL);
    //make sure the list is not empty
    assert(list->size != 0);
    
    //make sure the list is not empty
    assert(list->size != 0);
    
    removeLink(list, list->frontSentinel->next);
    
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
    // FIXME: you must write this
    
    //make sure the list is allocated
    assert(list != NULL);
    //make sure the list is not empty
    assert(list->size != 0);

    //pass the link that backSentinel points to and remove it
    removeLink(list, list->backSentinel->prev);
    
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
    // FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);

    int isEmpty = 0; //flag for if frontsentinel is null
    
    //what is the list size? if 0 it is empty
    if(list->size == 0){
        isEmpty = 1;
    }
    
    return isEmpty;
    
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
    // FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);
    
    //make sure the list is not empty
    assert(list->size != 0);
    
    //set current to the next value stored by front sentinel
    struct Link* current = list->frontSentinel->next;
    
    //traverse and print while current is not equal to the tail pointer
    while(current->next != NULL){
        printf("%i, ", current->value);
        current = current->next;
    }
    printf("\n");

}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
    // FIXME: you must write this
    
    //make sure the list is allcoated
    assert(list != NULL);

    linkedListAddFront(list, value);
    
    
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
    // FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);
    
    //make sure the list is not empty
    assert(list->size != 0);

    struct Link* current = list->frontSentinel->next; //used for traversal
    int foundValue = 0; //flag for if the value was found
    
    //linear search until the value is found or current is equal to the tail pointer
    while(current != list->backSentinel && foundValue == 0){
        //if value is found, trip the flag
        if(current->value == value){
            foundValue = 1;
        }
        
        //traverse
        current = current->next;
    }
    
    return foundValue;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
    // FIXME: you must write this
    //make sure the list is allocated
    assert(list != NULL);
    //make sure the list is not empty
    assert(list->size != 0);

    struct Link* current = list->frontSentinel->next; //set current to whatever
    int valueFound = 0; //flag for if the value was found or not
    
    //search for the value while the value is not found and traversal has not reached the end of the list
    while(current != list->backSentinel && valueFound == 0){
        if(current->value == value){
            valueFound = 1;
            removeLink(list, current);
            
            return;
            
        }
        current = current->next;
    }
    
}
