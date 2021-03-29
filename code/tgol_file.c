#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tgol_file.h"

const char* knownFlags[4] = { "-sbs", "-save", "-overwrite", "-refresh" };
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
    int lim = sizeof(knownFlags) / sizeof(const char*);
    for(int i = 0; i < lim; i++) {
        if(strcmp(array[i], s) == 0)
            ret = true;
    }
    return ret;
}

ErrorCode readFile(FILE* in, t_data mat) {
    int xtemp, ytemp;
    char tmp[5];
    mat->colLength = 0;
    mat->colIndex = NULL;
    //Czytanie pierwszej linii
    if (fscanf(in, "%d %s %d", &ytemp, tmp, &xtemp) != 3)
        return INPUT_DIMS;

    int readRow = ytemp;
    int readCol = 0;

    //Inicjalizowanie struktury
    mat->x = xtemp;
    mat->y = ytemp;
    mat->rowIndex = calloc(mat->y + 1, sizeof(int));
    mat->rowIndex[0] = 0;
    mat->rowLength = mat->y+1;
    int* numPerLine = calloc(ytemp, sizeof(int));

    //Czytanie reszty linii
    int amount;
    while ((amount = fscanf(in, "%d %d", &xtemp, &ytemp)) != EOF) {
        if (amount == 2) {
            if (xtemp > mat->x || ytemp > mat->y || xtemp < 1 || ytemp < 1)
                return INPUT_LIMIT_XY;
            if (readRow < ytemp)
                return INPUT_INCORRECT_ORDER;
            if (readCol >= xtemp && readRow <= ytemp)
                return INPUT_INCORRECT_ORDER;
            mat->colLength++;
            mat->colIndex = (int*)realloc(mat->colIndex, mat->colLength * sizeof(int));
            mat->colIndex[mat->colLength - 1] = xtemp - 1;
            numPerLine[mat->y - ytemp]++;
        }
        else
            return INPUT_INCORRECT;

        readRow = ytemp;
        readCol = xtemp;
    }

    int sum = 0;
    for (int i = 1; i <= mat->y; i++) {
        sum += numPerLine[i - 1];
        mat->rowIndex[i] = sum;
    }
    return COR;
}