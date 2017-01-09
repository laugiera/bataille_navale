# makefile de base correspondant a l'exercice 2, TP8


battleship: main.o init.o game.o
		gcc -o battleship main.o init.o game.o

main.o: main.c init.h game.h
	gcc -o main.o -c main.c -Wall -ansi

init.o: init.c init.h
	     gcc -o init.o -c init.c -Wall -ansi

game.o: game.c game.h
	     gcc -o game.o -c game.c -Wall -ansi