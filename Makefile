CFLAGS = -Wall -ansi -ggdb
CC = gcc
CLIBS = -lncurses

default: all

all: mine

mine: minesweeper.c commands aux init
	$(CC) minesweeper.c commands.o aux_field.o init.o -o mine $(CFLAGS) $(CLIBS)

aux: aux_field.c
	$(CC) aux_field.c -c $(CFLAGS) $(CLIBS)

commands: commands.c
	$(CC) commands.c -c $(CFLAGS) $(CLIBS)

init: init.c
	$(CC) init.c -c $(CFLAGS) $(CLIBS)

run: mine
	./mine

purge:
	rm mine *.o
