CC = clang
CFLAGS = -Wall -Wextra -std=c99 -pedantic -O0 -g
TARGETS = encode tools.o

.PHONY = all clean

all: $(TARGETS)

encode: encode.c encode.h tools.o
	$(CC) $(CFLAGS) -o encode encode.c

tools.o: tools.c tools.h
	$(CC) $(CFLAGS) -c -o tools.o tools.c

clean:
	rm -f $(TARGETS)

