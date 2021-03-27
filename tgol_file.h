#ifndef _TGOLFILE
#define _TGOLFILE

#define DEBUG 1
#define DEFAULT_ARGC 3

#include <stdio.h>
#include <stdbool.h>

extern const char* knownFlags[4];
extern const char* Errors[10];

typedef enum {
    INCORRECT_NUMBER_OF_ARGS = 1,
    UNKNOWN_FLAG,
    FILE_OPEN_ERR,
    INCORRECT_GENS,
    INPUT_LIMIT_XY,
    INPUT_DIMS,
    INPUT_INCORRECT,
    INPUT_INCORRECT_ORDER,
    AMBIGUOUS_OUT,
    NO_OUT
} ErrorCode;

typedef struct {
    int x;
    int y;
    int* col_index;
    int* row_index;
    int col_length;
    int row_length;
} data, * t_data;


bool contains(const char**, char*);
ErrorCode read_file(FILE*, t_data);

#endif