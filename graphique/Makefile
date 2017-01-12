# makefile de base correspondant a l'exercice 2, TP8


battleship: main.o init.o game.o
	gcc `sdl-config --libs` -lSDL_ttf -o battleship main.o init.o game.o

main.o: main.c init.h game.h
	gcc `sdl-config --cflags --libs` -lSDL_ttf -o main.o -c main.c -Wall -ansi

init.o: init.c init.h
	gcc `sdl-config --cflags --libs` -lSDL_ttf -o init.o -c init.c -Wall -ansi

game.o: game.c game.h
	gcc `sdl-config --cflags --libs` -lSDL_ttf -o game.o -c game.c -Wall -ansi