#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include "tools.h"

void* my_malloc(size_t size) {
    errno = 0;
    void* ptr = malloc(size);
    if (errno != 0) {
	perror("Malloc failed!");
	exit(EXIT_FAILURE);
    } else {
	return ptr;
    }
}

/* prints a single bit
 * buffers input until it has a character, then prints
 * @param bit: either a literal 0 or 1 character
 */
void print_bit(unsigned int bit) {
    if (!(0 == bit || 1 == bit)) {
	fprintf(stderr, "Can't print bit %d\n", bit);
	exit(EXIT_FAILURE);
    }
    // Set the bit at buffer_index (counting from L -> R)
    unsigned int mask = bit ? (1 << (CHAR_BIT-1)) : 0;
    mask = mask >> buffer_index++;
    print_buffer |= mask;
    // If our buffer is full, print and empty it
    if (buffer_index >= CHAR_BIT) {
	printf("%c", (char)print_buffer);
	buffer_index = 0;
	print_buffer = 0;
    }
}

/* prints the binary representation of a character
 * @param c: the character to print
 */
void print_char(unsigned int c) {
    unsigned int mask = (1 << (CHAR_BIT - 1));
    for (int i=0; i<CHAR_BIT; i++) {
	if (c & mask) {
	    print_bit(1);
	} else {
	    print_bit(0);
	}
	mask = mask >> 1;
    }
}

/* prints what we have in our buffer so far, padding with 0's
 */
void print_and_flush() {
    while (buffer_index) {
	print_bit(0);
    }
}
