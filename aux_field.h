#include "declarations.h"

int valid_pos(int i, int j, int row, int col);
int aux_fill_check(int value);
void aux_fill(cell** field, int i, int j);
char int_to_char(int x);
int near_start(int i, int j, int s_i, int s_j);
int alloc_field(field* f);
void destroy_field(field* f);
void print_field(field* f);
void spread_bombs(field* f, int start_i, int start_j);
void open_field(field* f, int i, int j);
