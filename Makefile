CC = gccx
CFLAGS = -Wall -Wextra -std=c99 -pedantic -O0 -g
TARGETS = encode tools.o

.PHONY = all clean

all: $(TARGETS)

encode: encode.c encode.h tools.o
	$(CC) $(CFLAGS) -o encode tools.o encode.c

tools.o: tools.c tools.h
	$(CC) $(CFLAGS) -c tools.c

clean:
	rm -f $(TARGETS)

