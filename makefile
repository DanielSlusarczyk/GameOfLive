gol: gameoflife.o
	gcc -o gol gameoflife.o
gameoflife.o: gameoflife.c
	gcc -c -o gameoflife.o gameoflife.c
clean:
	rm gol *.o