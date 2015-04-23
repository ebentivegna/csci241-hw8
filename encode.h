#ifndef ENCODE_H
#define ENCODE_H
#include <stdio.h>
// Reads through file and updates letter frequencies (an array of size 256) from source file.
void char_count(int* frequencies, FILE* source);
#endif // ENCODE_H
