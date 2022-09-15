/** 
    @file text.h
    @author Yousif Mansour yamansou
    Header for the Text subclass of VType
*/

#include "vtype.h"

/** Subclass of VType for storing integers. */
typedef struct {
  /** Inherited from VType */
  void (*print)( struct VTypeStruct const *v );

  /** Inherited from VType */
  bool (*equals)( struct VTypeStruct const *a,
                  struct VTypeStruct const *b );

  /** Inherited from VType */
  unsigned int (*hash)( struct VTypeStruct const *b );

  /** Inherited from VType */
  void (*destroy)( struct VTypeStruct *v );

  /** string stored by this text. */
  char *str;
} Text;

/**
 * Make an instance of Text holding the text parsed from the init string.
 * @param init String countaining the initialization value as text.
 * @param n Optional return for the number of characters used from init.
 * @return VType* pointer to the new VType instance
 */
VType *parseText( char const *init, int *n );
