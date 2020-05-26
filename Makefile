CC = gcc
CFLAGS = -Wall -g

FILES = src/parser/lexer.c src/parser/TokenArr.c src/parser/TokenArr.h

build: $(FILES)
	$(CC) $(CFLAGS) -o ship $^

clean:
	rm ship
