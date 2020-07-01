#include "aux_field.h"

void open(field* f, int i, int j, int *end);
void mark(field* f, int i, int j, int *n_marks);
void unmark(field* f, int i, int j, int *n_marks);
void send(field* f, int n_marks, int *end);
void help();
void quit(field* f);
