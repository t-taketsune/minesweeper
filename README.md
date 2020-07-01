# minesweeper
ASCII minesweeper game written in C.

USAGE: To play the game, compile it with your preferred C compiler, and run the executable on your terminal, or use make run to compile and run it automatically. The first move is a pair of integer numbers, denoting the coordinates where you will start the game. After that, every move will be a command followed by a pair of integers. There are four commands to use: open, mark, unmk, send. Open opens that cell and the surrounding cells. If the cell is a bomb, the game is lost. Mark flags the cell as a potential bomb. Unmk removes the flag from the cell. Send is the command to check if the flags are correct, if they are, you win the game. Note that the pair of integer is still required, but totally irrelevant for the last command.

Developed using the ncurses library for windows.
