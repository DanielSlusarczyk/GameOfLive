#ifndef _TGOLEVO
#define _TGOLEVO
#include "tgol_file.h"

extern char dead, alive;

typedef struct field{
    int x;
    int y;
    int neighbors;
    bool previous_alive;
    struct field* next;
} field, *t_field;

void print_generation(t_data);
t_field add_coordinates(t_data, t_field, int, int, bool);
t_data new_generation(t_data);

#endif
