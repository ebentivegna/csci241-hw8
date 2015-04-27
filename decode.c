//decode.c


Node* build_tree(FILE* input){
    int bit = read_bit(FILE* input);
    if (bit == EOF){
	printf("%s\n", "Error: build_tree shouldn't encounter EOF");
    }
    if (bit == 1){
	char c = read_char();
	Node* node = malloc(sizeof(Node));
	node->left = NULL;
	node->right = NULL;
	node->next = NULL;
	node->char_val = c;
	return node;
    } else {
	Node* tree = malloc(sizeof(Node));
	node->left = build_tree(input);
	node->right = build_tree(input);
	return tree;
    }
}

char read_char(FILE* input){
    int c = 0;
    for (int i = 0; i < CHAR_BIT; i++){
	c = (read_bit(input) << (CHAR_BIT - i - 1))||c;
    }
    return c;
}
