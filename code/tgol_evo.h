#ifndef _TGOLEVO
#define _TGOLEVO
#include <stdbool.h>
#include "tgol_file.h"

extern char dead, alive;

typedef struct field {
    int x;
    int y;
    int neighbors;
    bool previousAlive;
    struct field* next;
} field, *t_field;

void printMat(t_data);
t_field addCoordinates(t_data, t_field, int, int, bool);
t_data newGeneration(t_data, char);
bool CRSEquals(data, data);

#endif
