#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <curses.h>
#include "tgol_file.h"
#include "tgol_evo.h"

char dead = '.';
char alive = 'X';

void printMat(t_data mat) {
        int colIterator = 0;
        for(int i = 0; i < mat->y; i++) {
            for(int j = 0; j < mat->x; j++) {
                if(mat->colIndex != NULL) {
                    if(mat->colIndex[colIterator] == j && mat->rowIndex[i + 1] > colIterator) {
                        printf("%c ", alive);
                        colIterator++;
                    }
                    else
                        printf("%c ", dead);
                }
                else
                    printf("%c ", dead);
            }
            printf("\n");
	}
}

t_field addCoordinates(t_data m, t_field lista, int a, int b, bool al) {
    if(a >= 0 && a < m->x && b > 0 && b <= m->y) {
        if(lista == NULL ||(lista->x > a && lista->y <= b) ||(lista->y < b)) {
            t_field n = calloc(1, sizeof(field)); //wyciek
            n->x = a;
            n->y = b;
            n->previousAlive = al;
            n->next = lista; 
            if(al == true) {
                n->previousAlive = true;
                n->neighbors = 0;
            }
            else if(n->previousAlive!=true) {
                n->previousAlive = false;
                n->neighbors = 1;
            }
            return n;
        }
        else if(lista == NULL ||(lista->x == a && lista->y == b)) {
            if(al!=true)
                lista->neighbors++;
            if(lista->previousAlive != true) 
                lista->previousAlive = al;
            return lista;
        }
        else {
            lista->next = addCoordinates(m, lista->next, a, b, al);
            return lista;
        }

    }
    else
        return lista;
}

//tryby: 'm' - sąsiedztwo moore'a, 'n' - sąsiedztwo von
t_data newGeneration(t_data mat, char mode) {
    t_data newMat = calloc(1, sizeof(data));
    newMat->rowLength = mat->y+1;
    newMat->colLength = 0;
    newMat->colIndex = NULL;
    newMat->x = mat->x;
    newMat->y = mat->y;
    newMat->rowIndex = calloc(mat->y + 1, sizeof(int));
    newMat->rowIndex[0] = 0;

    t_field data = NULL;

    for(int i = 0; i < mat->y; i++) {
        for(int j = mat->rowIndex[i]; j < mat->rowIndex[i+1]; j++) {
            //lewo
            data = addCoordinates(mat, data, mat->colIndex[j] - 1, mat->y - i, false);
            //góra
            data = addCoordinates(mat, data, mat->colIndex[j], mat->y - i + 1, false);
            //prawo
            data = addCoordinates(mat, data, mat->colIndex[j] + 1, mat->y - i, false);
            //dół
            data = addCoordinates(mat, data, mat->colIndex[j], mat->y - i - 1, false);
            //środek
            data = addCoordinates(mat, data, mat->colIndex[j], mat->y - i, true);
            if(mode == 'm') {
                //lewo-góra(MOORE)
                data = addCoordinates(mat, data, mat->colIndex[j] - 1, mat->y - i + 1, false);
                //prawo-góra(MOORE)
                data = addCoordinates(mat, data, mat->colIndex[j] + 1, mat->y - i +1, false);
                //prawo-dół(MOORE)
                data = addCoordinates(mat, data, mat->colIndex[j] + 1, mat->y - i - 1, false);
                //lewo-dół(MOORE)
                data = addCoordinates(mat, data, mat->colIndex[j] - 1, mat->y - i - 1, false);
            }
        }
    }
    int* numPerLine = calloc(newMat->y, sizeof(int));
    while(data != NULL) {
        /*
        if(DEBUG)
            printf("(x, y)= ( %d, %d ), sasiadow: %d, wczesniejszy stan: %d  \n", data->x+1, data->y, data->neighbors, data->previousAlive==true ? 1 : 0);
        */
        if((data->previousAlive == true &&(data->neighbors == 2 || data->neighbors == 3)) ||(data->previousAlive == false && data->neighbors == 3)) {
            newMat->colLength++;
            newMat->colIndex = realloc(newMat->colIndex, newMat->colLength * sizeof(int));
            newMat->colIndex[newMat->colLength-1] = data->x;
            numPerLine[mat->y - data->y]++;
        }
        data = data->next;
    }
    free(data);
    int sum = 0;
    for(int i = 1; i <= mat->rowLength; i++) {
        sum += numPerLine[i - 1];
        newMat->rowIndex[i] = sum;
    }
    return newMat;
}

bool CRSEquals(data crs1, data crs2) {
    if(crs1.x != crs2.x || crs1.y != crs2.y || crs1.colLength != crs2.colLength || crs1.rowLength != crs2.rowLength)
        return false;
    for(int i = 0; i < crs1.rowLength; i++) {
        if(crs1.rowIndex[i] != crs2.rowIndex[i])
            return false;
    }
    for(int i = 0; i < crs1.colLength; i++) {
        if(crs1.colIndex[i] != crs2.colIndex[i])
            return false;
    }
    return true;
}