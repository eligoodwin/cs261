/*
 * CS 261 Data Structures
 * Assignment 6
 * Name: 
 * Date: 
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement
    HashLink* deleteLink = NULL;
    HashLink* currentLink = NULL;
    
    //if table [i] is not null,
    for(int i = 0; i < map->capacity; ++i){
        //if null skip
        if(map->table[i] != NULL){
            //set traversal link
            currentLink = map->table[i];
            map->table[i] = NULL;
            
            while(currentLink != NULL){
                deleteLink = currentLink;
                currentLink = currentLink->next;
                //delete the link
                hashLinkDelete(deleteLink);
            }
        }
        
        free(map->table[i]);
        
    }
    
    //free the table
    free(map->table);
    
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
    HashLink* currentLink = NULL;
    //hash for idx,
    int indx = HASH_FUNCTION(key) % map->capacity;
    currentLink = map->table[indx];
    
    //go to that indx and then traverse until found
    while(currentLink != NULL){
        if(strcmp(currentLink->key, key) == 0){
            //found
            return &currentLink->value;
        }
        currentLink = currentLink->next;
    }
    //not found
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // FIXME: implement
    
    //save old table
    HashLink* currentLink = NULL;
    HashLink* deleteLink = NULL;
    
    HashLink** oldTable = map->table;
    int oldCapacity = map->capacity;
    
    //init a new map, using old map
    hashMapInit(map, capacity);
    
    //rehash values into buckets using put
    for(int i = 0; i < oldCapacity; ++i){
        if(oldTable[i] != NULL){
            //get the link
            currentLink = oldTable[i];
            //traverse and shove into the new map's buckets and delete the previous link
            while(currentLink != NULL){
                deleteLink = currentLink;
                //has into new map
                hashMapPut(map, currentLink->key, currentLink->value);
                currentLink = currentLink->next;
                hashLinkDelete(deleteLink);
            }
            
            oldTable[i] = NULL;

        }
        //free the old table index
        free(oldTable[i]);
    }
    //free the old table
    free(oldTable);

    
    return;
    
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIXME: implement
    int indx = 0;
    HashLink* currentLink = NULL;
    HashLink* newLink = NULL;
    
    //test if what the load is, if greater than hashloadmax, increase the size of the hashtable
    if(hashMapTableLoad(map) >= MAX_TABLE_LOAD){
        resizeTable(map, map->capacity * 2);
    }
    
    //get the indx to insert the key and value
    indx = HASH_FUNCTION(key) % map->capacity;
    currentLink = map->table[indx];
    
    //test if indx is null, if so insert
    if(currentLink == NULL){
        //create a new link
        newLink = hashLinkNew(key, value, NULL);
        map->table[indx] = newLink;
    }
    
    //find the place to insert
    else{
        //traverse until key is found and increment
        while(currentLink != NULL){
            //if keys are the same replace the value
            if(strcmp(currentLink->key, key) == 0){
                currentLink->value = value;
                return;
            }
            //traverse
            currentLink = currentLink->next;
        }
        
        //insert as stack if it wasn't found in the bucket
        newLink = hashLinkNew(key, value, map->table[indx]);
        //reset the stack pointer in table to have the new link
        map->table[indx] = newLink;
    }
    
    //increment size
    ++map->size;
    return;
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
    HashLink* currentLink = NULL; //current link being looked at
    HashLink* prevLink = NULL; //trailing link
    int indx = 0;
    
    indx = HASH_FUNCTION(key) % map->capacity;

    //if the indx is null, nothing there
    if(map->table[indx] == NULL)
        return;
    

    //traverse the bucket searching
    currentLink = map->table[indx];
    while(currentLink != NULL){
        if(strcmp(currentLink->key, key) == 0){
            //if at head adjust accordingly
            if(currentLink == map->table[indx]){
                map->table[indx] = currentLink->next;
                hashLinkDelete(currentLink);
            }
            
            else{
                //set previous pointer to the next pointer after current
                prevLink->next =  currentLink->next;
                hashLinkDelete(currentLink);
            }
            currentLink = NULL;
            --map->size;

        }
        else{
            prevLink = currentLink;
            currentLink = currentLink->next;
        }
    }
    
    
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement
    HashLink* currentLink = NULL;
    
    //get the index
    int indx = HASH_FUNCTION(key) % map->capacity;
    if(map->table[indx] == NULL){
        return 0;
    }
    
    currentLink = map->table[indx];
    //traverse until found
    while(currentLink != NULL){
        //if the is found return true;
        if(strcmp(currentLink->key, key) == 0){
            return 1;
        }
        currentLink = currentLink->next;
    }
    
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
    int count = 0; //counter for empty buckets
    for(int i = 0; i < map->capacity; ++i){
        if(map->table[i] == NULL){
            ++count;
        }
    }
    
    return count;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
    float numberLinks = (float)map->size;
    float numberBuckets = (float)map->capacity;
    
    return numberLinks/numberBuckets;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}
