# makefile de base correspondant a l'exercice 2, TP8


mon_executable: main.o fonctions.o
		gcc -o mon_executable main.o fonctions.o

monmain.o: main.c fonctions.h
	gcc -o main.o -c main.c -Wall -ansi

mesfonctions.o: fonctions.c fonctions.h
	     gcc -o fonctions.o -c fonctions.c -Wall -ansi