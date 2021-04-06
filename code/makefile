test: tgol_main.o tgol_file.o tgol_evo.o tgol_png.o
	cc tgol_main.o tgol_file.o tgol_evo.o tgol_png.o -o TGOL -lpng
	
tgol_png.o: tgol_png.c
	cc -c tgol_png.c -lpng

tgol_file.o: tgol_file.c
	cc -c tgol_file.c

tgol_evo.o: tgol_evo.c
	cc -c tgol_evo.c

tgol_main.o: tgol_main.c
	cc -c tgol_main.c

debug: tgol_main.o tgol_file.o tgol_evo.o tgol_png.o
	cc -DDEBUG=true -g tgol_main.c tgol_file.c tgol_evo.c tgol_png.c -lpng -o TGOL

clean:
	rm *.o *.png *.txt TGOL