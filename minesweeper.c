#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define UNKNOWN 'X'
#define MARKED 'O'
#define OPEN ' '
#define EMPTY 0
#define BOMB 10
#define SIZE 10
#define NUMBER_OF_BOMBS 2

static const char open_cmd[] = "open";
static const char mark_cmd[] = "mark";
static const char unmk_cmd[] = "unmk";
static const char send_cmd[] = "send";

typedef struct {
    int real;
    char shown;
} cell;

typedef struct {
    int x, y;
} coor;

char int_to_char(int x) {
    return (char) (x + 48);
}

int valid_pos(int i, int j) {
    return (i>=0 && i<SIZE+1 && j>=0 && j<SIZE+1) ? 1 : 0;
}

int near_start(int i, int j, int s_i, int s_j) {
    if ((i >= s_i - 1 && i <= s_i + 1) || (j >= s_j - 1 && j <= s_j + 1))
        return 1;
    return 0;
}

void aux_fill(cell(*field)[SIZE+2], int i, int j) {
    field[i-1][j-1].real+=1;
    field[i][j-1].real+=1;
    field[i+1][j-1].real+=1;
    field[i-1][j+1].real+=1;
    field[i][j+1].real+=1;
    field[i+1][j+1].real+=1;
    field[i-1][j].real+=1;
    field[i+1][j].real+=1;
}

void print_field(cell (*field)[SIZE+2]) {
    printf("\n  01");
    for (int aux=2; aux!=SIZE+2; aux++) {
        if (aux%5 == 0) {
            printf("%02d", aux);
        } else if (aux+1%5 != 0) {
            printf("  ");
        }
    }
    printf("\n01 ");
    for (int aux=1; aux!=SIZE+1; aux++)
        printf("%c ", field[1][aux].shown);
    printf("\n");
    for (int i=2; i!=SIZE+1; i++) {
        i%5 == 0 ? printf("%02d ", i) : printf("   ");
        for (int j=1; j!=SIZE+1; j++)
            printf("%c ", field[i][j].shown);
        printf("\n");
    }
}

void open_field(cell(*field)[SIZE+2], int i, int j) {
    if (field[i][j].shown == field[i][j].real || field[i][j].shown == MARKED) {
        return;
    }
    if (field[i][j].real != EMPTY) {
        field[i][j].shown = int_to_char(field[i][j].real);
        return;
    }
    field[i][j].shown = field[i][j].real;
    if (valid_pos(i + 1, j)) {
        open_field(field, i + 1, j);
    }
    if (valid_pos(i - 1, j)) {
        open_field(field, i - 1, j);
    }
    if (valid_pos(i, j + 1)) {
        open_field(field, i, j + 1);
    }
    if (valid_pos(i, j - 1)) {
        open_field(field, i, j - 1);
    }
}

void open(int i, int j, cell(*field)[SIZE+2], int *end) {
    if (field[i][j].real == BOMB) {
        printf("You have lost the game.");
        *end = 1;
        return;
    }
    open_field(field, i, j);
}

void mark(int i, int j, cell(*field)[SIZE+2], int *n_marks) {
    if (field[i][j].shown == MARKED) {
        printf("This cell is already marked.");
        return;
    }
    field[i][j].shown = MARKED;
    (*n_marks)++;
}

void unmark(int i, int j, cell(*field)[SIZE+2], int *n_marks) {
    if (field[i][j].shown != MARKED) {
        printf("This cell is not marked.");
        return;
    }
    field[i][j].shown = UNKNOWN;
    (*n_marks)--;
}

void send(int i, int j, cell(*field)[SIZE+2], int *n_marks, coor bombs[], int *end) {
    if ((*n_marks) != NUMBER_OF_BOMBS) {
        printf("Your number of marks is not equal to the number of bombs. Recheck.");
        return;
    }
    for (int aux=0; aux!=NUMBER_OF_BOMBS; aux++) {
        if (field[bombs[aux].x][bombs[aux].y].shown != MARKED) {
            printf("Your marks are not correct. Recheck.");
            return;
        }
    }
    printf("You have won!\n");
    *end = 1;
    return;
}

int main() {
    printf("%s %s %s", mark_cmd, open_cmd, unmk_cmd);
    cell field[SIZE+2][SIZE+2];
    coor bomb_coords[NUMBER_OF_BOMBS];
    int i, j, end=0, start_i, start_j, n_marks=0;
    char cmd[5]="open";
    for (i=0; i!=SIZE+2; i++)
        for (j=0; j!=SIZE+2; j++) {
            field[i][j].real = EMPTY;
            field[i][j].shown = UNKNOWN;
        }
    srand(time(NULL));
    print_field(field);
    scanf("%d %d", &start_i, &start_j);
    for (int aux=0; aux!=NUMBER_OF_BOMBS; aux++) {
        i = (rand()%SIZE)+1;
        j = (rand()%SIZE)+1;
        if (field[i][j].real == EMPTY && !near_start(i, j, start_i, start_j)) {
            field[i][j].real = BOMB;
            aux_fill(field, i, j);
            bomb_coords[aux].x = i;
            bomb_coords[aux].y = j;
        }
        else {
            aux--;
        }
    }
    i = start_i;
    j = start_j;
    open(i, j, field, &end);
    while (!end) {
        print_field(field);
        scanf("%d %d %s", &i, &j, cmd);
        if (strcmp(cmd, open_cmd) == 0) {
            open(i, j, field, &end);
        } else if (strcmp(cmd, mark_cmd) == 0) {
            mark(i, j, field, &n_marks);
        } else if (strcmp(cmd, unmk_cmd) == 0) {
            unmark(i, j, field, &n_marks);
        } else if (strcmp(cmd, send_cmd) == 0) {
            send(i, j, field, &n_marks, bomb_coords, &end);
        }
    }
}
