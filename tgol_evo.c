#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tgol_file.h"
#include "tgol_evo.h"

char dead = 'o';
char alive = 'x';

void print_mat(data mat) {
    for(int i = 0; i < mat.y; i++) {
        for(int j = 0; j < mat.x; j++) {
            if(isAlive(mat, i, j))
                printf("%c ", alive);
            else
                printf("%c ", dead);
        }
        printf("\n");
    }
}

bool isAlive(data mat, int cell_i, int cell_j) {
    //jeżeli podane współrzędne są poza zakresem, to można po prostu potraktować komórkę spoza niego jako martwą
    //pozwoli to ominąć nakładanie ograniczeń w pętlach wewnątrz funkcji związanych z sąsiedztwami
    if(cell_i < 0 || cell_i >= mat.y || cell_j < 0 || cell_j >= mat.x)
        return false;
    int colIterator = 0;
    //najpierw trzeba sprawdzić ilość żywych w wierszu danej komórki
    int aliveInCellsRow = mat.row_index[cell_i+1] - mat.row_index[cell_i];
    if(aliveInCellsRow == 0)
        return false;
    else {
        int aliveInCurrentRow = 0;
        //ustawiamy iterator na odpowiednim przedziale, żeby sprawdzać współrzędne kolumn dla odpowiedniego wiersza
        for(int i = 0; i < cell_i; i++) {
            aliveInCurrentRow = mat.row_index[i+1] - mat.row_index[i];
            colIterator += aliveInCurrentRow;
        }
        //jeżeli współrzędne się pokryły, to znaczy że znaleźliśmy żywą komórkę
        for(int j = colIterator; j < colIterator + aliveInCellsRow; j++)
            if(mat.col_index[j] == cell_j)
                return true;
    }
    //jeżeli wcześniej nie wypluło true, to znaczy że w rzędzie sprawdzanej komórki są jakieś żywe, ale ona sama jest martwa
    return false;
}
/*
void printMooreNextGen(data mat) {
    int colIterator = 0;
    for(int i = 0; i < mat.y) {
        for(int j = 0; j < mat.x; j++) {
            int aliveNeighb = 0; //ilość żywych sąsiadów obecnie sprawdzanej komórki
            for(int ii = i-1; ii < i+1; ii++) {
                for(int jj = j-1; jj < j+1; jj++) {
                    if(ii != i && jj != j && isAlive(ii, jj))
                        aliveNeighb++;
                }
            }
            if(aliveNeighb == 3)
        }
    }
}
*/