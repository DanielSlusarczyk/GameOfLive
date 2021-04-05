﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "tgol_file.h"
#include "tgol_evo.h"
#include "tgol_png.h"

#ifndef DEBUG
#define DEBUG false
#endif

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");
    FILE* outFile = NULL;
    bool sbs = false;
    bool save = false;
    bool overwrite = false;
    bool refresh = false;
    double sleepTime = 1;
    const char *fileExte = ".png";
    char fileName [30];

    if(argc < DEFAULT_ARGC) {
        printf("%s\n", Errors[INCORRECT_NUMBER_OF_ARGS - 1]);
        return INCORRECT_NUMBER_OF_ARGS;
    }
    if(inFile == NULL) {
        fclose(inFile);
        printf("%s\n", Errors[FILE_OPEN_ERR - 1]);
        return FILE_OPEN_ERR;
    }

    if(atoi(argv[2]) <= 0) {
        printf("%s\n", Errors[INCORRECT_GENS - 1]);
        fclose(inFile);
        return INCORRECT_GENS;
    }

    int n = DEFAULT_ARGC;
    while(n < argc) {
        if(argv[n][0] != '-') {
            printf("%s\n", Errors[UNKNOWN_FLAG - 1]);
            fclose(inFile);
            return UNKNOWN_FLAG;
        }
        else {
            if(!contains(knownFlags, argv[n])) {
                printf("%s\n", Errors[UNKNOWN_FLAG - 1]);
                fclose(inFile);
                return UNKNOWN_FLAG;
            }
            else if(strcmp(argv[n], "-sbs") == 0)
                sbs = true;
            else if(strcmp(argv[n], "-save") == 0) {
                if(overwrite) {
                    printf("%s\n", Errors[AMBIGUOUS_OUT - 1]);
                    fclose(inFile);
                    return AMBIGUOUS_OUT;
                }
		if(argc == n+1){
			printf("%s\n", Errors[NO_OUT - 1]);
			return NO_OUT;
		}
                save = true;
                if(argv[n + 1][0] != '-') {
                    outFile = fopen(argv[n + 1], "w");
		    strcpy(fileName, argv[n+1]);
                    if(outFile == NULL) {
                        printf("%s\n", Errors[NO_OUT - 1]);
                        fclose(inFile);
                        return NO_OUT;
                    }
                    n++;
                }
                else {
                    printf("%s\n", Errors[NO_OUT - 1]);
                    fclose(inFile);
                    return NO_OUT;
                }
            }
            else if(strcmp(argv[n], "-overwrite") == 0) {
                if(save) {
                    printf("%s\n", Errors[AMBIGUOUS_OUT - 1]);
                    fclose(inFile);
                    return AMBIGUOUS_OUT;
                }
                overwrite = true;
            }
            else if(strcmp(argv[n], "-refresh") == 0) {
                refresh = true;
                if(argv[n + 1] != NULL && argv[n + 1][0] != '-') {
                    sleepTime = atof(argv[++n]);
                    printf("wczytano czas odświeżenia ekranu: %.2lf\n", sleepTime);
                    printf("wciśnij ENTER aby kontynuować\n");
                    getchar();
                }
                else {
                    sleepTime = 0.8;
                    printf("ustawiono domyślny czas odświeżenia ekranu: %.2lf\n", sleepTime);
                    printf("wciśnij ENTER aby kontynuować\n");
                    getchar();
                }
            }
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

    t_data tmpMat = NULL;
    for(int i = 0; i < atoi(argv[2]); i++) {
        tmpMat = newGeneration(matrix, 'm');
	printf("GENERACJA NUMER: %d\n", i+1);
        if(CRSEquals(*matrix, *tmpMat)) {
	    printMat(matrix);
            printf("stan planszy ustalony, koniec programu\n");
            printf("wciśnij ENTER aby kontynuować\n");
            getchar();
            free(tmpMat);
            break;
        }
        else {
	    free(matrix->colIndex);
	    free(matrix->rowIndex);
            if(i!=0)
                free(matrix);
            matrix = tmpMat;
        }
        printMat(matrix);
        if(!DEBUG) {
            if(sbs) {
                printf("press ENTER to continue\n");
                getchar();
            }
            else if(refresh)
                usleep(1000000 * sleepTime);
            if(refresh && i!=atoi(argv[2])-1)
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
	generateImg(matrix->x, matrix->y, strcat( fileName, fileExte), matrix);
    }
    else if(overwrite) {
        outFile = fopen(argv[1], "w");
        writeFile(outFile, matrix);
    }
    free(tmpMat->colIndex);
    free(tmpMat->rowIndex);
    free(matrix);

    return 0;
}