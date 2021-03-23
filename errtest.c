#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tgol_file.h"

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");
    FILE* outFile = NULL;
    bool sbs = false;
    bool save = false;
    bool overwrite = false;
    bool refresh = false;

    if(argc < DEFAULT_ARGC)
        return INCORRECT_NUMBER_OF_ARGS;
    if(inFile == NULL)
        return FILE_OPEN_ERR;
    if(atoi(argv[2]) <= 0)  
        return INCORRECT_GENS;

    int n = DEFAULT_ARGC;
    while(n < argc) {
        if(argv[n][0] != '-')
            return UNKNOWN_FLAG;
        else {
            if(!contains(knownFlags, argv[n]))
                return UNKNOWN_FLAG;
            else if(strcmp(argv[n], "-sbs") == 0) sbs = true;
            else if(strcmp(argv[n], "-save") == 0) {
                if(overwrite)
                    return AMBIGUOUS_OUT;
                save = true;
                if(argv[n+1][0] != '-') {
                    outFile = fopen(argv[n+1], "w");
                    if(outFile == NULL)
                        return NO_OUT;
                    n++;
                }
                else return NO_OUT;
            }
            else if(strcmp(argv[n], "-overwrite") == 0) {
                if(save) return AMBIGUOUS_OUT;
                overwrite = true;
            }
            else if(strcmp(argv[n], "-refresh") == 0) refresh = true;
        }
        n++;
    }

    data mat;
    ErrorCode errCode = read_file(inFile, &mat);
    if(errCode != 0)
        return errCode;
    if(DEBUG) {
        printf("Wymiary: %d x %d\n", mat.x, mat.y);
        printf("Col_index [ ");
        for(int i = 0; i < mat.col_length; i++)
            printf("%d ", mat.col_index[i]);
        printf("]\n");
        printf("Row_index [ ");
        for(int i = 0; i <= mat.row_length; i++)
            printf("%d ", mat.row_index[i]);
        printf("]\n");
    }
    
    if(overwrite) {
        fclose(inFile);
        inFile = fopen(argv[1], "w");
    }
    return 0;
}


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
    mat->row_index = (int*)malloc((mat->y+1) * sizeof(int));
    mat->row_index[0] = 0;
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
            mat->col_index = (int*)realloc(mat->col_index, mat->col_length *sizeof(int));
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