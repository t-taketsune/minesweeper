#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include <math.h>
#include <string.h>

#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define UNKNOWN 'X'
#define MARKED 'O'
#define OPEN ' '
#define INVALID -1
#define EMPTY 0
#define BOMB 10
#define SIZE 20

#define BOX_GAPS 4
#define INFO_WIDTH 40
#define INPUT_HEIGHT 3

static const char open_cmd[] = "open";
static const char mark_cmd[] = "mark";
static const char unmk_cmd[] = "unmk";
static const char send_cmd[] = "send";
static const char quit_cmd[] = "quit";
static const char info_display[] = "Available commands:\n"
    "open: opens the content inside a cell.\n"
    "mark: flags a cell as a potential bomb.\n"
    "unmk: removes the flag from previously marked cell.\n"
    "send: checks if all bombs are marked, which is the winning condition.\n"
    "quit: exits the game.\n";

typedef struct {
    int real;
    char shown;
} cell;

typedef struct {
    int x, y;
} coor;

typedef struct {
    int row, col, n_bombs;
    cell** field;
    coor* bomb_coords;
    WINDOW* out_win, *game_win, *input_win, *info_win;
    int input_j, input_i, info_j, info_i;
} field;

#endif
