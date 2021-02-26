gameoflife.exe: gameoflife.o
	gcc -o gameoflife.exe gameoflife.o
gameoflife.o: gameoflife.c
	gcc -c -o gameoflife.o gameoflife.c
clean:
	rm gameoflife.exe *.o
