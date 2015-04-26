#ifndef ENCODE_H
#define ENCODE_H
#include <stdio.h>
#include "node.h"
// Reads through file and updates letter frequencies (an array of size 256) from source file.
void char_count(int* frequencies, FILE* source);
// Takes in frequencies array, and creates linked list elements;
Node* list_maker(int* frequencies);
// Prints a linked list, given its head
void print_list(Node* head);
// Converts the linked list to a tree. Returns the root node.
Node* tree_maker(Node* head);
// Add a node to a linked list (returns the new head)
Node* add_node(Node* new_node, Node* head);
#endif // ENCODE_H
