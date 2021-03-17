#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tgol_file.h"

bool contains(const char** array, char* s) {
    bool ret = false;
    for(int i = 0; i < (int)sizeof(array)/sizeof(char*); i++) {
        if(strcmp(array[i], s) == 0)
            ret = true;
    }
    return ret;
}

int main(int argc, char** argv) {

    //najpierw sprawdzam obowiazkowe argumenty, w kolejnosci ich wystepowania
    FILE* inFile = fopen(argv[1], "r");
    if(inFile == NULL) {
        printf("INPUT_ERR\n");
        return INPUT_ERR;
    }
    if(atoi(argv[2]) <= 0) {
        printf("INCORRECT_GENS\n");
        return INCORRECT_GENS;
    }
    //jezeli mamy wiecej niz 2 argumenty (nie liczac exe/out), uznajemy ze pojawila sie flaga
    bool flagsPresent = argc > DEFAULT_ARGC;

    //sprawdzamy czy jako 3 argument faktycznie jest flaga, czy jaka glupota
    if(flagsPresent && argv[DEFAULT_ARGC][0] != '-') {
        printf("INCORRECT_NUMBER_OF_ARGS\n");
        return INCORRECT_NUMBER_OF_ARGS;
    }
    if(flagsPresent) {
        bool saveOverwrite = false;
        for(int i = 1; i < argc; i++) {
            if(!contains(knownFlags, argv[i])) {
                /*
                jezeli obecnego argv nie ma na liscie znanych flag, to sprawdzamy czy rozpatrywac
                je jako sciezke do wyjscia, czy jako nieznana flage
                */
                if(strcmp(argv[i-1], "-save") == 0) {
                    FILE* outFile = fopen(argv[i], "w");
                    if(outFile == NULL) {
                        printf("NO_OUT\n");
                        return NO_OUT;
                    }
                }
                else {
                    printf("UNKNOWN_FLAG\n");
                    return UNKNOWN_FLAG;
                }
            }
            //jezeli flaga istnieje, sprawdzamy czy nie napotkano "-save" lub "-overwrite"
            else if(strcmp(argv[i], "-save") == 0 || strcmp(argv[i], "-overwrite") == 0) {
                //jezeli to pierwsze napotkanie jednego lub drugiego, odhaczam ze napotkalem
                if(!saveOverwrite) saveOverwrite = true;
                //jezeli to nie pierwsze, to mam konflikt, wystepuje blad
                else {
                    printf("AMBIGUOUS_OUT\n");
                    return AMBIGUOUS_OUT;
                }
            }
        }
    }   
    return 0;
}