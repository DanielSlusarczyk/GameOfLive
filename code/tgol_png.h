#ifndef _TGOLPNG
#define _TGOLPNG

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <png.h>
#include "tgol_file.h"

#define MAXDIM 1000
int x, y;
int width, height;
png_byte color_type;
png_byte bit_depth;
png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep* row_pointers;



void generateImg(int, int, char*, t_data);
void makeImg(int, t_data);
void writeImg(char*);


#endif
