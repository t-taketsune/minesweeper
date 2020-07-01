CFLAGS = -Wall -ansi -ggdb
CC = gcc
CLIBS = -lncurses

default: all

all: mine

mine: minesweeper.c commands.o aux_field.o init.o
	$(CC) minesweeper.c commands.o aux_field.o init.o -o mine $(CFLAGS) $(CLIBS)

aux_field.o: aux_field.c
	$(CC) aux_field.c -c $(CFLAGS) $(CLIBS)

commands.o: commands.c
	$(CC) commands.c -c $(CFLAGS) $(CLIBS)

init.o: init.c
	$(CC) init.c -c $(CFLAGS) $(CLIBS)

run: mine
	./mine

purge:
	rm mine *.o
