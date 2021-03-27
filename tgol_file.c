#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tgol_file.h"

const char* knownFlags[4] = {"-sbs", "-save", "-overwrite", "-refresh"};
const char* Errors[10] = {
    "INCORRECT_NUMBER_OF_ARGS",
    "UNKNOWN_FLAG",
    "FILE_OPEN_ERR",
    "INCORRECT_GENS",
    "INPUT_LIMIT_XY",
    "INPUT_DIMS",
    "INPUT_INCORRECT",
    "INPUT_INCORRECT_ORDER",
    "AMBIGUOUS_OUT",
    "NO_OUT"
};

bool contains(const char** array, char* s) {
    bool ret = false;
    int lim = sizeof(knownFlags)/sizeof(const char*);
    for(int i = 0; i < lim; i++) {
        if(strcmp(array[i], s) == 0)
            ret = true;
    }
    return ret;
}

ErrorCode read_file(FILE* in, t_data mat) {
    int xtemp, ytemp;
    char tmp[5];
    mat->row_length = 0;
    mat->col_length = 0;
    mat->col_index = NULL;
    //Czytanie pierwszej linii
    if(fscanf(in, "%d %s %d", &ytemp, tmp, &xtemp) != 3)
        return INPUT_DIMS;

    int read_row = ytemp;
    int read_col = 0;

    //Inicjalizowanie struktury
    mat->x = xtemp;
    mat->y = ytemp;
    mat->row_index = (int*)calloc((mat->y+1), sizeof(int));
    mat->row_length = mat->y;
    int* numPerLine = (int*)calloc(ytemp, sizeof(int));

    //Czytanie reszty linii
    int amount;
    while((amount = fscanf(in, "%d %d", &xtemp, &ytemp)) != EOF) {
        if(amount == 2) {
            if(xtemp > mat->x || ytemp > mat->y || xtemp < 1 || ytemp < 1)
                return INPUT_LIMIT_XY;
            if(read_row < ytemp)
                return INPUT_INCORRECT_ORDER;
            if(read_col >= xtemp && read_row <= ytemp)
                return INPUT_INCORRECT_ORDER;
            mat->col_length++;
            mat->col_index = (int*)realloc(mat->col_index, mat->col_length * sizeof(int));
            mat->col_index[mat->col_length - 1] = xtemp - 1;
            numPerLine[mat->y - ytemp]++;
        }
        else
            return INPUT_INCORRECT;

        read_row = ytemp;
        read_col = xtemp;
    }

    int sum = 0;
    for(int i = 1; i <= mat->y; i++) {
        sum += numPerLine[i - 1];
        mat->row_index[i] = sum;
    }
    return 0;
}