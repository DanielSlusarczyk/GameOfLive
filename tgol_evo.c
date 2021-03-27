#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tgol_file.h"
#include "tgol_evo.h"

char dead = 'o';
char alive = 'x';

//na razie wersja toporna, żeby jakkolwiek działał podgląd macierzy
void print_mat(data mat) {
    int colIterator = 0;
    bool** matrix = calloc(mat.y, sizeof(bool*));
    printf("MATRIX:\n");
    for(int i = 0; i < mat.y; i++) {
        matrix[i] = calloc(mat.x, sizeof(bool));
        int aliveInCurrentRow = mat.row_index[i + 1] - mat.row_index[i];
        for(int j = colIterator; j < colIterator + aliveInCurrentRow; j++) {
            matrix[i][mat.col_index[j]] = true;
        }
        colIterator += aliveInCurrentRow;
    }

    for(int i = 0; i < mat.y; i++) {
        for(int j = 0; j < mat.x; j++) {
            if(matrix[i][j])
                printf("%c ", alive);
            else
                printf("%c ", dead);
        }
        printf("\n");
    }
}
/*
int moore_neighb(data mat, int x, int y) {
    int alive_neighb = 0;
    int xstart = x > 1 ? x - 1 : x;
    int xlim = x != mat.x ? mat.x + 1 : x;
    int ystart = y > 1 ? y - 1 : y;
    int ylim = y != data->y ? data->y + 1 : y;
    for(int i = ystart; i < ylim; i++) {
        for(int j = xstart; j < xlim; j++) {

        }
    }
}

void evolve(data* mat, int mode) {

}
*/