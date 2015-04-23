CC = clang
CFLAGS = -Wall -Wextra -std=c99 -pedantic -O0 -g
TARGETS = encode

.PHONY = all clean

all: $(TARGETS)


encode: encode.c encode.h
	$(CC) $(CFLAGS) -c encode.c -o encode

clean:
	rm -f $(TARGETS)

