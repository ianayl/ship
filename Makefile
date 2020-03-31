CC = gcc
CFLAGS = -Wall

FILES = src/main.c

build: $(FILES)
	$(CC) $(CFLAGS) -o pish $<

clean:
	rm ./yafm
