/** 
    @file map.h
    @author
    Header for the map component, a hash map.
*/

#ifndef MAP_H
#define MAP_H

#include "vtype.h"
#include <stdbool.h>

/** Incomplete type for the Map representation. */
typedef struct MapStruct Map;

/** Make an empty map.
    @param len Initial length of the hash table.
    @return pointer to a new map.
*/
Map *makeMap( int len );

/** Get the size of the given map.
    @param m Pointer to the map.
    @return Number of key/value pairs in the map. */
int mapSize( Map *m );
  
/** Return the value associated with the given key. The returned VType
    is still owned by the map.
    @param m Map to query.
    @param k Key to look for in the map.
    @return Value associated with the given key, or NULL if the key
    isn't in the map.
*/
VType *mapGet( Map *m, VType *key );

/**
 * Creates the specified key-value pair in the map. 
 * If the key already exists, replace the given key's value with new value.
 * @param m Pointer to the map.
 * @param key Key to set in the map.
 * @param value Value mapped to the given key.
 */
void mapSet( Map *m, VType *key, VType *value );

/**
 * Removes the key-value pair in the map with the given key.
 * @param m Pointer to the map.
 * @param key Key to remove from the map.
 * @return true if the key did already exist and was removed.
 *         false if the key did not already exist in the map.
 */
bool mapRemove( Map *m, VType *key );

/** Free all the memory used to store a map, including all the
    memory in its key/value pairs.
    @param m The map to free.
*/
void freeMap( Map *m );
  
#endif
