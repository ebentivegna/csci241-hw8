#include <stdlib.h>
#include <string.h>
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
void print_bit(unsigned int bit, FILE* output) {
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
	fprintf(output, "%c", (char)print_buffer);
	buffer_index = 0;
	print_buffer = 0;
    }
}

/* prints the binary representation of a character
 * @param c: the character to print
 */
void print_char(unsigned int c, FILE* output) {
    unsigned int mask = (1 << (CHAR_BIT - 1));
    for (int i=0; i<CHAR_BIT; i++) {
	if (c & mask) {
	    print_bit(1, output);
	} else {
	    print_bit(0, output);
	}
	mask = mask >> 1;
    }
}

/* prints the bits of a string of binary characters
 * @param str: the binary string to print
 */
void print_str(const char* str, FILE* output) {
    for (unsigned long i=0; i < strlen(str); i++) {
	if ('0' == *(str + i)) {
	    print_bit(0, output);
	} else if ('1' == *(str + i)) {
	    print_bit(1, output);
	} else {
	    fprintf(stderr, "string %s has non-binary characters!\n", str);
	    exit(EXIT_FAILURE);
	}
    }
}

/* prints what we have in our buffer so far, padding with 0's
 */
void print_and_flush(FILE* output) {
    while (buffer_index) {
	print_bit(0, output);
    }
}

// Takes in a tree and returns binary representation of the tree.
void print_tree(Node* root, FILE* output) {
    if (NULL == root->left && NULL == root->right) {
	print_bit(1, output);
	print_char(root->char_val, output);
    } else {
	print_bit(0, output);
	print_tree(root->left, output);
	print_tree(root->right, output);
    }
}

int is_leaf(Node* node) {
    if (NULL == node->left && NULL == node->right)
	return 1;
    else
	return 0;
}

void free_tree(Node* root) {
    if (is_leaf(root)) {
	free(root);
	return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
