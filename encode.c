/*
 * Encode -- Magic, magic Huffman Encoding.
 * Authors: Elizabeth Bentivegna, Sage Jenson, Paul Buser
 * Date: April 2015
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "tools.h"
#include "encode.h"

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

/* my_mallocs and returns a sorted (ascending) linked list of Nodes
 * Includes EOF character with frequency of 1
 * @param frequencies: an array of size 256 representing frequencies of each ASCII character
 * @return the head of the list
 */
Node* list_maker(int* frequencies) {

    // Add EOF with frequency 1
	Node* head = my_malloc(sizeof(Node));
	head->char_val = FAKE_EOF;
	head->frequency = 1;
	head->left = NULL;
	head->right = NULL;
	head->next = NULL;
	//go thru frequency list and make linked list in order of frequency count
	for (int i = 0; i < ASCII_LEN; i++) {
        // Create node for the element we're adding
	    if (frequencies[i] > 0) {
		Node* new_node = my_malloc(sizeof(Node));
		new_node->char_val = i;
		new_node->frequency = frequencies[i];
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->next = NULL;
		head = add_node(new_node, head);
	    }
	}
    return head;
}

/* adds a node to the linked list
 * @param: new_node - the node to add
 * @param head - the head of the linked list
 * @return: the new head of the linked list
 */
Node* add_node(Node* new_node, Node* head) {
    Node* current = head;
    if (new_node->frequency > current->frequency) {
	    while (NULL != current->next && new_node->frequency > current->next->frequency) {
		current = current->next;
	    }
	    new_node->next = current->next;
	    current->next = new_node;
	} else {
	    new_node->next = head;
	    head = new_node;
	}
    return head;
}

Node* tree_maker(Node* head) {
    Node *left, *right;
    while (NULL != head->next) {
	left = head;
	right = head->next;
	Node* new_node = my_malloc(sizeof(Node));
	new_node->left = left;
	new_node->right = right;
	new_node->next = NULL;
	new_node-> char_val = 0;
	new_node-> frequency = left->frequency + right->frequency;
	head = head->next->next;
	// If head is null, our new node is the root
	if (NULL == head) {
	    return new_node;
	} else {
	    head = add_node(new_node, head);
	}
    }
    return head;
}

// Takes in a tree and returns binary representation of the tree.
void human_print_tree(Node* root) {
    if (NULL == root->left && NULL == root->right) {
	printf("1");
	printf("%d", root->char_val);
    } else {
	printf("0");
	human_print_tree(root->left);
	human_print_tree(root->right);
    }
}

/* finds code for each char recursively
 * @param keys: array of strings of size 256
 * @param head: head of the list
 * @param path: originally an empty string, records path to a node recursively
 */

void dictionary_maker(char* keys[ASCII_LEN], Node* head, char path[]){
    if (NULL != head){
	if (0 != head->char_val){
	    keys[head->char_val] = strdup(path);
	    return;
	} else {
	    strcat(path, "0");
	    dictionary_maker(keys, head->left, path);
	    *(path + strlen(path)-1) = '1';
	    dictionary_maker(keys, head->right, path);
	    *(path + strlen(path)-1) = '\0';
	    
	}
    }
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

int main(int argc, char* argv[]) {
    int frequencies[ASCII_LEN];
    char* keys[ASCII_LEN];
    char path[ASCII_LEN];
    FILE *input, *output;

    if (2 != argc && 3 != argc) {
	printf("usage: %s: <filename> [output]\n", argv[0]);
	exit(EXIT_FAILURE);
    }
    errno = 0;
    input = fopen(argv[1], "r");
    if (errno) {
	perror("Couldn't open file for reading\n");
	exit(EXIT_FAILURE);
    }
    if (3 == argc) {
	errno = 0;
	output = fopen(argv[2], "w");
	if (errno) {
	    perror("Couldn't open file for writing\n");
	    exit(EXIT_FAILURE);
	}
    } else {
	output = stdout;
    }

    for (int i=0; i < ASCII_LEN + 1; i++){
	keys[i] = NULL;
    }
    for (int i=0; i<ASCII_LEN; i++) {
        frequencies[i] = 0;
    }
    char_count(frequencies, input);
    Node* sorted_list = list_maker(frequencies);
    Node* tree = tree_maker(sorted_list);
    dictionary_maker(keys, tree, path);
//    for (int i=0; i < ASCII_LEN; i++){
//	if (keys[i]) printf("%d %s\n", i, *(keys+i));
//    }
    // print out tree
    print_tree(tree, output);
    // print EOF
    print_str(keys[FAKE_EOF], output);
    rewind(input);
    int current_char;
    while (EOF != (current_char = fgetc(input))) {
	print_str(keys[current_char], output);
    }
    print_str(keys[FAKE_EOF], output);
    print_and_flush(output);
}
