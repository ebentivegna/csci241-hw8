/*
 * Encode -- Magic, magic Huffman Encoding.
 * Authors: Elizabeth Bentivegna, Sage Jenson, Paul Buser
 * Date: April 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "encode.h"
#define ASCII_LEN 256

/* Counts characters from an input stream
 * @param frequencies: an array of 256 ints, to store the frequency counts
 * @param source: a stream to read chars from
 */
void char_count(int* frequencies, FILE* source) {
    int current_char;
    while (EOF != (current_char = fgetc(source))) {
        *(frequencies + current_char) += 1;
    }
}

/* Mallocs and returns a sorted (ascending) linked list of Nodes
 * Includes EOF character with frequency of 1
 * @param frequencies: an array of size 256 representing frequencies of each ASCII character
 * @return the head of the list
 */
Node* list_maker(int* frequencies) {

    // Add EOF with frequency 1
	Node* head = malloc(sizeof(Node));
	head->char_val = EOF;
	head->frequency = 1;
	head->left = NULL;
	head->right = NULL;
	head->next = NULL;
	//go thru frequency list and make linked list in order of frequency count
	for (int i = 0; i < ASCII_LEN; i++) {
        // Create node for the element we're adding
	    Node* new_node = malloc(sizeof(Node));
	    new_node->char_val = i;
	    new_node->frequency = frequencies[i];
	    new_node->left = NULL;
	    new_node->right = NULL;
	    new_node->next = NULL;
	    head = add_node(new_node, head);
	}
    return head;
}

Node* add_node(Node* new_node, Node* head) {
    if (new_node->frequency > head->frequency) {
	    while (NULL != head->next && new_node->frequency > head->next->frequency) {
		head = head->next;
	    }
	    new_node->next = head->next;
	    head->next = new_node;
	} else {
	    new_node->next = head;
	    head = new_node;
	}
    return head;
}



/* Prints a linked list of Nodes
 * @param head: the head of the linked list
 */
void print_list(Node* head) {
    while (NULL != head) {
//        printf("|%c: %d| --> ", head->char_val, head->frequency);
        printf("%c: %d\n", head->char_val, head->frequency);
        head = head->next;
    }
    printf("\n");
}

int main() {
    int frequencies[ASCII_LEN];
    for (int i=0; i<ASCII_LEN; i++) {
        frequencies[i] = 0;
    }
    char_count(frequencies, stdin);
    Node* sorted_list = list_maker(frequencies);
    print_list(sorted_list);
    return 0;
}

