#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define UNKNOWN 'X'
#define MARKED 'O'
#define OPEN ' '
#define INVALID -1
#define EMPTY 0
#define BOMB 10
#define SIZE 20
#define NUMBER_OF_BOMBS 20

static const char open_cmd[] = "open";
static const char mark_cmd[] = "mark";
static const char unmk_cmd[] = "unmk";
static const char send_cmd[] = "send";
static const char help_cmd[] = "help";
static const char quit_cmd[] = "quit";

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
} field;

/* CELL AUXILIARY FUNCTIONS */
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

/* FIELD ALLOCATION FUNCTIONS */
int alloc_field(field* f) {
    f->bomb_coords = malloc(sizeof(coor)*f->n_bombs);
    if (!f->bomb_coords)
        return 0;
    f->field = malloc(sizeof(cell*)*f->col);
    if (!f->field)
        return 0;
    int aux;
    for (aux=0; aux!=f->col; aux++) {
        f->field[aux] = malloc(sizeof(cell)*f->row);
        if (!f->field)
            return 0;
    }
    return 1;
}

void destroy_field(field* f) {
    free(f->bomb_coords);
    int i, j;
    for (i=0; i!=f->row; i++) {
        for (j=0; j!=f->col; j++)
            free(&f->field[i][j]);
        free(&f->field[i]);
    }
}

/* FIELD INITIALIZATION FUNCTIONS */
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

void spread_bombs(field* f, int start_i, int start_j) {
    srand(time(NULL));
    int aux=0, i, j;
    while (aux!=f->n_bombs) {
        i = (rand()%(f->row-2))+1;
        j = (rand()%(f->col-2))+1;
        if (f->field[i][j].real == EMPTY && !near_start(i, j, start_i, start_j)) {
            f->field[i][j].real = BOMB;
            aux_fill(f->field, i, j);
            f->bomb_coords[aux].x = i;
            f->bomb_coords[aux].y = j;
            aux++;
        }
    }
}

/* FIELD AUXILIARY FUNCTIONS */
void print_field(field* f) {
    printf("\n  01");
    int aux, i, j;
    for (aux=2; aux!=f->col-1; aux++) {
        if (aux%5 == 0) {
            printf("%02d", aux);
        } else if (aux+1%5 != 0) {
            printf("  ");
        }
    }
    printf("\n01 ");
    for (aux=1; aux!=f->row-1; aux++)
        printf("%c ", f->field[1][aux].shown);
    printf("\n");
    for (i=2; i!=f->row-1; i++) {
        if (i%5 == 0) {
            printf("%02d ", i);
        } else {
            printf("   ");
        }
        for (j=1; j!=f->col-1; j++)
            printf("%c ", f->field[i][j].shown);
        printf("\n");
    }
}

void open_field(field* f, int i, int j) {
    if (f->field[i][j].real == INVALID || f->field[i][j].shown == f->field[i][j].real || f->field[i][j].shown == MARKED) {
        return;
    }
    if (f->field[i][j].real != EMPTY) {
        f->field[i][j].shown = int_to_char(f->field[i][j].real);
        return;
    }
    f->field[i][j].shown = f->field[i][j].real;
    open_field(f, i + 1, j);
    open_field(f, i - 1, j);
    open_field(f, i, j + 1);
    open_field(f, i, j - 1);
}

/* FIELD COMMAND FUNCTIONS */
void open(field* f, int *end) {
    int i, j;
    scanf("%d %d", &i, &j);
    if (f->field[i][j].real == BOMB) {
        printf("You have lost the game.\n");
        *end = 1;
        return;
    }
    open_field(f, i, j);
    print_field(f);
}

void mark(field* f, int *n_marks) {
    int i, j;
    scanf("%d %d", &i, &j);
    if (f->field[i][j].shown == MARKED) {
        printf("This cell is already marked.\n");
        return;
    }
    f->field[i][j].shown = MARKED;
    (*n_marks)++;
    print_field(f);
}

void unmark(field* f, int *n_marks) {
    int i, j;
    scanf("%d %d", &i, &j);
    if (f->field[i][j].shown != MARKED) {
        printf("This cell is not marked.\n");
        return;
    }
    f->field[i][j].shown = UNKNOWN;
    (*n_marks)--;
    print_field(f);
}

void send(field* f, int n_marks, int *end) {
    if (n_marks != NUMBER_OF_BOMBS) {
        printf("Your number of marks is not equal to the number of bombs. Recheck.");
        return;
    }
    int aux;
    for (aux=0; aux!=NUMBER_OF_BOMBS; aux++) {
        if (f->field[f->bomb_coords[aux].x][f->bomb_coords[aux].y].shown != MARKED) {
            printf("Your marks are not correct. Recheck.");
            return;
        }
    }
    printf("You have won!\n");
    *end = 1;
    return;
}

void init_game(field* f) {
    /* Creating field. */
    printf("\nInform the desired field size and number of bombs. (rows, cols, bombs).\n");
    scanf("%d %d %d", &f->row, &f->col, &f->n_bombs);
    f->row+=2;
    f->col+=2;
    if (!alloc_field(f)) {
        printf("Could not allocate memory for the game. Aborting.");
        destroy_field(f);
        exit(0);
    }
    /* Initializing values. */
    init_field(f);
    /* Printing field. Taking first open cell.*/
    print_field(f);
    printf("\nInform the position to start the game. (row, col)\n");
    int start_i, start_j;
    scanf("%d %d", &start_i, &start_j);
    while(!valid_pos(start_i, start_j, f->row-1, f->col-1)) {
        printf("\nInvalid position.\n");
        scanf("%d %d", &start_i, &start_j);
    }
    /* Spreading bombs. */
    spread_bombs(f, start_i, start_j);
    /* Opening field. */
    open_field(f, start_i, start_j);
}

int main() {
    field game;
    init_game(&game);
    int end = 0, n_marks = 0;
    char cmd[5];
    print_field(&game);
    while (!end) {
        scanf("%s", cmd);
        if (strcmp(cmd, open_cmd) == 0) {
            open(&game, &end);
        } else if (strcmp(cmd, mark_cmd) == 0) {
            mark(&game, &n_marks);
        } else if (strcmp(cmd, unmk_cmd) == 0) {
            unmark(&game, &n_marks);
        } else if (strcmp(cmd, send_cmd) == 0) {
            send(&game, n_marks, &end);
        } else if (strcmp(cmd, help_cmd) == 0) {
            printf("Available commands:\n"
            "open: opens the content inside a cell.\n"
            "mark: flags a cell as a potential bomb.\n"
            "unmk: removes the flag from previously marked cell.\n"
            "send: checks if all bombs are marked, which is the winning condition.\n"
            "help: displays this message.\n"
            "quit: exits the game.\n");
        } else if (strcmp(cmd, quit_cmd) == 0) {
            destroy_field(&game);
            printf("Exiting.\n");
            exit(0);
        } else {
            printf("Unknown command. 0 0 help for a list of commands.\n");
        }
    }
    return 0;
}
