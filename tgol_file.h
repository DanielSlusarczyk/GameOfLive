#ifndef _TGOLFILE
#define _TGOLFILE

#define DEFAULT_ARGC 3

bool sbs = false;
bool save = false;
bool overwrite = false;
bool refresh = false;
const char* knownFlags[4] = {"-sbs", "-save", "-overwrite", "-refresh"};

typedef enum {
    INCORRECT_NUMBER_OF_ARGS = 1,
    UNKNOWN_FLAG,
    INPUT_ERR,
    INCORRECT_GENS,
    INPUT_NOT_INT,
    INPUT_SHORT,
    INPUT_XY,
    AMBIGUOUS_OUT,
    NO_OUT
} ErrorCode;

#endif