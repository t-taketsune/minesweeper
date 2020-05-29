CFLAGS = -Wall -ansi
CC = gcc

all: mine

mine: minesweeper.c
	$(CC) minesweeper.c -o mine $(CFLAGS)

run: mine
	./mine

purge:
	rm mine
