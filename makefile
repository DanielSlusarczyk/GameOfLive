errtest: errtest.o tgol_file.o
	cc errtest.o tgol_file.o -o errtest

tgol_file.o: tgol_file.c
	cc -c tgol_file.c

errtest.o: errtest.c
	cc -c errtest.c

clean:
	rm *.o errtest