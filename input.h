/**
 * @file input.h TEST
 * @author Yousif Mansour yamansou
 * @date 2022-04-18
 * 
 * This component handles most input used for maintaining the map.
 * Its main responsibility is to read a single line from a given input and return it. 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/** Initial capacity of a dynamically-sized string */
#define INITIAL_CAPACITY 10

/** Line-feed character */
#define LINE_FEED '\n'

/** String null terminator */
#define NULL_TERMINATOR '\0'

/**
 * Read a single line of text from the File fp and 
 * return it as a string. Returns null if there is no
 * more input to read.
 * 
 * @param fp File pointer to read from
 * @return char* String read from input
 */
char *readLine( FILE *fp );
