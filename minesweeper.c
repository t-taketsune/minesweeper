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
    printf("\n ");
    for (int aux=0; aux!=SIZE+2; aux++) {
        if (aux%5 == 0) {
            printf("%02d", aux);
        } else if (aux+1%5 != 0) {
            printf("  ");
        }
    }
    printf("\n\n");
    for (int i=1; i!=SIZE+2; i++) {
        i%5 == 0 ? printf("%02d ", i) : printf("   ");
        for (int j=1; j!=SIZE+2; j++)
            printf("%c ", field[i][j].shown);
        printf("\n");
    }
}

void open_field(cell(*field)[SIZE+2], int i, int j) {
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
    cell field[SIZE+2][SIZE+2];
    int i, j, end=0, start_i, start_j;
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
        }
        else {
            aux--;
        }
    }
    i = start_i;
    j = start_j;
    while (!end) {
        if (field[i][j].real == BOMB) {
            printf("You lost.\n");
            end = 1;
        } else if (field[i][j].real != EMPTY) {
            field[i][j].shown = int_to_char(field[i][j].real);
        } else {
            open_field(field, i, j);
        }
        print_field(field);
        scanf("%d %d", &i, &j);
    }


}
