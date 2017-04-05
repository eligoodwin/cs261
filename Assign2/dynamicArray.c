

/*	dynamicArray.c: Dynamic Array implementation. */
/* CS261- Assignment 2. 0*/
/* Name: Eli Goodwin
 * Date: 2017.01.25
 * Solution description: creates a dynamic array data structure that can be used as a stack or bag
 */



#include <assert.h>
#include <stdlib.h>
#include "dynArray.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};


/* ************************************************************************
	Dynamic Array Functions
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

	param: 	v		pointer to the dynamic array
	param:	cap 	capacity of the dynamic array
	pre:	v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
*/
void initDynArr(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v!= 0);
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;	
}

/* Allocate and initialize dynamic array.

	param:	cap 	desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
			and 0 elements in it.		
*/
DynArr* newDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}

/* Deallocate data array in dynamic array. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/* Resizes the underlying array to be the size cap 

	param: 	v		pointer to the dynamic array
	param:	cap		the new desired capacity
	pre:	v is not null
	post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap)
{
    
    
	/* FIXME: You will write this function DONE */
    //make sure the array is not empty
    assert(v != NULL);
   
    //create a temp array of the desired capacity
    int sizeStorage = v->size;
    
    TYPE *tempArr = (TYPE*)malloc(sizeof(TYPE)*newCap);
    
    //copy elements to the new array
    for(int i = 0; i < v->size; ++i)
    {
        tempArr[i] = v->data[i];
    }
    
    //free old array
    freeDynArr(v);
    
    //set new array to old array
    
    v->data = tempArr;
    v->size = sizeStorage;
    v->capacity = newCap;

    
    //destroy the temp array
    

	
}

/* Get the size of the dynamic array

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	return v->size;
}

/* 	Adds an element to the end of the dynamic array

	param: 	v		pointer to the dynamic array
	param:	val		the value to add to the end of the dynamic array
	pre:	the dynArry is not null
	post:	size increases by 1
	post:	if reached capacity, capacity is doubled
	post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val)
{
	/* FIXME: You will write this function */
    assert(v != NULL);
    
    int testSize = v->size;
    
    //check if cap <= size, if so allocate a new array
    if(testSize >= v->capacity)
    {
        _dynArrSetCapacity(v, 2 * v->capacity);
    }

    //shove data into new index at size
    v->data[v->size] = val;
    
    //increment size
    v->size++;


}

/*	Get an element from the dynamic array from a specified position
	
	param: 	v		pointer to the dynamic array
	param:	pos		integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
*/

TYPE getDynArr(DynArr *v, int pos)
{
    
	/* FIXME: You will write this function */
    //test if pos is valid
    assert(v !=  NULL);
    assert(v->size != 0);
    assert(pos < v->size);
    assert(pos >= 0);
    
    /* FIXME: you must change this return value */
    return v->data[pos];
}

/*	Put an item into the dynamic array at the specified location,
	overwriting the element that was there

	param: 	v		pointer to the dynamic array
	param:	pos		the index to put the value into
	param:	val		the value to insert 
	pre:	v is not null
	pre:	v is not empty
	pre:	pos >= 0 and pos < size of the array
	post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val)
{
	/* FIXME: You will write this function */
    //test pre conditions
    assert(v !=  NULL);
    assert(v->size != 0);
    assert(pos < v->size);
    assert(pos >= 0);
    
    //insert into array
    v->data[pos] = val;
    
}

/*	Swap two specified elements in the dynamic array

	param: 	v		pointer to the dynamic array
	param:	i,j		the elements to be swapped
	pre:	v is not null
	pre:	v is not empty
	pre:	i, j >= 0 and i,j < size of the dynamic array
	post:	index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *v, int i, int  j)
{
    //test pre conditions
    assert(v !=  NULL);
    assert(v->size != 0);
    assert(i < v->size);
    assert(j < v->size);
    
	/* FIXME: You will write this function */
    TYPE temp;
    
    //move data from i to temp
    temp = v->data[i];
    
    //move data from j to what was i
    v->data[i] = v->data[j];
    
    //move temp to j
    v->data[j] = temp;
    
}

/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap

	param: 	v		pointer to the dynamic array
	param:	idx		location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *v, int idx)
{
	/* FIXME: You will write this function */
    assert(v !=  NULL);
    assert(v->size != 0);
    assert(idx < v->size);
    assert(idx != 0);
    
    //go to that position specified by idx, set iterator to idx,
    for(int i = idx; i < v->size; ++i)
    {
        v->data[i] = v->data[i + 1];
    }
    
    //decrement size
    v->size -= 1;
    
    
}



/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the 
	dynamic array stack has an item on it.

	param:	v		pointer to the dynamic array
	pre:	the dynArr is not null
	post:	none
	ret:	1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *v)
{
	/* FIXME: You will write this function */
    assert(v != NULL);
    
    int empty = 0; //result of empty empty test
    
    //is there an item in the top of the stack
    if(v->size == 0)
    {
        empty = 1;
    }
    
	/* FIXME:  You will change this return value*/
	return empty;
}

/* 	Push an element onto the top of the stack

	param:	v		pointer to the dynamic array
	param:	val		the value to push onto the stack
	pre:	v is not null
	post:	size increases by 1
			if reached capacity, capacity is doubled
			val is on the top of the stack
*/
void pushDynArr(DynArr *v, TYPE val)
{
	/* FIXME: You will write this function */
    assert(v != NULL);
    
    int testSize = v->size;
    if(testSize >= v->capacity)
    {
        _dynArrSetCapacity(v, 2 * v->capacity);
    }
    
    v->data[v->size] = val;
    v->size += 1;
    
    
}

/*	Returns the element at the top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the stack
*/
TYPE topDynArr(DynArr *v)
{
	/* FIXME: You will write this function */
    assert(v != NULL);
    //assert(v->size != 0);
    
	/* FIXME: You will change this return value*/
	return v->data[v->size - 1];
}

/* Removes the element on top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	size is decremented by 1
			the top has been removed
*/
void popDynArr(DynArr *v)
{
	/* FIXME: You will write this function */
    assert(v != NULL);
    assert(v->size != 0);
    
    
    //set top of stack to 0
    v->data[v->size - 1] = 0;
    v->size -= 1;
    
}

/* ************************************************************************
	Bag Interface Functions
************************************************************************ */

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	v		pointer to the dynamic array
	param:	val		the value to look for in the bag
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the bag
*/
int containsDynArr(DynArr *v, TYPE val)
{
    
	/* FIXME: You will write this function */
    assert(v != NULL);
    assert(v->size != 0);
    
    int found = 0; //was the val found in the bag?
    
    for(int i = 0; i < v->size; ++i)
    {
        if(v->data[i] ==  val)
        {
            found = 1;
        }
    }
	
	/* FIXME:  You will change this return value */
	return found;

}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	v		pointer to the dynamic array
	param:	val		the value to remove from the array
	pre:	v is not null
	pre:	v is not empty
	post:	val has been removed
	post:	size of the bag is reduced by 1
*/
void removeDynArr(DynArr *v, TYPE val)
{
	/* FIXME: You will write this function */
    assert(v != NULL);
    assert(v->size != 0);
    
    int count = 0; //counter for the while loop
    
    //find location of val if it exists
    while(count < v->size && val != v->data[count])
    {
        //if the data in the element in question is == to the val, remove and adjust the array entries
        if(v->data[count] == val)
        {
            for(int i = count; i < v->size; ++i)
            {
                v->data[i] = v->data[i + 1];
            }
            
            //decrement size by 1
            v->size -= 1;
        }
        
        ++count;
    }
    
    //remove val and then move all values down one
    
    
}
