CC = gcc
CFLAGS = -Wall

FILES = src/lexer.c

build: $(FILES)
	$(CC) $(CFLAGS) -o pish $<

clean:
	rm ./yafm
