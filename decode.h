#ifndef DECODE_H
#define DECODE_H
#include "tools.h"
#include <stdio.h>
//Gets bits individually from stream, returns 1 bit at a time
unsigned int read_bit( FILE* input );
//Reads binary stream and builds tree based on input
Node * build_tree( FILE* input );
#endif // DECODE_H
