#ifndef _TGOLEVO
#define _TGOLEVO
#include "tgol_file.h"

extern char dead, alive;

void print_mat(data);
int moore_neighb(data, int, int);
int neumann_neighb(data, int, int);
void evolve(data*, int);

#endif