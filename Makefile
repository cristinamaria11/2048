build: 2048

2048: 2048.o displayMenu.o game.o
	gcc -Wall 2048.o displayMenu.o game.o -o 2048 -lcurses -lm

2048.o: 2048.c
	gcc -Wall -g -c 2048.c

displayMenu.o: displayMenu.c
	gcc -Wall -g -c displayMenu.c

game.o: game.c
	gcc -Wall -g -c game.c

.PHONY:

clean:
	rm -f *.o *~ 2048

run:
	./2048
