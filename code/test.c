#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ncurses.h>
#include "tgol_file.h"
#include "tgol_evo.h"

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");
    FILE* outFile = NULL;
    bool sbs = false;
    bool save = false;
    bool overwrite = false;
    bool refresh = false;

    if(argc < DEFAULT_ARGC) {
        printf("%s\n", Errors[INCORRECT_NUMBER_OF_ARGS - 1]);
        return INCORRECT_NUMBER_OF_ARGS;
    }
    if(inFile == NULL) {
        printf("%s\n", Errors[FILE_OPEN_ERR - 1]);
        return FILE_OPEN_ERR;
    }

    if(atoi(argv[2]) <= 0) {
        printf("%s\n", Errors[INCORRECT_GENS - 1]);
        return INCORRECT_GENS;
    }

    int n = DEFAULT_ARGC;
    while(n < argc) {
        if(argv[n][0] != '-') {
            printf("%s\n", Errors[UNKNOWN_FLAG - 1]);
            return UNKNOWN_FLAG;
        }
        else {
            if(!contains(knownFlags, argv[n])) {
                printf("%s\n", Errors[UNKNOWN_FLAG - 1]);
                return UNKNOWN_FLAG;
            }
            else if(strcmp(argv[n], "-sbs") == 0)
                sbs = true;
            else if(strcmp(argv[n], "-save") == 0) {
                if(overwrite) {
                    printf("%s\n", Errors[AMBIGUOUS_OUT - 1]);
                    return AMBIGUOUS_OUT;
                }
                save = true;
                if(argv[n + 1][0] != '-') {
                    outFile = fopen(argv[n + 1], "w");
                    if(outFile == NULL) {
                        printf("%s\n", Errors[NO_OUT - 1]);
                        return NO_OUT;
                    }
                    n++;
                }
                else {
                    printf("%s\n", Errors[NO_OUT - 1]);
                    return NO_OUT;
                }
            }
            else if(strcmp(argv[n], "-overwrite") == 0) {
                if(save) {
                    printf("%s\n", Errors[AMBIGUOUS_OUT - 1]);
                    return AMBIGUOUS_OUT;
                }
                overwrite = true;
            }
            else if(strcmp(argv[n], "-refresh") == 0)
                refresh = true;
        }
        n++;
    }

    data mat;
    ErrorCode errCode = readFile(inFile, &mat);
    if(errCode != COR) {
        printf("%s\n", Errors[errCode - 1]);
        return errCode;
    }
    t_data matrix = &mat;
    printf("Wczytana generacja:\n");
    printMat(matrix);
    if(DEBUG) {
        printf("loaded %dx%d matrix from %s\n", mat.y, mat.x, argv[1]);
        printf("col index [ ");
        for(int i = 0; i < mat.colLength; i++)
            printf("%d ", mat.colIndex[i]);
        printf("]\n");
        printf("row index [ ");
        for(int i = 0; i < mat.rowLength; i++)
            printf("%d ", mat.rowIndex[i]);
        printf("]\n");
    }
    if(!DEBUG) {
        system("clear");
    }
    //Przeprowadzanie wszystkich generacji
    for(int i = 0; i < atoi(argv[2]); i++) {
        t_data tmpMat = newGeneration(matrix, 'm');
        if(CRSEquals(*matrix, *tmpMat)) {
            printf("stan planszy ustalił się na generacji %d, kończę działanie programu\n", i + 1);
            printf("stan planszy w generacji %d:\n", i + 1);
            printMat(matrix);
            free(tmpMat);
            free(matrix);
            break;
        }
        else
            matrix = tmpMat;
        printMat(matrix);
        if(!DEBUG) {
            if(sbs) {
                printf("press ENTER to continue\n");
                getchar();
            }
            else
                system("sleep 0.33");
            if(refresh)
                system("clear");
        }
        if(DEBUG) {
            printf("Wymiary: %d x %d\n", matrix->y, matrix->x);
            printf("ColIndex [ ");
            for(int i = 0; i < matrix->colLength; i++)
                printf("%d ", matrix->colIndex[i]);
            printf("]\n");
            printf("RowIndex [ ");
            for(int i = 0; i < matrix->rowLength; i++)
                printf("%d ", matrix->rowIndex[i]);
            printf("]\n");
        }
    }

    if(save) {
        writeFile(outFile, matrix);
    }
    else if(overwrite) {
        outFile = fopen(argv[1], "w");
        fprintf(outFile, "%s", "udało się nadpisać plik\n");
    }

    return 0;
}