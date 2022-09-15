/**
 * @file text.c
 * @author Youtsif Mansour yamansou
 * Implementation of the Text VType.
 */

#include "text.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// print method for Text.
static void print( VType const *v )
{
    // Convert the VType pointer to a more specific type then print.
    Text const *this = (Text const *) v;
    printf( "\"%s\"", this->str );
}

// equals method for Text.
static bool equals( VType const *a, VType const *b )
{
    // Make sure the b object is also a Text.
    // (i.e., it uses the same print funtion)
    if ( b->print != print )
        return false;

    // Extract the string from each of these Texts.
    char *this = ( (Text const *) a )->str;
    char *that = ( (Text const *) b )->str;

    return strcmp( this, that ) == 0;
}

// hash method for Text. Hashes the characters in the string using 
// the Jenkins 32-bit hash function. 
static unsigned int hash( VType const *v )
{
    //Convert the VType pointer specifically to Text
    Text const *this = (Text const *) v;

    //Get the string from this and its length
    char *str = this->str;
    int len = strlen( str );

    // Jenkins 32-bit hash function implementation
    unsigned int i = 0;
    unsigned int hash = 0;
    while ( i != len ) {
        hash += str[ i++ ];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

// destroy method for Text.
static void destroy( VType *v )
{
    //Convert the VType pointer specifically to Text
    Text const *this = (Text const *) v;

    //free its memory allocated string
    free( this->str );
    
    free( v );
}

VType *parseText( char const *init, int *n )
{
    //get the length of the initialization string
    int len = strlen( init );

    //find the indices of the two quotation marks
    int firstQuoteIndex = -1;
    int secondQuoteIndex = -1;
    for( int i = 0; i < len; i++ ) {
        if ( init[ i ] == '"' ) {
            if ( firstQuoteIndex < 0 )
                firstQuoteIndex = i;
            else if( init[ i - 1 ] != '\\' ){
                secondQuoteIndex = i;
                break;
            }
        }
    }

    //if both quotations weren't found, init is invalid
    if( firstQuoteIndex < 0 || secondQuoteIndex < 0 )
        return NULL;

    //make sure that all text before before the first quote is whitespace
    for( int i = 0; i < firstQuoteIndex; i++ ) 
        if( !isspace( init[ i ] ) )
            return NULL;

    int newStrLen = secondQuoteIndex - firstQuoteIndex - 1;

    //Allocate a Text and allocate its string field to 
    //exactly fit all the characters and a null terminator without the quotes
    Text *this = (Text *) malloc( sizeof( Text ) );
    this->str = (char *) malloc( ( newStrLen + 1 ) * sizeof( char ) );

    //copy the characters from the init string, 
    //skipping the quotes and checking for invalid chars
    int wordLen = 0;
    for( int i = 0; i < newStrLen; i++ ) {

        //properly offset the init index accounting for all quotes
        int initIndex = firstQuoteIndex + 1 + i;

        //check for excape sequences
        if( init[ initIndex ] == '\\' ) {

            switch( init[ initIndex + 1 ] ) {
            case 'n':
                this->str[ wordLen++ ] = '\n';
                i++;
                break;
            case 't':
                this->str[ wordLen++ ] = '\t';
                i++;
                break;
            case '\\':
                this->str[ wordLen++ ] = '\\';
                i++;
                break;
            case '"':
                if ( initIndex + 1 == secondQuoteIndex )
                    return NULL;
                this->str[ wordLen++ ] = '"';
                i++;
                break;
            }
            
        } else {

            //check for invalid linefeed
            if( init[ initIndex ] == '\n' )
                return NULL;

            //copy this valid character into the new Text struct
            this->str[ wordLen++ ] = init[ initIndex ];

        }
    }

    //add a null terminator to the Text string
    this->str[ wordLen ] = '\0';

    //fill the rest of the Text fields
    this->print = print;
    this->equals = equals;
    this->hash = hash;
    this->destroy = destroy;

    // Fill in the length pointer if the caller asked for it
    if( n )
        *n = secondQuoteIndex + 1;

    //return the Text as a pointer to its superclass
    return (VType *) this;
}