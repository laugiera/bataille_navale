#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "test_fct.h"

void pause();

int main(int argc, char *argv[])
{
	/*Uint32 jaune = SDL_MapRGB(Uint32, 255, 255, 0);*/
	SDL_Surface *ecran = NULL;
    if (TTF_Init() == -1 || SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    if (ecran == NULL) {
        fprintf(stderr, "Erreur de chargement vidéo");
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("DeathStar Battleship!!!! YISS", NULL);
    /*SDL_FillRect(ecran, NULL, jaune);*/
    printf("%s\n", ecran->format);

    pause();
    
    SDL_Quit();
    TTF_Quit();
 
    return EXIT_SUCCESS;
}



/*
ligne de compliation : 
gcc test_graphique.c /Library/Frameworks/SDL.framework/Headers/SDLmain.m -framework SDL -framework Cocoa

#nom de l'exécutable final
EXEC    = battleshipMac
#objets nécessaires pour l'exécutable final
OBJS    = ./bin/main.o ./bin/init.o ./bin/SDLMain.o
#compilateur a utiliser
CC      = gcc
#options de compilation C
CFLAGS  = -ansi -pedantic -Wall `sdl-config --cflags`
#options d'édition de liens
LDFLAGS = `sdl-config --libs`
#si on est sur Mac OS X, on précise à GCC qu'il doit compiler en i386


ifeq ($(strip $(shell uname -s)),Darwin)
	CC  += -arch i386
endif


#La règle principale a pour seule dépendance l'exécutable final.
all: ${EXEC}

#règle de construction de l'exécutable final
${EXEC}: ${OBJS}
	${CC} ${LDFLAGS} -o $@ $^

#création du répertoire bin
bin:
	mkdir -p ./bin

#construction spécifique de SDLMain
./bin/SDLMain.o: /Library/Frameworks/SDL.framework/Headers/SDLmain.m bin
	${CC} ${CFLAGS} -g -c -o $@ $<

#construction d'un fichier objet dans bin
./bin/%.o: %.c init.h bin
	${CC} ${CFLAGS} -g -c -o $@ $<

clean:
	rm -f ./bin/*.o

very-clean: clean
	rm -f ${EXEC}
	rm -rf bin
*/