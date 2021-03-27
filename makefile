errtest: errtest.o tgol_file.o tgol_evo.o
	cc errtest.o tgol_file.o tgol_evo.o -o errtest

tgol_file.o: tgol_file.c
	cc -c tgol_file.c

tgol_evo.o: tgol_evo.c
	cc -c tgol_evo.c

errtest.o: errtest.c
	cc -c errtest.c

clean:
	rm *.o errtest