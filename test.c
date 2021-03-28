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
            else if(strcmp(argv[n], "-sbs") == 0) sbs = true;
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
    ErrorCode errCode = read_file(inFile, &mat);
    if(errCode != COR) {
        printf("%s\n", Errors[errCode - 1]);
        return errCode;
    }
    t_data matrix = &mat;
    printf("Wczytana generacja:\n");
    print_generation(matrix);
    if(DEBUG) {
        printf("Wymiary: %d x %d\n", mat.y, mat.x);
        printf("Col_index [ ");
        for(int i = 0; i < mat.col_length; i++)
            printf("%d ", mat.col_index[i]);
        printf("]\n");
        printf("Row_index [ ");
        for(int i = 0; i < mat.row_length; i++)
            printf("%d ", mat.row_index[i]);
        printf("]\n");
    }
    if(overwrite) {
        fclose(inFile);
        outFile = fopen(argv[1], "w");
        fprintf(outFile, "%s", "udało się nadpisać plik\n");
    }
    if(save) {
        fprintf(outFile, "%s", "udało się zapisać do pliku\n");
    }
    if(!DEBUG) {
        system("clear");
    }
    //Przeprowadzanie wszystkich generacji
    for(int i = 0; i < atoi(argv[2]); i++) {
        matrix = new_generation(matrix);
        print_generation(matrix);
        if(!DEBUG) {
            system("sleep 0.05");
            system("clear");
        }
        if(DEBUG) {
            printf("Wymiary: %d x %d\n", matrix->y, matrix->x);
            printf("Col_index [ ");
            for(int i = 0; i < matrix->col_length; i++)
                printf("%d ", matrix->col_index[i]);
            printf("]\n");
            printf("Row_index [ ");
            for(int i = 0; i < matrix->row_length; i++)
                printf("%d ", matrix->row_index[i]);
            printf("]\n");
        }
    }
    return 0;
}