/**
 * @file input.c
 * @author Yousif Mansour yamansou
 * @date 2022-04-18
 * 
 * This component handles most input used for maintaining the map.
 * Its main responsibility is to read a single line from a given input and return it. 
 * 
 */
#include "input.h"
#include <string.h>

void static ensureCapacity( void** list, int* capacity, int count, size_t sizeOfElement )
{
    if( count == *capacity - 1 )  {
        *capacity *= 2;
        *list = realloc( *list, *capacity * sizeOfElement );
    }
}

char *readLine( FILE *fp )
{
    //get the first character and check if there is no more input to be read
    char ch = getc( fp );
    if ( ch == EOF ) 
        return NULL;

    //dynamically allocate the string and add the first character
    char *line = malloc( INITIAL_CAPACITY * sizeof(char *) );
    line[ 0 ] = ch;

    //initialze line's character count and capacity count
    int lineCount = 1;
    int lineCapacity = INITIAL_CAPACITY;

    //while the input is not a new-line character or end of file
    while ( ( ch = getc( fp ) ) != LINE_FEED && ch != EOF ) {
        
        //ensure that capacity is correct
        ensureCapacity( (void**) &line, &lineCapacity, lineCount, sizeof(char *) );

        //add character at the correct spot
        line[ lineCount++ ] = ch;

    }
    
    //add a null terminator and return the string
    line[ lineCount++ ] = NULL_TERMINATOR;
    return line;
}
