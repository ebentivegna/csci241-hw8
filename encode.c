/*
 * Encode -- Magic, magic Huffman Encoding.
 * Authors: Elizabeth Bentivegna, Sage Jenson, Paul Buser
 * Date: April 2015
 */

#include <stdio.h>
#include <stdlib.h>
#define ASCII_LEN 256

void char_count(int* frequencies, FILE* source) {
    int current_char;
    while (EOF != (current_char = fgetc(source))) {
        *(frequencies + current_char) += 1;
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

