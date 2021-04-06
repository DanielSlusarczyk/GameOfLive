#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <png.h>
#include "tgol_file.h"
#include "tgol_png.h"

void generateImg(char* file_name, t_data mat) {
  int width_x = mat->x;
  int heigh_y = mat->y;
  int sideLength = width_x > heigh_y ? (MAXDIM - MAXDIM % width_x)/width_x : (MAXDIM - MAXDIM % heigh_y)/heigh_y;
  makeImg(sideLength, mat);
  writeImg(file_name, mat->y * sideLength);
}

void makeImg(int sideLength, t_data mat) {
  width = sideLength * mat->x;
  height = sideLength * mat->y;
  bit_depth = 8;
  color_type = PNG_COLOR_TYPE_GRAY;

  number_of_passes = 7;
  row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * (mat->y * sideLength));
  for(y = 0; y < (mat->y * sideLength); y++) {
	  row_pointers[y] = (png_byte*)malloc(sizeof(png_byte) * (mat->x * sideLength));
  }

  for(int i = 0; i < mat->y; i++) {
    int* tmp = (int*)calloc((mat->rowIndex[i + 1] - mat->rowIndex[i] + 1), sizeof(int));
    for(int k = mat->rowIndex[i]; k < mat->rowIndex[i + 1]; k++){
      tmp[k - mat->rowIndex[i]] = mat->colIndex[k];
    }
    for(int p = i * sideLength; p < (i + 1) * sideLength; p++){
      int colIte = 0;
      int t;
      int tt = 0;
      png_byte* row = row_pointers[p];
      for(int q = 0; q < mat->x * sideLength; q++){
		t = ((q - (q % sideLength))/sideLength);
		if(t == tmp[colIte] && colIte < (mat->rowIndex[i + 1] - mat->rowIndex[i])){
			tt++;
			row[q] = 0;
			if(tt == sideLength){
				if(colIte < (mat->rowIndex[i + 1] - mat->rowIndex[i])) {
					colIte++;
				}
				tt = 0;
			}
		}
		else {
			row[q] = 255;
		}
      }
    }
    free(tmp);  
  }
}
void writeImg(char* file_name, int rowPtrLim) {
  FILE *fp = fopen(file_name, "wb");
  if(fp == NULL) {
	  printf("writeImg: Plik %s nie może zostać otwarty do zapisu\n", file_name);
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png_ptr) {
	  printf("writeImg: błąd funkcji png_create_write_struct\n");
  }

  info_ptr = png_create_info_struct(png_ptr);
  if(!info_ptr) {
	  printf("writeImg: błąd funkcji png_create_info_struct\n");
  }

  if(setjmp(png_jmpbuf(png_ptr))) {
	  printf("writeImg: błąd podczas inicjalizacji\n");
  }

  png_init_io(png_ptr, fp);
  if(setjmp(png_jmpbuf(png_ptr))) {
	  printf("writeImg: błąd podczas zapisu nagłówka\n");
  }

  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
  png_write_info(png_ptr, info_ptr);
  if(setjmp(png_jmpbuf(png_ptr))) {
	  printf("writeImg: błąd podczas zapisu poszczególnych bajtów");
  }

  png_write_image(png_ptr, row_pointers);
  for(int i = 0; i < rowPtrLim; i++) {
	free(row_pointers[i]);
  }
  free(row_pointers);

  if(setjmp(png_jmpbuf(png_ptr))) {
	  printf("writeImg: błąd końca zapisu");
  }
  
  png_write_end(png_ptr, NULL);
  fclose(fp);
}