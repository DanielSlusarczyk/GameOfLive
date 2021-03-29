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

void printMat(t_crs);
t_field addCoordinates(t_crs, t_field, int, int, bool);
t_crs newGeneration(t_crs, char);
bool CRSEquals(crs, crs);

#endif
