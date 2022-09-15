// Simple test program for the text component.

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vtype.h"
#include "map.h"
#include "integer.h"

int main()
{
  // // Make a few values we use below.

  VType *v1 = parseInteger( "1", NULL );
  VType *v2 = parseInteger( "2", NULL );
  VType *v3 = parseInteger( "3", NULL );
  VType *v4 = parseInteger( "4", NULL );
  VType *v5 = parseInteger( "5", NULL );
  VType *v6 = parseInteger( "6", NULL );
  VType *v7 = parseInteger( "7", NULL );
  VType *v8 = parseInteger( "8", NULL );

  //specifically test resizing map
  Map *map = makeMap( 2 );
  mapSet( map, v1, v2 );
  mapSet( map, v3, v4 );
  mapSet( map, v5, v6 );
  mapSet( map, v7, v8 );
  assert( mapSize( map ) == 4 );
  assert( v1->equals( v2, mapGet( map, v1 ) ) );
  
  
  // VType *v5 = parseInteger( "5", NULL );
  // VType *v10 = parseInteger( "10", NULL );
  // VType *v15 = parseInteger( "15", NULL );
  // VType *v20 = parseInteger( "20", NULL );
  
  // // Make a map with 3 slots in its hash table.
  // Map *map = makeMap( 3 );
  // assert( mapSize( map ) == 0 );

  // // Put a the entry 5 -> 10 in the map.
  // mapSet( map, parseInteger( "5", NULL ), parseInteger( "10", NULL ) );
  // assert( mapSize( map ) == 1 );
  // VType *v = mapGet( map, v5 );
  // assert( v10->equals( v10, v ) );
  
  // // Put a second entry, 10 -> 15 in the map.
  // mapSet( map, parseInteger( "10", NULL ), parseInteger( "15", NULL ) );
  // assert( mapSize( map ) == 2 );
  // v = mapGet( map, v10 );
  // assert( v15->equals( v15, v ) );

  // // Check the key / value that was previously there.
  // v = mapGet( map, v5 );
  // assert( v10->equals( v10, v ) );

  // // Change the value for key 5. to 5 -> 20
  // mapSet( map, parseInteger( "5", NULL ), parseInteger( "20", NULL ) );
  // assert( mapSize( map ) == 2 );
  // v = mapGet( map, v5 );
  // assert( v20->equals( v20, v ) );
  
  // // Remove the value for key 10.
  // assert( mapRemove( map, v10 ) );
  // assert( mapSize( map ) == 1 );

  // // Make sure that value is gone.
  // v = mapGet( map, v10 );
  // assert( v == NULL );
  
  // // Try to remove a value that's not there.
  // assert( mapRemove( map, v10 ) == false );
  // assert( mapSize( map ) == 1 );
  
  // // Free our maps.
  // freeMap( map );

  // // Free our temporary values.
  // v5->destroy( v5 );
  // v10->destroy( v10 );
  // v15->destroy( v15 );
  // v20->destroy( v20 );

  return EXIT_SUCCESS;
}
