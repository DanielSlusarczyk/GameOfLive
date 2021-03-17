#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "gameoflife.h"

bool flag_exists(char* s)
{
    for(int i = 0; i < sizeof(flags) / sizeof(char*); i++)
    {
        if(strcmp(flags[i], s) == 0)
            return true;
    }
    return false;
}

int main(int argc, char** argv)
{
    ErrCode err;
    bool flags_present = (argc > DEFAULT_ARGC);
    bool save = false;
    bool overwrite = false;
    FILE* input_file = fopen(argv[DEFAULT_ARGC - 2], "r");
    FILE* output_file;
    
    if(argc < DEFAULT_ARGC)
    {
        printf("ERR: INCORRECT_NUMBER_OF_ARGS\n");
        return INCORRECT_NUMBER_OF_ARGS;
    }
    if(flags_present)
    {
        for(int i = DEFAULT_ARGC; i < argc; i++)
        {
            if(!flag_exists(argv[i]))
            {
                printf("ERR: UNKNOWN_FLAG\n");
                return UNKNOWN_FLAG;
            }
            else
            {
                if(strcmp(argv[i], "-save") == 0)
                {
                    save = true;
                    output_file = fopen(argv[i], "w");
                    if(i == argc - 1 || output_file == NULL)
                    {
                        printf("ERR: NO_OUT\n");
                        return NO_OUT;
                    }
                }
                if(strcmp(argv[i], "-overwrite") == 0)
                    overwrite = true;
            }
        }
    }
    if(input_file == NULL)
    {
        printf("ERR: INPUT_ERR\n");
        return INPUT_ERR;
    }
    if(atoi(argv[DEFAULT_ARGC - 1]) < 1)
    {
        printf("ERR: INCORRECT_GENS\n");
        return INCORRECT_GENS;
    }
    if(save && overwrite)
    {
        printf("ERR: AMBIGUOUS_OUT\n");
        return AMBIGUOUS_OUT;
    }
    
    return 0;
}