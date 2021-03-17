#ifndef _GAMEOFLIFE
#define _GAMEOFLIFE

#define DEFAULT_ARGC 3

const char* flags[4] = {"-sbs", "-save", "-overwrite", "-refresh"};

typedef enum
{   INCORRECT_NUMBER_OF_ARGS = 1,
    UNKNOWN_FLAG,
    INPUT_ERR,
    INCORRECT_GENS,
    INPUT_NOT_INT,
    INPUT_SHORT,
    INPUT_XY,
    AMBIGUOUS_OUT,
    NO_OUT
} ErrCode;

#include<stdlib.h>

int vonneumann();
int moore();

#endif