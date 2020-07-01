#include "init.h"

void init_field(field* f) {
    int i, j;
    for (i=0; i!=f->row; i++) {
        f->field[i][0].real = INVALID;
        f->field[0][i].real = INVALID;
        f->field[i][f->col-1].real = INVALID;
        f->field[f->row-1][i].real = INVALID;
    }
    for (i=1; i!=f->row-1; i++)
        for (j=1; j!=f->col-1; j++) {
            f->field[i][j].real = EMPTY;
            f->field[i][j].shown = UNKNOWN;
        }
}

void init_game(field* f) {
    /* Creating field. */
    initscr();
    waddstr(stdscr, "Inform the desired field size and number of bombs. (rows -- min 5 / max 99, cols -- min 5 / max 99, bombs -- min 3 / as many as possible).\n");
    int max_i, max_j, check=0;
    getmaxyx(stdscr, max_i, max_j);
    while (!check) {
        wscanw(stdscr, "%d %d %d", &f->row, &f->col, &f->n_bombs);
        if (max_i < (f->row + INPUT_HEIGHT + BOX_GAPS) || max_j < ((f->col*2) + INFO_WIDTH + BOX_GAPS)) {
            waddstr(stdscr, "Terminal is too small.\n");
        } else if (f->row < 5) {
            waddstr(stdscr, "Too few rows.\n");
        } else if (f->col < 5) {
            waddstr(stdscr, "Too few columns.\n");
        } else if (f->n_bombs < 3) {
            waddstr(stdscr, "Too few bombs.\n");
        } else if (f->n_bombs >= f->row*f->col-9) {
            waddstr(stdscr, "Too many bombs!\n");
        } else {
            check = 1;
        }
    }
    f->out_win = newwin(max_i, max_j, 0, 0);
    int j_offset = (max_j - (f->col*2) - 3 - INFO_WIDTH)/2, i_offset = (max_i - f->row - 2 - INPUT_HEIGHT)/2;
    f->input_i = i_offset + f->row + 3;
    f->input_j = j_offset;
    f->info_i = i_offset;
    f->info_j = j_offset + f->col*2 + 5;
    f->game_win = newwin(f->row+3, (f->col*2)+5, i_offset, j_offset);
    f->input_win = newwin(INPUT_HEIGHT, f->col*2 + INFO_WIDTH + 5, f->input_i, f->input_j);
    f->info_win = newwin(f->row+3, INFO_WIDTH, f->info_i, f->info_j);

    f->row+=2;
    f->col+=2;
    if (!alloc_field(f)) {
        waddstr(stdscr, "Could not allocate memory for the game. Aborting.\n");
        destroy_field(f);
        exit(0);
    }

    /* Initializing values. */
    init_field(f);
    /* Printing field. Taking first open cell.*/
    waddstr(stdscr, "Inform the position to start the game. (row, col)\n");
    int start_i, start_j;
    wscanw(stdscr, "%d %d", &start_i, &start_j);
    while(!valid_pos(start_i, start_j, f->row-1, f->col-1)) {
        printw("\nInvalid position.\n", stdscr);
        wscanw(stdscr, "%d %d", &start_i, &start_j);
    }
    /* Spreading bombs. */
    spread_bombs(f, start_i, start_j);
    /* Opening field. */
    open_field(f, start_i, start_j);
}
