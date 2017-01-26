# makefile de base correspondant a l'exercice 2, TP8


battleship: main.o init.o game.o ia.o
	gcc -o battleship main.o init.o game.o ia.o

main.o: main.c init.h game.h ia.h
	gcc -o main.o -c main.c -Wall -ansi

init.o: init.c init.h ia.h
	gcc -o init.o -c init.c -Wall -ansi

game.o: game.c game.h ia.h init.h
	gcc -o game.o -c game.c -Wall -ansi

ia.o: ia.c ia.h game.h init.h
	gcc -o ia.o -c ia.c -Wall -ansi