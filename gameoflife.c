#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"gameoflife.h"

int main(int argc, char** argv)
{
    //obsluga bledow
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

    //wczytywanie pliku do macierzy
    int dims[2];
    for(int i = 0; i < 2; i++)
    {
        fscanf(inputfile, "%d", &dims[i]);
    }
    printf("Loaded %d x %d matrix\n", dims[0], dims[1]);
    char** matrix = calloc(dims[0], sizeof(char*));
    fgetc(inputfile); //obgryzamy spacje/newline
    for(int i = 0; i < dims[0]; i++)
    {
        matrix[i] = calloc(dims[1], sizeof(char));
        for(int j = 0; j < dims[1]; j++)
        {
            matrix[i][j] = fgetc(inputfile);
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}