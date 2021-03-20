#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tgol_file.h"

bool contains(const char** array, char* s) {
    bool ret = false;
    int lim = sizeof(knownFlags)/sizeof(const char*);
    for(int i = 0; i < lim; i++) {
        if(strcmp(array[i], s) == 0)
            ret = true;
    }
    return ret;
}

ErrorCode argvErr(int argc, char** argv) {
    if(argc < DEFAULT_ARGC) return INCORRECT_NUMBER_OF_ARGS;
    //sprawdzam obowiazkowe argumenty, w kolejnosci ich wystepowania
    FILE* inFile = fopen(argv[1], "r");
    if(inFile == NULL) return INPUT_ERR;
    fclose(inFile);
    if(atoi(argv[2]) <= 0) return INCORRECT_GENS;

    int n = DEFAULT_ARGC;
    bool spotkany = false;
    while(n < argc) {
        if(argv[n][0] != '-') return UNKNOWN_FLAG;
        else {
            if(!contains(knownFlags, argv[n])) return UNKNOWN_FLAG;
            else if(strcmp(argv[n], "-sbs") == 0) sbs = true;
            else if(strcmp(argv[n], "-save") == 0) {
                if(overwrite) return AMBIGUOUS_OUT;
                save = true;
                if(argv[n+1][0] != '-') {
                    FILE* outFile = fopen(argv[n+1], "w");
                    if(outFile == NULL) return NO_OUT;
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
    return 0;
}

int main(int argc, char** argv) {

    ErrorCode errCode = argvErr(argc, argv);
    if(errCode != 0) {
        printf("%s\n", errList[errCode-1]);
        return errCode;
    }
    return 0;
}