/** 
    @file map.c
    @author
    Hash table implementation of a map.
*/

#include "map.h"
#include <stdlib.h>

#include "vtype.h"

/** Node containing a key / value pair. */
typedef struct NodeStruct {
  /** Pointer to the key part of the key / value pair. */
  VType *key;
  
  /** Pointer to the value part of the key / value pair. */
  VType *val;
  
  /** Pointer to the next node at the same element of this table. */
  struct NodeStruct *next;
} Node;

/** Representation of a hash table implementation of a map. */
struct MapStruct {
  /** Table of key / value pairs. */
  Node **table;

  /** Current length of the table. */
  int tlen;
  
  /** Current size of the map (number of different keys). */
  int size;
};

Map *makeMap( int len )
{
  Map *m = (Map *) malloc( sizeof( Map ) );
  m->size = 0;
  m->tlen = len;
  m->table = (Node **) malloc( m->tlen * sizeof( Node* ) );
  
  return m;
}

int mapSize( Map *m )
{
  return m->size;
}

/**
 * Search the map for given key and return the NODE with the given key.
 * If the key does not exist in the map, return null.
 * @param m Map to query.
 * @param key Key to look for in the map.
 * @return Node* Node associated with the given key.
 *               Null if the key does not exist in the map.
 */
static Node *mapSearch( Map *m, VType *key )
{
  //calculate the hash of the key
  int keyIndex = key->hash( key ) % m->tlen;
  //default the return value to null
  Node *returnVal = NULL;

  //loop through the probed linear list and find the node with the same key as parameter key
  for( Node *current = m->table[ keyIndex ]; current; current = current->next )
    if( key->equals( key, current->key ) )
      returnVal = current;

  return returnVal;

}

VType *mapGet( Map *m, VType *key )
{
  //find the Node in the map with the given key
  Node *keyNode = mapSearch( m, key );

  //if the node exists, return its value
  if ( keyNode )
    return keyNode->val;

  //if not, return null
  else
    return NULL;
}

/**
 * Frees all the memory used by the node n.
 * @param n the node in question.
 */
static void freeNode( Node *n )
{
  if ( n->key->print )
    n->key->destroy( n->key );
  if ( n->val->print )
    n->val->destroy( n->val );
  free( n );
}

void mapSet( Map *m, VType *key, VType *value )
{
  //first search the map for the given key
  Node *keyNode = mapSearch( m, key );

  //if the node exists, replace its value and free the old keys and values
  if( keyNode ) {
    keyNode->key->destroy( keyNode->key );
    keyNode->val->destroy( keyNode->val );
    keyNode->key = key;
    keyNode->val = value;

  //if the node does not exist, create it and add it to map
  } else {

    // //EXTRA CREDIT: resize the map if the number of entries is equal to the number of the length of the hash table
    if ( m->size == m->tlen ) {

      //the new table length is double the old one
      int newTLen = m->tlen * 2;
      
      //create a new table with double the length
      Node **newTable = malloc( newTLen * sizeof(Node *) );

      //for every linked list in the original table...
      for( int i = 0; i < m->tlen; i++ ) {

        //create a pointer to node pointer and have it point to the head of each linked list
        Node **link = malloc( sizeof(Node *) );
        *link = m->table[ i ];

        //while there are nodes in the linked list
        while( *link ) {

          //make a copy of the old node with a null next pointer
          Node *newNode = (Node *) malloc( sizeof( Node ) );
          newNode->key = (*link)->key;
          newNode->val = (*link)->val;
          newNode->next = NULL;
          
          //calcualte the new hashed index of the node's key
          int newKeyIndex = (*link)->key->hash( (*link)->key ) % newTLen;

          //add the node to the new table
          //special case: first node in linked list
          if( !newTable[ newKeyIndex ] )
            newTable[ newKeyIndex ] = newNode;

          //add node to end of linked list
          else {
            
            //get the first node in the list
            Node *current = newTable[ newKeyIndex ];

            //iterate through the list until we're at the last node in the list
            while( current->next )
              current = current->next;

            //add the new node to the list and iterate size
            current->next = newNode;

          }

          //remove the node from the old table
          Node *nextNode = (*link)->next;
          free( *link );
          *link = nextNode;
        }

        //free the space used by the linker
        free( link );
      }

      //set the old map's table to be the new map
      free( m->table );
      m->table = newTable;
      m->tlen = newTLen;
    }

    //create the new node and set its fields
    Node *newNode = (Node *) malloc( sizeof( Node ) );
    newNode->key = key;
    newNode->val = value;
    newNode->next = NULL;

    //calcualte index the key hashes to
    int keyIndex = key->hash( key ) % m->tlen;

    //special case: first node in linked list
    if ( !m->table[ keyIndex ] ) {
      m->table[ keyIndex ] = newNode;
      m->size++;

    //add node to end of linked list
    } else {

      //get the first node in the list
      Node *current = m->table[ keyIndex ];

      //iterate through the list until we're at the last node in the list
      while( current->next )
        current = current->next;

      //add the new node to the list and iterate size
      current->next = newNode;
      m->size++;

    }

  }

}

bool mapRemove( Map *m, VType *key )
{
  //search the map for the node with the given key
  Node *keyNode = mapSearch( m, key );

  //if the key does not exist in the map, return false
  if( !keyNode )
    return false;

  //if the key does exist in the map, remove it
  else {
    
    //calcualte index the key hashes to
    int keyIndex = key->hash( key ) % m->tlen;

    //special case: node to be removed is first in list
    if( key->equals( key, m->table[ keyIndex ]->key) ) {

      //store reference to old node so it can be freed from memory
      Node *oldNode = m->table[ keyIndex ];

      //remove the node from the list
      m->table[ keyIndex ] = oldNode->next;
      m->size--;

      //free the memory from the old node
      freeNode( oldNode );
    }

    //iterate through the list to find the node and remove it
    else {

      //get the first node in the list
      Node *current = m->table[ keyIndex ];

      //iterate until the NEXT node's key is the key we're looking for
      while ( !key->equals( key, current->next->key ) )
        current = current->next;

      //store reference to old node so it can be freed from memory
      Node *oldNode = current->next;

      //remove the node from the list
      current->next = oldNode->next;
      m->size--;

      //free memovry from the old node
      freeNode( oldNode );

    }

    //return true indicating that the key-value pair was removed
    return true;
  }
}

void freeMap( Map *m )
{
  //free every node in the map's hashtable
  for( int i = 0; i < m->tlen; i++ ) {

    //get the first node in the linked list
    Node *current = m->table[ i ];

    //while current is not null, remove it
    while( current ) {
      Node *nextNode = current->next;
      freeNode( current );
      current = nextNode;
    }

  }

  //free the table itself
  free( m->table );

  //finally, free the map
  free( m );
}
