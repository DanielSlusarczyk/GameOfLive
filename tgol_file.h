#ifndef _TGOLFILE
#define _TGOLFILE

#define DEFAULT_ARGC 3

#include <stdbool.h>

FILE* inFile;
FILE* outFile;
bool sbs = false;
bool save = false;
bool overwrite = false;
bool refresh = false;
const char* knownFlags[4] = {"-sbs", "-save", "-overwrite", "-refresh"};
const char* errList[9] = {"INCORRECT_NUMBER_OF_ARGS", "UNKNOWN_FLAG", "INPUT_ERR", "INCORRECT_GENS", "INPUT_NOT_INT", "INPUT_SHORT", "INPUT_XY", "AMBIGUOUS_OUT", "NO_OUT"};

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

bool contains(const char**, char*);
ErrorCode argvErr(int, char**);

#endif