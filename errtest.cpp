#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "tgol_file.h"

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");
    FILE* outFile = NULL;
    bool sbs = false;
    bool save = false;
    bool overwrite = false;
    bool refresh = false;

    if (argc < DEFAULT_ARGC) {
        printf("%s\n", Errors[INCORRECT_NUMBER_OF_ARGS - 1]);
        return INCORRECT_NUMBER_OF_ARGS;
    }
    if (inFile == NULL) {
        printf("%s\n", Errors[FILE_OPEN_ERR - 1]);
        return FILE_OPEN_ERR;
    }

    if (atoi(argv[2]) <= 0) {
        printf("%s\n", Errors[INCORRECT_GENS - 1]);
        return INCORRECT_GENS;
    }

    int n = DEFAULT_ARGC;
    while (n < argc) {
        if (argv[n][0] != '-') {
            printf("%s\n", Errors[UNKNOWN_FLAG - 1]);
            return UNKNOWN_FLAG;
        }
        else {
            if (!contains(knownFlags, argv[n])) {
                printf("%s\n", Errors[UNKNOWN_FLAG - 1]);
                return UNKNOWN_FLAG;
            }
            else if (strcmp(argv[n], "-sbs") == 0) sbs = true;
            else if (strcmp(argv[n], "-save") == 0) {
                if (overwrite) {
                    printf("%s\n", Errors[AMBIGUOUS_OUT - 1]);
                    return AMBIGUOUS_OUT;
                }
                save = true;
                if (argv[n + 1][0] != '-') {
                    outFile = fopen(argv[n + 1], "w");
                    if (outFile == NULL) {
                        printf("%s\n", Errors[NO_OUT - 1]);
                        return NO_OUT;
                    }
                    n++;
                }
                else {
                    printf("%s\n", Errors[NO_OUT - 1]);
                    return NO_OUT;
                }
            }
            else if (strcmp(argv[n], "-overwrite") == 0) {
                if (save) {
                    printf("%s\n", Errors[AMBIGUOUS_OUT - 1]);
                    return AMBIGUOUS_OUT;
                }
                overwrite = true;
            }
            else if (strcmp(argv[n], "-refresh") == 0)
                refresh = true;
        }
        n++;
    }

    data mat;
    ErrorCode errCode = read_file(inFile, &mat);
    if (errCode != COR) {
        printf("%s\n", Errors[errCode - 1]);
        return errCode;
    }
    t_data matrix = &mat;
    printf("Wczytana generacja:\n");
    write_generation(matrix);
    if (DEBUG) {
        printf("Wymiary: %d x %d\n", mat.y, mat.x);
        printf("Col_index [ ");
        for (int i = 0; i < mat.col_length; i++)
            printf("%d ", mat.col_index[i]);
        printf("]\n");
        printf("Row_index [ ");
        for (int i = 0; i < mat.row_length; i++)
            printf("%d ", mat.row_index[i]);
        printf("]\n");
    }
    if (overwrite) {
        fclose(inFile);
        outFile = fopen(argv[1], "w");
        fprintf(outFile, "%s", "udało się nadpisać plik\n");
    }
    if (save) {
        fprintf(outFile, "%s", "udało się zapisać do pliku\n");
    }
    if (!DEBUG) {
        Sleep(1000);
        system("cls");
    }
    //Przeprowadzanie wszystkich generacji
    for (int i = 0; i < atoi(argv[2]); i++) {
        matrix = new_generation(matrix);
        write_generation(matrix);
        if (!DEBUG) {
            system("pause");
            system("cls");
        }
        if (DEBUG) {
            printf("Wymiary: %d x %d\n", matrix->y, matrix->x);
            printf("Col_index [ ");
            for (int i = 0; i < matrix->col_length; i++)
                printf("%d ", matrix->col_index[i]);
            printf("]\n");
            printf("Row_index [ ");
            for (int i = 0; i < matrix->row_length; i++)
                printf("%d ", matrix->row_index[i]);
            printf("]\n");
        }
    }
    return 0;
}

bool contains(const char** array, char* s) {
    bool ret = false;
    int lim = sizeof(knownFlags) / sizeof(const char*);
    for (int i = 0; i < lim; i++) {
        if (strcmp(array[i], s) == 0)
            ret = true;
    }
    return ret;
}

void write_generation(t_data mat) {
        int ite_col = 0;
        for (int i = 0; i < mat->y; i++) {
            for (int j = 0; j < mat->x; j++) {
                if (mat->col_index != NULL) {
                    if (mat->col_index[ite_col] == j && mat->row_index[i + 1] > ite_col) {
                        printf("x ");
                        ite_col++;
                    }
                    else
                        printf("0 ");
                }
                else
                    printf("0 ");
            }
            printf("\n");
        }
        printf("\n");
}


t_field add_coordinates(t_data m, t_field lista, int a, int b, bool al) {
    if (a >= 0 && a < m->x && b > 0 && b <= m->y) {
        if (lista == NULL || (lista->x > a && lista->y <= b) || (lista->y < b)) {
            t_field n = (t_field)malloc(sizeof(field));
            n->x = a;
            n->y = b;
            n->previous_alive = al;
            n->next = lista; 
            if (al == true) {
                n->previous_alive = true;
                n->neighbors = 0;
            }
            else if (n->previous_alive!=true) {
                n->previous_alive = false;
                n->neighbors = 1;
            }
            return n;
        }
        else if (lista == NULL || (lista->x == a && lista->y == b)) {
            if(al!=true)
                lista->neighbors++;
            if (lista->previous_alive != true) 
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

    for (int i = 0; i < mat->y; i++) {
        for (int j = mat->row_index[i]; j < mat->row_index[i + 1]; j++) {
            //lewo
            data = add_coordinates(mat, data, mat->col_index[j] -1, mat->y - i, false);
            //lewo-góra (MOORE)
            data = add_coordinates(mat, data, mat->col_index[j] - 1, mat->y - i + 1, false);
            //góra
            data = add_coordinates(mat, data, mat->col_index[j], mat->y - i + 1, false);
            //prawo-góra (MOORE)
            data = add_coordinates(mat, data, mat->col_index[j] + 1, mat->y - i +1, false);
            //prawo
            data = add_coordinates(mat, data, mat->col_index[j] + 1, mat->y - i, false);
            //prawo-dół (MOORE)
            data = add_coordinates(mat, data, mat->col_index[j] + 1, mat->y - i - 1, false);
            //dół
            data = add_coordinates(mat, data, mat->col_index[j], mat->y - i - 1, false);
            //lewo-dół (MOORE)
            data = add_coordinates(mat, data, mat->col_index[j] - 1, mat->y - i - 1, false);
            //środek
            data = add_coordinates(mat, data, mat->col_index[j], mat->y - i, true);
        }
    }
    int* numPerLine = (int*)calloc(new_mat->y, sizeof(int));
    while (data != NULL) {
        if(DEBUG)
            printf("(x, y)=( %d, %d ), sasiadow: %d, wczesniejszy stan: %d  \n", data->x+1, data->y, data->neighbors, data->previous_alive==true ? 1 : 0);
        if ((data->previous_alive == true && (data->neighbors == 2 || data->neighbors == 3)) || (data->previous_alive == false && data->neighbors == 3)) {
            new_mat->col_length++;
            new_mat->col_index = (int*)realloc(new_mat->col_index, new_mat->col_length * sizeof(int));
            new_mat->col_index[new_mat->col_length - 1] = data->x;
            numPerLine[mat->y - data->y]++;
        }
        data = data->next;
    }
    int sum = 0;
    for (int i = 1; i <= mat->row_length; i++) {
        sum += numPerLine[i - 1];
        new_mat->row_index[i] = sum;
    }
    return new_mat;
}