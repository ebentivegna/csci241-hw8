/*
 * Encode -- Magic, magic Huffman Encoding.
 * Authors: Elizabeth Bentivegna, Sage Jenson, Paul Buser
 * Date: April 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#define ASCII_LEN 256

void char_count(int* frequencies, FILE* source) {
    int current_char;
    while (EOF != (current_char = fgetc(source))) {
        *(frequencies + current_char) += 1;
    }
}

Node* list_maker(int* frequencies) {

	//go thru frequency list and make linked list in order of frequency count
	Node* current;
	Node* head = malloc(sizeof(Node));
	*head = { .char_val = 0, .frequency = frequencies[0], .left = NULL, .right = NULL, .next = NULL };
	for (int i = 1; i < ASCII_LEN; i++) {
		
		Node* new_node = malloc(sizeof(Node));
		*new_node = { .char_val = i, .frequency = frequencies[i], .left = NULL, .right = NULL, .next = NULL };
		current = head;		

		while (new_node->frequency > current->frequency) {
			
			if (current->next != NULL){
				current = current->next;
			}
			else {
				break;
			}
			
		}
		
	}
		
		

}


int main() {
    int frequencies[ASCII_LEN];
    for (int i=0; i<ASCII_LEN; i++) {
        frequencies[i] = 0;
    }
    char_count(frequencies, stdin);
    for (int i = 0; i < ASCII_LEN; i++) {
        printf("%c: %d\n", i, frequencies[i]);
    }
    return 0;
}

