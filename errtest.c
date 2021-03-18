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

int main(int argc, char** argv) {

    if(argc < DEFAULT_ARGC) {
        printf("INCORRECT_NUMBER_OF_ARGS\n");
        return INCORRECT_NUMBER_OF_ARGS;
    }
    //sprawdzam obowiazkowe argumenty, w kolejnosci ich wystepowania
    FILE* inFile = fopen(argv[1], "r");
    if(inFile == NULL) {
        printf("INPUT_ERR\n");
        return INPUT_ERR;
    }
    if(atoi(argv[2]) <= 0) {
        printf("INCORRECT_GENS\n");
        return INCORRECT_GENS;
    }

    int n = DEFAULT_ARGC;
    bool spotkany = false;
    while(n < argc) {
        if(argv[n][0] != '-') {
            printf("UNKNOWN_FLAG\n");
            return UNKNOWN_FLAG;
        }
        else {
            if(!contains(knownFlags, argv[n])) {
                printf("UNKNOWN_FLAG\n");
                return UNKNOWN_FLAG;
            }
            else if(strcmp(argv[n], "-save") == 0) {
                if(!spotkany)
                    spotkany = true;
                else {
                    printf("AMBIGUOUS_OUT\n");
                    return AMBIGUOUS_OUT;
                }
                if(argv[n+1][0] != '-') {
                    FILE* outFile = fopen(argv[n+1], "w");
                    if(outFile == NULL) {
                        printf("NO_OUT\n");
                        return NO_OUT;
                    }
                    n++;
                }
                else {
                    printf("NO_OUT\n");
                    return NO_OUT;
                }
            }
            else if(strcmp(argv[n], "-overwrite") == 0) {
                if(!spotkany)
                    spotkany = true;
                else {
                    printf("AMBIGUOUS_OUT\n");
                    return AMBIGUOUS_OUT;
                }
            }
        }
        n++;
    }
    
    return 0;
}