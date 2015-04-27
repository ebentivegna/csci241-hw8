/*
 * Decode -- Magic, magic Huffman decoding.
 * Authors: Elizabeth Bentivegna, Sage Jenson, Paul Buser
 * Date: April 2015
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "tools.h"
#include "decode.h"

/*
 * Reads from stream and returns one bit at a time
 */ 
int read_bit( FILE* input ) {
    
   if ( buffer_len-- > 0 ) {
       int bit;
	if (buffer & (1 << (CHAR_BIT - 1))) {
	    bit = 1;
	} else {
	    bit = 0;
	}	    
	buffer = buffer << 1;
	return bit;	

    } else {
	
	buffer = fgetc( input );
	if ( buffer == EOF ) {
	    return EOF;
	}
	
	buffer_len = CHAR_BIT;
	return read_bit( input );
    
    }
}

int main(int argc, char* argv[]) {

    FILE* input = fopen( argv[1], "r" );
    int current = 0;
    for (int i = 0; i < CHAR_BIT; i++) {
	printf("%d", read_bit(input));
    }
}
