CC = gcc
CFLAGS = -Wall -g

FILES = src/parser/lexer.c src/parser/tokens.c src/parser/tokens.h

build: $(FILES)
	$(CC) $(CFLAGS) -o ship $^

clean:
	rm ship
