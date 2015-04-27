#ifndef TOOLS_H
#define TOOLS_H
#define ASCII_LEN 256
#define FAKE_EOF (ASCII_LEN - 1)
struct Node {
    int char_val;
    int frequency;
    struct Node* next;
    struct Node* left;
    struct Node* right;
};
typedef struct Node Node;
// Extra special error-checkin' malloc for the masses!
void* my_malloc(size_t size);
// buffer that holds bits until we have at least 8
unsigned int print_buffer;
// the number of characters we have stored so far in our buffer
int buffer_index;
// Prints bits using our buffer
void print_bit(unsigned int bit);
void print_and_flush();
void print_char(unsigned int c);
void print_str(const char* str);
// Prints the binary representation of a tree
void print_tree(Node* root);
#endif // TOOLS_H
