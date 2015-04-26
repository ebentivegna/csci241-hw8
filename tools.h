#ifndef TOOLS_H
#define TOOLS_H
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
#endif // TOOLS_H
