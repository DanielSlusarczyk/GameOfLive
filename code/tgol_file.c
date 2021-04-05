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
    for (int i = 0; i < lim; i++) {
        if (strcmp(array[i], s) == 0)
            ret = true;
    }
    return ret;
}

ErrorCode readFile(FILE* in, t_data mat) {
    int xtemp, ytemp;
    char tmp[5];
    mat->colLength = 0;
    mat->colIndex = NULL;

    if (fscanf(in, "%d %s %d", &ytemp, tmp, &xtemp) != 3) {
        fclose(in);
        return INPUT_DIMS;
    }
    int readRow = ytemp;
    int readCol = 0;

    mat->x = xtemp;
    mat->y = ytemp;
    mat->rowIndex =(int*)calloc(mat->y + 1, sizeof(int));
    mat->rowIndex[0] = 0;
    mat->rowLength = mat->y + 1;
    int* numPerLine =(int*)calloc(ytemp, sizeof(int));

    int amount;
    while ((amount = fscanf(in, "%d %d", &xtemp, &ytemp)) != EOF) {
        if (amount == 2) {
            if (xtemp > mat->x || ytemp > mat->y || xtemp < 1 || ytemp < 1) {
                fclose(in);
                free(mat->rowIndex);
                free(numPerLine);
                return INPUT_LIMIT_XY;
            }
            if (readRow < ytemp) {
                fclose(in);
                free(mat->rowIndex);
                free(mat->colIndex);
                free(numPerLine);
                return INPUT_INCORRECT_ORDER;
            }
            if (readCol >= xtemp && readRow <= ytemp) {
                fclose(in);
                free(mat->rowIndex);
                free(mat->colIndex);
                free(numPerLine);
                return INPUT_INCORRECT_ORDER;
            }
            mat->colLength++;
            mat->colIndex = (int*)realloc(mat->colIndex, mat->colLength * sizeof(int));
            mat->colIndex[mat->colLength - 1] = xtemp - 1;
            numPerLine[mat->y - ytemp]++;
        }
        else {
            fclose(in);
            free(mat->rowIndex);
            free(mat->colIndex);
            free(numPerLine);
            return INPUT_INCORRECT;
        }
        readRow = ytemp;
        readCol = xtemp;
    }

    int sum = 0;
    for (int i = 1; i <= mat->y; i++) {
        sum += numPerLine[i - 1];
        mat->rowIndex[i] = sum;
    }
    
    fclose(in);
    free(numPerLine);
    return COR;
}

void writeFile(FILE* out, t_data mat) {
    fprintf(out, "%d x %d\n", mat->y, mat->x);
    int colIterator = 0;
    for (int i = 1; i < mat->rowLength; i++) {
        int aliveCurrentRow = mat->rowIndex[i] - mat->rowIndex[i - 1];
        for (int j = colIterator; j < colIterator + aliveCurrentRow; j++) {
            fprintf(out, "%d %d\n", mat->colIndex[j] + 1, mat->x - i + 1);
        }
        colIterator += aliveCurrentRow;
    }
    fclose(out);
}