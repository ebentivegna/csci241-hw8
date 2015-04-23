#ifndef NODE_H
#define NODE_H
struct Node {
    int data;
    struct Node* next;
    struct Node* left;
    struct Node* right;
};
typedef struct Node Node;
#endif // NODE_H
