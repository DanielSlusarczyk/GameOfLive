test: test.o tgol_file.o tgol_evo.o
	cc test.o tgol_file.o tgol_evo.o -o test -lncurses

tgol_file.o: tgol_file.c
	cc -c tgol_file.c

tgol_evo.o: tgol_evo.c
	cc -c tgol_evo.c

test.o: test.c
	cc -c test.c

debug: test.o tgol_file.o tgol_evo.o
	cc -DDEBUG=true -g test.c tgol_file.c tgol_evo.c -o test -lncurses

clean:
	rm *.o test