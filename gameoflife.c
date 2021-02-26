#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
HOW TO CALL THE PROGRAM

with step by step mode disabled:
./gameoflife.exe <input file> <number of generations>

with step by step mode enabled:
./gameoflife.exe -sts <input file> <number of generations>

number of generations should always be >= 2
*/

int main(int argc, char** argv)
{
    int sts = strcmp(argv[1], "-sts") == 0 ? 1 : 0;
    if(sts == 1)
    {
        printf("Step by step mode enabled\n");
    }
    if(argc != (3 + sts))
    {
        printf("error code 1: incorrect number of args\n");
        return 1;
    }
    FILE* inputfile = fopen(argv[1 + sts], "r");
    if(inputfile == NULL)
    {
        printf("error code 2: cannot open the specified input file\n");
        return 2;
    }
    int generations = atoi(argv[2 + sts]);
    {
        if(generations == 0)
        {
            printf("error code 3: invalid number of generations\n");
            return 3;
        }
    }
    return 0;
}