#ifndef ENCODE_H
#define ENCODE_H
#include <stdio.h>
#include "node.h"
// Reads through file and updates letter frequencies (an array of size 256) from source file.
void char_count(int* frequencies, FILE* source);
// Takes in frequencies array, and creates linked list elements;
Node* list_maker(int* frequencies);
#endif // ENCODE_H
