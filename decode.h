#ifndef DECODE_H
#define DECODE_H
#include "tools.h"
#include <stdio.h>
//Gets bits individually from stream, returns 1 bit at a time
int read_bit( FILE* input );
//Reads binary stream and builds tree based on input
Node * build_tree( FILE* input );
//Some variables
int buffer_len = 0;		//amount of bits in our buffer
int buffer = 0;			//buffer to store the bits we are reading
#endif // DECODE_H
