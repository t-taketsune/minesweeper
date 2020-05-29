#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UNKNOWN 'X'
#define EMPTY 0
#define BOMB 10
#define SIZE 20
#define NUMBER_OF_BOMBS 20

typedef struct {
    int real;
    char shown;
} cell;

char int_to_char(int x) {
    return (char) (x + 48);
}

int valid_pos(int i, int j) {
    return (i>=0 && i<SIZE && j>=0 && j<SIZE) ? 1 : 0;
}

void aux_fill(cell(*field)[SIZE], int i, int j) {
    if (valid_pos(i-1, j-1)) {
        field[i-1][j-1].real+=1;
    }
    if (valid_pos(i, j-1)) {
        field[i][j-1].real+=1;
    }
    if (valid_pos(i+1, j-1)) {
        field[i+1][j-1].real+=1;
    }
    if (valid_pos(i-1, j+1)) {
        field[i-1][j+1].real+=1;
    }
    if (valid_pos(i, j+1)) {
        field[i][j+1].real+=1;
    }
    if (valid_pos(i+1, j+1)) {
        field[i+1][j+1].real+=1;
    }
    if (valid_pos(i-1, j)) {
        field[i-1][j].real+=1;
    }
    if (valid_pos(i+1, j)) {
        field[i+1][j].real+=1;
    }
}

void print_field(cell (*field)[SIZE]) {
    for (int i=0; i!=SIZE; i++) {
        for (int j=0; j!=SIZE; j++)
            printf("%c ", field[i][j].shown);
        printf("\n");
    }
}

void open_field(cell(*field)[SIZE], int i, int j) {
    if (field[i][j].shown == field[i][j].real) {
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

int main() {
    cell field[SIZE][SIZE];
    int i, j, end=0;
    for (i=0; i!=SIZE; i++)
        for (j=0; j!=SIZE; j++) {
            field[i][j].real = EMPTY;
            field[i][j].shown = UNKNOWN;
        }
    srand(time(NULL));
    for (int aux=0; aux!=NUMBER_OF_BOMBS; aux++) {
        i = rand()%SIZE;
        j = rand()%SIZE;
        if (field[i][j].real == EMPTY) {
            field[i][j].real = BOMB;
            aux_fill(field, i, j);
        }
        else {
            aux--;
        }
    }
    while (!end) {
        print_field(field);
        scanf("%d %d", &i, &j);
        if (field[i][j].real == BOMB) {
            printf("You lost.\n");
            end = 1;
        } else if (field[i][j].real != EMPTY) {
            field[i][j].shown = int_to_char(field[i][j].real);
        } else {
            open_field(field, i, j);
        }
    }


}
