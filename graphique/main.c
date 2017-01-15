/**
 * @file      main.c
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 Décembre 2016
 * @brief     ~
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "init.h"


int main( int argc, char *argv[] ){

	/*INITIALISATION LIBS*/
	if(TTF_Init() == -1 || SDL_Init(SDL_INIT_VIDEO) == -1)
		exit(EXIT_FAILURE);
	printf("ok libs\n");
	/*VARIABLES */

	SDL_Surface *ecran = SDL_SetVideoMode(LARGEUR_F, HAUTEUR_F, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("StarWars Battleship !", NULL);

	if (ecran == NULL) {
        fprintf(stderr, "Erreur de chargement vidéo");
        exit(EXIT_FAILURE);
    }

	/*COULEURS*/
	Uint32 bleuFonce = SDL_MapRGB(ecran->format, 31, 97, 97);
	Uint32 bleu = SDL_MapRGB(ecran->format, 91, 198, 198);
	Uint32 colors[2]= {bleuFonce,bleu};

	printf("ok variables\n");

	/*AFFICHAGE ECRANS*/
	int choix = 0;
	/*tq le joueur ne veut pas quiter le programme ou n'a pas terminé le jeu, on affiche l'écran d'accueil*/
	do {
		choix = welcome_screen(ecran,colors);
		if (choix == 1)
		{
			game_screen(ecran,colors);
			choix = -1;
		}
		else if (choix == 2)
		{
			game_screen(ecran,colors);
			choix = -1;
		}
		else if (choix == 3)
		{
			rules_screen(ecran);
			choix = 0;
			
		}
	}while(choix != -1);

 	/*FREE MALLOC + FERMETURE LIBS*/


    SDL_Quit();
    TTF_Quit();

    return EXIT_SUCCESS;

}