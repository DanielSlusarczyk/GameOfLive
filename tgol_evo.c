#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <curses.h>
#include "tgol_file.h"
#include "tgol_evo.h"

char dead = '.';
char alive = 'O';

<<<<<<< HEAD
void print_generation(t_data mat) {
        int ite_col = 0;
        for(int i = 0; i < mat->y; i++) {
            for(int j = 0; j < mat->x; j++) {
                if(mat->col_index != NULL) {
                    if(mat->col_index[ite_col] == j && mat->row_index[i + 1] > ite_col) {
                        printf("%c ", alive);
                        ite_col++;
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

t_field add_coordinates(t_data m, t_field lista, int a, int b, bool al) {
    if(a >= 0 && a < m->x && b > 0 && b <= m->y) {
        if(lista == NULL ||(lista->x > a && lista->y <= b) ||(lista->y < b)) {
            t_field n = (t_field)malloc(sizeof(field));
            n->x = a;
            n->y = b;
            n->previous_alive = al;
            n->next = lista; 
            if(al == true) {
                n->previous_alive = true;
                n->neighbors = 0;
            }
            else if(n->previous_alive!=true) {
                n->previous_alive = false;
                n->neighbors = 1;
            }
            return n;
        }
        else if(lista == NULL ||(lista->x == a && lista->y == b)) {
            if(al!=true)
                lista->neighbors++;
            if(lista->previous_alive != true) 
                lista->previous_alive = al;
            return lista;
        }
        else {
            lista->next = add_coordinates(m, lista->next, a, b, al);
            return lista;
        }

    }
    else
        return lista;
}

t_data new_generation(t_data mat) {
    t_data new_mat = (t_data)malloc(sizeof(data));
    new_mat->row_length = mat->y+1;
    new_mat->col_length = 0;
    new_mat->col_index = NULL;
    new_mat->x = mat->x;
    new_mat->y = mat->y;
    new_mat->row_index = (int*)malloc((mat->y + 1) * sizeof(int));
    new_mat->row_index[0] = 0;

    t_field data = NULL;

    for(int i = 0; i < mat->y; i++) {
        for(int j = mat->row_index[i]; j < mat->row_index[i + 1]; j++) {
            //lewo
            data = add_coordinates(mat, data, mat->col_index[j] -1, mat->y - i, false);
            //lewo-góra(MOORE)
            data = add_coordinates(mat, data, mat->col_index[j] - 1, mat->y - i + 1, false);
            //góra
            data = add_coordinates(mat, data, mat->col_index[j], mat->y - i + 1, false);
            //prawo-góra(MOORE)
            data = add_coordinates(mat, data, mat->col_index[j] + 1, mat->y - i +1, false);
            //prawo
            data = add_coordinates(mat, data, mat->col_index[j] + 1, mat->y - i, false);
            //prawo-dół(MOORE)
            data = add_coordinates(mat, data, mat->col_index[j] + 1, mat->y - i - 1, false);
            //dół
            data = add_coordinates(mat, data, mat->col_index[j], mat->y - i - 1, false);
            //lewo-dół(MOORE)
            data = add_coordinates(mat, data, mat->col_index[j] - 1, mat->y - i - 1, false);
            //środek
            data = add_coordinates(mat, data, mat->col_index[j], mat->y - i, true);
        }
    }
    int* numPerLine = (int*)calloc(new_mat->y, sizeof(int));
    while(data != NULL) {
        if(DEBUG)
            printf("(x, y)= ( %d, %d ), sasiadow: %d, wczesniejszy stan: %d  \n", data->x+1, data->y, data->neighbors, data->previous_alive==true ? 1 : 0);
        if((data->previous_alive == true &&(data->neighbors == 2 || data->neighbors == 3)) ||(data->previous_alive == false && data->neighbors == 3)) {
            new_mat->col_length++;
            new_mat->col_index = (int*)realloc(new_mat->col_index, new_mat->col_length * sizeof(int));
            new_mat->col_index[new_mat->col_length - 1] = data->x;
            numPerLine[mat->y - data->y]++;
        }
        data = data->next;
    }
    int sum = 0;
    for(int i = 1; i <= mat->row_length; i++) {
        sum += numPerLine[i - 1];
        new_mat->row_index[i] = sum;
    }
    return new_mat;
}
