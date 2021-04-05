#ifndef _TGOLFILE
#define _TGOLFILE

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
    NO_OUT,
    COR
} ErrorCode;

typedef struct data {
    int x;
    int y;
    int* colIndex;
    int* rowIndex;
    int colLength;
    int rowLength;
} data, * t_data;

bool contains(const char**, char*);
ErrorCode readFile(FILE*, t_data);
void writeTxt(FILE*, t_data);

#endif