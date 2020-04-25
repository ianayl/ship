CC = gcc
CFLAGS = -Wall

FILES = src/lexer.c

build: $(FILES)
	$(CC) $(CFLAGS) -o ship $<

clean:
	rm ship
