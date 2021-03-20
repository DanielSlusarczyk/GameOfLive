#ifndef _TGOLFILE
#define _TGOLFILE

#define DEBUG 1
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

typedef struct data {
    //Wymiar x planszy
    int x;
    //Wymiar y planszy
    int y;
    //Wektor z numerami kolumn
    int* col_index;
    //Wektor z ilościa niezerowych elementów w wierszu
    int* row_index;
    //Długośc wektora col_index
    int col_length;
    //Długość wektora row_index
    int row_length;
} data, * t_data;


bool contains(const char**, char*);
ErrorCode read_file(FILE* in, t_data matrix);

#endif