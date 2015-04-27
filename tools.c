#include <stdlib.h>
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
    unsigned int mask = bit ? 0x80 : 0x00;
    bit >> buffer_index++;
    print_buffer |= bit;
    // If our buffer is full, print and empty it
    if (buffer_index >= CHAR_BIT) {
	printf("%c", (char)print_buffer);
	buffer_index = 0;
	print_buffer = 0;
    }
}

/* prints what we have in our buffer so far, padding with 0's
 */
void print_and_flush() {
    while (buffer_index) {
	print_bit(0);
    }
}
