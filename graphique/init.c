/**
 * @file      init.c
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 Décembre 2016
 * @brief     Définis les structures et les méthodes du jeu
 * @details    ~
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "init.h"


int get_grid_index(int x_position, int y_position, int *index_row, int *index_cols){
	int i,j;
	printf("x position %d et y position %d\n",x_position,y_position );
	for (i = 0; i < 10; i++)
	{
		/*printf("TAILLE_CELL*(i+1) = %d et TAILLE_CELL*(i+2) = %d\n",TAILLE_CELL*(i+1),TAILLE_CELL*(i+2) );*/
		if(x_position>=TAILLE_CELL*(i+1) && x_position<TAILLE_CELL*(i+2))
		{
			/*printf("ok col (x) FOUND !\n");*/
			for (j = 0; j < 10; j++)
			{
				/*printf("TAILLE_CELL*(j+1) = %d et TAILLE_CELL*(j+2) = %d\n",TAILLE_CELL*(j+1),TAILLE_CELL*(j+2) );*/
				if(y_position>=TAILLE_CELL*(j+1) && y_position<TAILLE_CELL*(j+2))
				{
					/*printf("ok ligne (y) FOUND ! \n");*/
					(*index_row) = j;
					(*index_cols) = i;
					return EXIT_SUCCESS;
				}

			}
		}
	}

	return EXIT_FAILURE;
}

void welcome_screen(SDL_Surface * ecran, Uint32 colors[]){
	SDL_Rect position;
	position.x=(LARGEUR_F/2)-(LARGEUR_BUTTON/2);
	position.y=((HAUTEUR_F/3)/2)-(HAUTEUR_BUTTON/2);

	SDL_Surface *modeJoVsJO = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_BUTTON, HAUTEUR_BUTTON, 32, 0, 0, 0, 0);
	SDL_Surface *modeIA = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_BUTTON, HAUTEUR_BUTTON, 32, 0, 0, 0, 0);
	SDL_Surface *rules = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_BUTTON, HAUTEUR_BUTTON, 32, 0, 0, 0, 0);

	SDL_WM_SetCaption("StarWars Battleship !", NULL);

	SDL_FillRect(ecran, NULL, colors[0]);
	SDL_FillRect(modeJoVsJO, NULL, colors[1]);
	SDL_FillRect(modeIA, NULL, colors[1]);
	SDL_FillRect(rules, NULL, colors[1]);

	SDL_BlitSurface(modeJoVsJO, NULL, ecran, &position);
	position.y=((2*(HAUTEUR_F/3))/2)-(HAUTEUR_BUTTON/2);
	SDL_BlitSurface(modeIA, NULL, ecran, &position);
	position.y=((3*(HAUTEUR_F/3))/2)-(HAUTEUR_BUTTON/2);
	SDL_BlitSurface(rules, NULL, ecran, &position);

	SDL_Flip(ecran); 															
	pause(ecran);
}

void rules_screen(SDL_Surface * ecran){


}

void game_screen(SDL_Surface * ecran){


}

void stroke_screen(SDL_Surface * ecran){


}

void pause(SDL_Surface *ecran){
	int continuer = 1, x,y,res,ind_cols,ind_rows;
	SDL_Event event;

	SDL_Rect position;

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
		            case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
						continuer = 0;
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT){
					x=event.button.x;
					y=event.button.y;
					if(x>TAILLE_CELL && x<TAILLE_CELL+(10*TAILLE_CELL) && y>TAILLE_CELL && y<TAILLE_CELL+(10*TAILLE_CELL)){
						res = get_grid_index(x,y,&ind_rows,&ind_cols);
						printf("GRID TOUUUUUCH %d\n",res);
					}
				}
				break;
		}
	}
}