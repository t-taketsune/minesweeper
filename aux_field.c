#include "aux_field.h"

int valid_pos(int i, int j, int row, int col) {
    return (i>=0 && i<col && j>=0 && j<col) ? 1 : 0;
}

int aux_fill_check(int value) {
    return (value == INVALID) ? 0 : 1;
}

void aux_fill(cell** field, int i, int j) {
    field[i-1][j-1].real += aux_fill_check(field[i-1][j-1].real);
    field[i][j-1].real += aux_fill_check(field[i][j-1].real);
    field[i+1][j-1].real += aux_fill_check(field[i+1][j-1].real);
    field[i-1][j+1].real += aux_fill_check(field[i-1][j+1].real);
    field[i][j+1].real += aux_fill_check(field[i][j+1].real);
    field[i+1][j+1].real += aux_fill_check(field[i+1][j+1].real);
    field[i-1][j].real += aux_fill_check(field[i-1][j].real);
    field[i+1][j].real += aux_fill_check(field[i+1][j].real);
}

char int_to_char(int x) {
    return (char) (x + 48);
}

int near_start(int i, int j, int s_i, int s_j) {
    if ((i >= s_i - 1 && i <= s_i + 1) || (j >= s_j - 1 && j <= s_j + 1))
        return 1;
    return 0;
}

int alloc_field(field* f) {
    f->bomb_coords = malloc(sizeof(coor)*f->n_bombs);
    if (!f->bomb_coords)
        return 0;
    f->field = malloc(sizeof(cell*)*f->row);
    if (!f->field)
        return 0;
    int aux;
    for (aux=0; aux!=f->row; aux++) {
        f->field[aux] = malloc(sizeof(cell)*f->col);
        if (!f->field)
            return 0;
    }
    return 1;
}

void destroy_field(field* f) {
    free(f->bomb_coords);
    int i;
    for (i=0; i!=f->row; i++) {
        free(f->field[i]);
    }
    free(f->field);
}

void print_full(field* f) {
    mvaddstr(f->info_i+1, f->info_j+(INFO_WIDTH/2)-14, "***  ASCII  MINESWEEPER  ***");
    mvaddstr(f->info_i+3, f->info_j+(INFO_WIDTH/2)-18, "-------  Available commands  -------");
    mvaddstr(f->info_i+5, f->info_j+2, "open: opens a cell");
    mvaddstr(f->info_i+6, f->info_j+2, "  + open <row> <col>");
    mvaddstr(f->info_i+8, f->info_j+2, "mark: flags a cell as a bomb");
    mvaddstr(f->info_i+9, f->info_j+2, "  + mark <row> <col>");
    mvaddstr(f->info_i+11, f->info_j+2, "unmk: removes the cell's flag");
    mvaddstr(f->info_i+12, f->info_j+2, "  + unmk <row> <col>");
    mvaddstr(f->info_i+14, f->info_j+2, "send: checks if flags are correct");
    mvaddstr(f->info_i+16, f->info_j+2, "quit: exits the game");
}

void print_mid(field* f) {
    mvaddstr(f->info_i+1, f->info_j+2, "open: opens a cell");
    mvaddstr(f->info_i+2, f->info_j+2, "  + open <row> <col>");
    mvaddstr(f->info_i+3, f->info_j+2, "mark: flags a cell as a bomb");
    mvaddstr(f->info_i+4, f->info_j+2, "  + mark <row> <col>");
    mvaddstr(f->info_i+5, f->info_j+2, "unmk: removes the cell's flag");
    mvaddstr(f->info_i+6, f->info_j+2, "  + unmk <row> <col>");
    mvaddstr(f->info_i+7, f->info_j+2, "send: checks if flags are correct");
    mvaddstr(f->info_i+8, f->info_j+2, "quit: exits the game");
}

void print_mini(field* f) {
    mvaddstr(f->info_i+1, f->info_j+2, "open: opens a cell");
    mvaddstr(f->info_i+2, f->info_j+2, "mark: flags a cell as a bomb");
    mvaddstr(f->info_i+3, f->info_j+2, "unmk: removes the cell's flag");
    mvaddstr(f->info_i+4, f->info_j+2, "send: checks if flags are correct");
    mvaddstr(f->info_i+5, f->info_j+2, "quit: exits the game");
}

void print_field(field* f) {
    box(f->out_win, 0, 0);
    box(f->game_win, 0, 0);
    box(f->info_win, 0, 0);
    box(f->input_win, 0, 0);
    curscr = f->out_win;
    wrefresh(f->out_win);
    int i, j;
    for (i=0; i<f->col; i+=5) {
        mvwprintw(f->game_win, 1, (i*2)+1, "%02d", i);
    }
    for (i=1; i!=f->row; i++) {
        if (i%5==0) {
            mvwprintw(f->game_win, i+1, 1, "%02d ", i);
        }
        for (j=1; j!=f->col; j++) {
            mvwprintw(f->game_win, i+1, (j*2) + 2, "%c ", f->field[i][j].shown);
        }
    }
    curscr = f->game_win;
    wrefresh(f->game_win);
    if (f->row <= 8) {
        print_mini(f);
    } else if (f->row <= 16) {
        print_mid(f);
    } else {
        print_full(f);
    }
    curscr = f->info_win;
    wrefresh(f->info_win);
    curscr = f->input_win;
    move(f->input_i + 1, f->input_j + 1);
    wrefresh(f->input_win);
}

void spread_bombs(field* f, int start_i, int start_j) {
    srand(time(NULL));
    int aux=0, i, j;
    while (aux!=f->n_bombs) {
        i = (rand()%(f->row-2))+1;
        j = (rand()%(f->col-2))+1;
        if (f->field[i][j].real != BOMB && !near_start(i, j, start_i, start_j)) {
            f->field[i][j].real = BOMB;
            aux_fill(f->field, i, j);
            f->bomb_coords[aux].x = i;
            f->bomb_coords[aux].y = j;
            aux++;
        }
    }
}

void open_field(field* f, int i, int j) {
    if (f->field[i][j].real == INVALID || f->field[i][j].shown == OPEN || f->field[i][j].shown == f->field[i][j].real || f->field[i][j].shown == MARKED) {
        return;
    }
    if (f->field[i][j].real != EMPTY) {
        f->field[i][j].shown = int_to_char(f->field[i][j].real);
        return;
    }
    f->field[i][j].shown = OPEN;
    open_field(f, i + 1, j);
    open_field(f, i - 1, j);
    open_field(f, i, j + 1);
    open_field(f, i, j - 1);
}
