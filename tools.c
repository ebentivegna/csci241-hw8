#include <stdlib.h>
#include <stdio.h>
#include "tools.h"

void* my_malloc(size_t size) {
    errno = 0;
    void* ptr = malloc(size);
    if (errno != 0) {
	perror("Malloc failed!");
	exit(EXIT_FAILURE);
    } else {
	return ptr;
    }
}
