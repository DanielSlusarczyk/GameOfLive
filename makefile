tgol: gameoflife.o
	gcc -o tgol gameoflife.o
gameoflife.o: gameoflife.c
	gcc -c -o gameoflife.o gameoflife.c
clean:
	rm gol *.o