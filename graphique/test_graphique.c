#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"

void pause();

int main(int argc, char *argv[])
{
	/*Uint32 jaune = SDL_MapRGB(Uint32, 255, 255, 0);*/
	SDL_Surface *ecran = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
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
 
    return EXIT_SUCCESS;
}

void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}


/*
ligne de compliation : 
gcc test_graphique.c /Library/Frameworks/SDL.framework/Headers/SDLmain.m -framework SDL -framework Cocoa
*/