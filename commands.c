#include "commands.h"

void open(field* f, int i, int j, int *end) {
    if (f->field[i][j].real == BOMB) {
        printw("You have lost the game.\n", f->info_win);
        *end = 1;
        return;
    }
    open_field(f, i, j);
    print_field(f);
}

void mark(field* f, int i, int j, int *n_marks) {
    if (f->field[i][j].shown == MARKED) {
        printw("This cell is already marked.\n", f->info_win);
        return;
    }
    f->field[i][j].shown = MARKED;
    (*n_marks)++;
    print_field(f);
}

void unmark(field* f, int i, int j, int *n_marks) {
    if (f->field[i][j].shown != MARKED) {
        printw("This cell is not marked.\n", f->info_win);
        return;
    }
    f->field[i][j].shown = UNKNOWN;
    (*n_marks)--;
    print_field(f);
}

void send(field* f, int n_marks, int *end) {
    if (n_marks != f->n_bombs) {
        printw("Your number of marks is not equal to the number of bombs. Recheck.", f->info_win);
        return;
    }
    int aux;
    for (aux=0; aux!=f->n_bombs; aux++)
        if (f->field[f->bomb_coords[aux].x][f->bomb_coords[aux].y].shown != MARKED) {
            printw("Your marks are not correct. Recheck.", f->info_win);
            return;
        }
    printw("You have won!\n", f->info_win);
    *end = 1;
    return;
}

void quit(field* f) {
    endwin();
    destroy_field(f);
    exit(0);
}
