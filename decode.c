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
Node* build_tree(FILE* input){
    int bit = read_bit(input);
    if (bit == EOF){
	printf("%s\n", "Error: build_tree shouldn't encounter EOF");
    }
    if (bit == 1){
	char c = read_char(input);
	Node* node = my_malloc(sizeof(Node));
	node->left = NULL;
	node->right = NULL;
	node->next = NULL;
	node->char_val = c;
	return node;
    } else {
	Node* tree = my_malloc(sizeof(Node));
	tree->left = build_tree(input);
	tree->right = build_tree(input);
	return tree;
    }
}

char read_char(FILE* input){
    int c = 0;
    for (int i = 0; i < CHAR_BIT; i++){
	int bit = read_bit(input);
	bit = bit << (CHAR_BIT - i - 1);
	c |= bit;
    }
    return c;
}

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

int is_leaf(Node* node) {
    if (NULL == node->left && NULL == node->right)
	return 1;
    else
	return 0;
}

int read_char_in_tree(FILE* input, Node* root) {
    Node* cur_node = root;
    int bit;
    while (!is_leaf(cur_node)) {
	bit = read_bit(input);
	if (0 == bit) {
	    cur_node = cur_node->left;
	} else {
	    cur_node = cur_node->right;
	}
    }
    return cur_node->char_val;
}

int main(int argc, char* argv[]) {
    FILE* input = fopen(argv[1], "r");
    Node* root = build_tree(input);
    int our_eof = read_char_in_tree(input, root);
    while (1) {
	int cur_char = read_char_in_tree(input, root);
	if (our_eof == cur_char)
	    exit(EXIT_SUCCESS);
	printf("%c", cur_char);
    }
}
