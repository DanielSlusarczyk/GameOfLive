#ifndef _TGOLEVO
#define _TGOLEVO
#include "tgol_file.h"

extern char dead, alive;

void print_mat(data);
bool isAlive(data, int, int);
void printMooreNextGen(data);
void printNeumannNextGen(data);

#endif