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
#include <SDL/SDL_image.h>
#include "init.h"

/**
 * @brief      retourne l'index d'une case cliquée dans la grille de jeu
 * @param      int x_position, y_position, les coordonnées de la souris au moment du clic
 * @param      int *index_row, int* index_cols les indexs correspondant à la case cliquée (pas de convertion ascii)
 * @details    Attention : rows correspondant à x et cols à y !
 * @return     int	
 */
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
/**
 * @brief      écran d'accueil avec trois boutons : mode solo (IA) | mode multi (2 joueurs) | rules
 * @param      SDL_Surface * ecran
 * @param      Uint32 colors[]	les couleurs définies dans le main
 * @return     int choix de l'écran qui suivra
 */
int welcome_screen(SDL_Surface *ecran, Uint32 colors[]){

	printf("Welcome screen\n");
	SDL_Rect position;
	position.x=0;
	position.y=0;
	/*
	SDL_Surface *background = IMG_Load("img/fondACCUEIL.png");
	SDL_Surface *modeJoVsJO = IMG_Load("img/multi.png");
	SDL_Surface *modeIA = IMG_Load("img/solo.png");
	SDL_Surface *rules = IMG_Load("img/rules.png");
	*/
	/*RGB SURFACES pour que Lou puisse faire des trucs*/
	SDL_Surface *background = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_F, HAUTEUR_F, 32, 0, 0, 0, 0);
	SDL_Surface *modeJoVsJO = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_BUTTON, HAUTEUR_BUTTON, 32, 0, 0, 0, 0);
	SDL_Surface *modeIA = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_BUTTON, HAUTEUR_BUTTON, 32, 0, 0, 0, 0);
	SDL_Surface *rules = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_BUTTON, HAUTEUR_BUTTON, 32, 0, 0, 0, 0);
	SDL_FillRect(background, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
	SDL_FillRect(modeJoVsJO, NULL, SDL_MapRGB(ecran->format, 100, 70, 200));
	SDL_FillRect(modeIA, NULL, SDL_MapRGB(ecran->format, 100, 70, 200));
	SDL_FillRect(rules, NULL, SDL_MapRGB(ecran->format, 100, 70, 200));
	/*FIN DES SURFACES (commenter pour travailler avec imgs*/

	/*alors visiblement j'ai une sorte de bug qui fait fait que tant qu'on a jamais fait de pause_welcome_screen il vaut pas afficher le welcome screen
	-chercher ce qui fait le déclic ds la fct 
	*/
	pause_welcome_screen(ecran);


	printf("fin premier pause\n");
	SDL_BlitSurface(background,NULL,ecran,&position);
	position.x=(LARGEUR_F/2)-(LARGEUR_BUTTON/2);
	position.y=300;
	SDL_BlitSurface(modeIA, NULL, ecran, &position);
	position.y=450;
	SDL_BlitSurface(modeJoVsJO, NULL, ecran, &position);
	position.y=600;
	SDL_BlitSurface(rules, NULL, ecran, &position);

	SDL_Flip(ecran); 
	/*on attend que le joueur clique sur un des trois boutons*/															
	int choix = pause_welcome_screen(ecran);
	SDL_FreeSurface(background);
	SDL_FreeSurface(modeIA);
	SDL_FreeSurface(modeJoVsJO);
	SDL_FreeSurface(rules);
	printf("choix : %d\n", choix);
	return choix;
}
/**
 * @brief      Ecran qui affiche les règles
 * @param      SDL_Surface * ecran
 * @details    La fonction attend que le joueur clique sur le bouton ok
 * @return     void
 */
void rules_screen(SDL_Surface * ecran){
	printf("rules screen\n");
	SDL_Rect position;
	position.x=0;
	position.y=0;
	/* IMAGES pour le reste du monde
	SDL_Surface *background = IMG_Load("img/fondACCUEIL.png");
	SDL_Surface *retour = IMG_Load("img/multi.png");
	*/
	/*SURFACES pour Lou*/
	SDL_Surface *background = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_F, HAUTEUR_F, 32, 0, 0, 0, 0);
	SDL_Surface *retour = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_BUTTON, HAUTEUR_BUTTON, 32, 0, 0, 0, 0);
	SDL_FillRect(background, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
	SDL_FillRect(retour, NULL, SDL_MapRGB(ecran->format, 100, 70, 200));
	/*Fin des surfaces*/

	SDL_BlitSurface(background,NULL,ecran,&position);
	
	position.x=LARGEUR_F-LARGEUR_BUTTON-30;
	position.y=30;
	SDL_BlitSurface(retour, NULL, ecran, &position);

	SDL_Flip(ecran); 													
	pause_simple_screen(ecran);

	SDL_FreeSurface(background);
	SDL_FreeSurface(retour);

}
/**
 * @brief      Ecran de jeu
 * @param      SDL_Surface * ecran
 * @return     void
 */
void game_screen(SDL_Surface * ecran, Uint32 colors[]){

	/*VARIABLES*/
	SDL_Surface *grid[10][10];
	SDL_Surface *cols[10] = {NULL};
	SDL_Surface *rows[10] = {NULL};

	SDL_Rect position;

	int ind_cols, ind_rows;

	TTF_Font *police = NULL;
	police = TTF_OpenFont("polices/Starjout.ttf", 30);

	SDL_Color couleurNoire = {0, 0, 0};

	 
	int i,j;
	char string [80];
	int continuer =1;

	while(continuer != -1) /*condition à changer*/
	{
			/*ALLOC SURFACES*/
			position.x=TAILLE_CELL;
			position.y=0;

			SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
			for (i = 0; i < 10; i++)
			{
				sprintf(string,"%d",i);
				cols[i] = TTF_RenderText_Blended(police, string, couleurNoire);
		    	SDL_BlitSurface(cols[i], NULL, ecran, &position); /* Blit du texte */
				position.x += TAILLE_CELL;
			}
			position.x=0;
			position.y=TAILLE_CELL;
			for (i = 0; i < 10; i++)
			{		
				sprintf(string,"%c",'A'+i);
				rows[i] = TTF_RenderText_Blended(police, string, couleurNoire);
		    	SDL_BlitSurface(rows[i], NULL, ecran, &position); /* Blit du texte */
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
			printf("Init Grid ok\n");

			SDL_Flip(ecran);

			/*GAME*/
			/*on attend que le joueur choisisse une case*/
			continuer = pause_game(ecran, &ind_cols, &ind_rows);
			/*on affiche le résultat de la case*/
			if(continuer != -1)
				stroke_screen(ecran, ind_cols, ind_rows);

	}


	/*FREE SURFACES*/
	for (i = 0; i < 10; i++)
    {
    	for (j = 0; j < 10; j++)
    		SDL_FreeSurface(grid[i][j]); 

    }
    for (i = 0; i < 10; i++)
    	SDL_FreeSurface(rows[i]);
    for (i = 0; i < 10; i++)
    	SDL_FreeSurface(cols[i]);

    TTF_CloseFont(police); /* Doit être avant TTF_Quit() */

}
/**
 * @brief      Ecran qui affiche le resultat d'un coup joué 
 * @param      SDL_Surface * ecran
 * @details    La fonction attend que le joueur clique sur le bouton ok
 * @return     void
 */
void stroke_screen(SDL_Surface * ecran, int cols, int rows){
	SDL_Rect position;
	position.x=0;
	position.y=0;

	char string[80];

	TTF_Font *police = NULL;
	police = TTF_OpenFont("polices/Starjout.ttf", 30);

	SDL_Color couleurBlanc = {255, 255, 255};

	SDL_Surface *background = IMG_Load("img/fondACCUEIL.png");
	SDL_Surface *retour = IMG_Load("img/multi.png");

	SDL_BlitSurface(background,NULL,ecran,&position);
	
	position.x=LARGEUR_F-LARGEUR_BUTTON-30;
	position.y=30;
	SDL_BlitSurface(retour, NULL, ecran, &position);

	sprintf(string,"CASE : %c %d",'A'+rows,cols);
	SDL_Surface *texte = TTF_RenderText_Blended(police, string, couleurBlanc);
	position.x = (LARGEUR_F/2)-(LARGEUR_BUTTON/2);
	position.y = (HAUTEUR_F/2)-(HAUTEUR_BUTTON/2);
    SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */

	SDL_Flip(ecran); 															
	pause_simple_screen(ecran);

	SDL_FreeSurface(background);
	SDL_FreeSurface(retour);
	SDL_FreeSurface(texte);
	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */

}
/**
 * @brief      Gestion des events sur l'ecran d'accueil
 * @param      SDL_Surface *ecran
 * @details    5 events possibles : fermer programme/touche échap/clic sur bouton 1/clic sur bouton 2/clic sur bouton 3/
 * @return     int -1 pour fermer le programme/échap, 1 pour jouer en solo, 2 pour jouer en multi, 3 pour afficher les regles
 */
int pause_welcome_screen(SDL_Surface *ecran){
	int continuer = 1,x,y,choix=0;
	SDL_Event event;

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				choix = -1;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
		            case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
						continuer = 0;
						choix = -1;
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT){
					x=event.button.x;
					y=event.button.y;
					if(x>(LARGEUR_F/2)-(LARGEUR_BUTTON/2) && x<(LARGEUR_F/2)+(LARGEUR_BUTTON/2)){
						if(y>300 && y<400){
							choix=1;
							continuer = 0;
						}
						else if(y>450 && y<550){
							choix=2;
							continuer = 0;
						}
						else if(y>600 && y<700){
							choix=3;
							continuer = 0;
						}
					}

				}
				break;
		}
	}
	return choix;
}
/**
 * @brief      Gestion des events sur l'écran des règles et celui des coups joués
 * @param      SDL_Surface *ecran
 * @details    3 events possibles : fermer/échap + 1 bouton "ok"
 * @return     void
 */
void pause_simple_screen(SDL_Surface *ecran){
	int continuer = 1, x,y;
	SDL_Event event;

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
					if(x>694 && x<(LARGEUR_F-30) && y>30 && y<30+HAUTEUR_BUTTON){
						printf("Button ok clicked !\n");
						continuer = 0;
					}
				}
				break;
		}
	}
}
/**
 * @brief      Gestion des events sur l'écran de jeu
 * @param      SDL_Surface *ecran
 * @return     void
 */
int pause_game(SDL_Surface *ecran, int* ind_cols, int* ind_rows){
	int continuer = 1, choix=0, x,y;
	SDL_Event event;

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0; choix=-1;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
		            case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
						continuer = 0; choix=-1;
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
						get_grid_index(x,y,ind_rows,ind_cols);
						printf("GRID TOUUUUUCH\n");
						continuer = 0;
					}
				}
				break;
		}
	}
	return choix;
}

void pause_pourTest()
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