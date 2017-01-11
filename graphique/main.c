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
#include "init.h"


int main( int argc, char *argv[] ){

	/*INITIALISATION LIBS*/
	if(TTF_Init() == -1 || SDL_Init(SDL_INIT_VIDEO) == -1)
		exit(EXIT_FAILURE);
	printf("ok libs\n");
	/*VARIABLES */
	TTF_Font *police = NULL;

	SDL_Surface *ecran = SDL_SetVideoMode(LARGEUR_F, HAUTEUR_F, 32, SDL_HWSURFACE);
	SDL_Surface *grid[10][10];
	SDL_Surface *texte = NULL;
	SDL_Surface *cols[10] = {NULL};
	SDL_Surface *rows[10] = {NULL};

	SDL_Rect position;

	Uint32 bleuFonce = SDL_MapRGB(ecran->format, 31, 97, 97);
	Uint32 bleu = SDL_MapRGB(ecran->format, 91, 198, 198);
	Uint32 colors[2]= {bleuFonce,bleu};
	SDL_Color couleurNoire = {0, 0, 0};

	police = TTF_OpenFont("polices/Starjout.ttf", 30);
	printf("ok variables\n");
	/*Initialisation écran*/
	welcome_screen(ecran,colors);
	SDL_Flip(ecran); /* Mise à jour de l'écran*/

	

   /* // Allocation de la surface
	int i,j;
	char string [80];
	position.x=TAILLE_CELL;
	position.y=0;
	printf("Init ok\n");
	for (i = 0; i < 10; i++)
	{
		sprintf(string,"%d",i);
		cols[i] = TTF_RenderText_Blended(police, string, couleurNoire);
    	SDL_BlitSurface(cols[i], NULL, ecran, &position); *
		position.x += TAILLE_CELL;
	}
	position.x=0;
	position.y=TAILLE_CELL;
	for (i = 0; i < 10; i++)
	{		
		sprintf(string,"%c",'A'+i);
		rows[i] = TTF_RenderText_Blended(police, string, couleurNoire);
    	SDL_BlitSurface(rows[i], NULL, ecran, &position); *
		position.y += TAILLE_CELL;	
	}
	position.y =TAILLE_CELL;
	position.x = TAILLE_CELL;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{

			grid[i][j]=SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_CELL, TAILLE_CELL, 32, 0, 0, 0, 0);
			SDL_FillRect(grid[i][j], NULL, colors[(j+i)%2]); 
			SDL_BlitSurface(grid[i][j], NULL, ecran, &position); 
			position.y += TAILLE_CELL;
		}
		position.x += TAILLE_CELL;
		position.y = TAILLE_CELL;
	}
	printf("Grid ok\n");
*
	texte = TTF_RenderText_Blended(police, "Hello worldeuh !", couleurNoire);
	position.x = 160;
	position.y = 670;
    SDL_BlitSurface(texte, NULL, ecran, &position); *

    SDL_Flip(ecran); // Mise à jour de l'écran
    pause(ecran,texte);

    for (i = 0; i < 10; i++)
    {
    	for (j = 0; j < 10; j++)
    		SDL_FreeSurface(grid[i][j]); // Libération de la surface

    }

    SDL_FreeSurface(texte);  */                                               
    SDL_Quit();

    TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
    TTF_Quit();

    return EXIT_SUCCESS;

}