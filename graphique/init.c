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
 * @details    x correspond à cols et y à rows
 * @return     int	
 */
int get_grid_index(int x_position, int y_position, int *index_row, int *index_cols){
	int i,j;
	for (i = 0; i < 10; i++)
	{
		/*printf("TAILLE_CELL*(i+1) = %d et TAILLE_CELL*(i+2) = %d\n",TAILLE_CELL*(i+1),TAILLE_CELL*(i+2) );*/
		if(x_position>=DECALAGE + TAILLE_CELL*(i+1) && x_position<DECALAGE + TAILLE_CELL*(i+2))
		{
			/*printf("ok col (x) FOUND !\n");*/
			for (j = 0; j < 10; j++)
			{
				/*printf("TAILLE_CELL*(j+1) = %d et TAILLE_CELL*(j+2) = %d\n",TAILLE_CELL*(j+1),TAILLE_CELL*(j+2) );*/
				if(y_position>=DECALAGE + TAILLE_CELL*(j+1) && y_position<DECALAGE + TAILLE_CELL*(j+2))
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
 * @return     int choix de l'écran qui suivra (1,2,3)
 */
int welcome_screen(SDL_Surface * ecran, Uint32 colors[]){

	SDL_Rect position;
	position.x=0;
	position.y=0;

	SDL_Surface *background = IMG_Load("img/Accueuil.jpg");
	SDL_Surface *modeJoVsJO = IMG_Load("img/bouton_multi.png");
	SDL_Surface *modeIA = IMG_Load("img/bouton_IA.png");
	SDL_Surface *rules = IMG_Load("img/bouton_rules.png");

	SDL_BlitSurface(background,NULL,ecran,&position);
	
	position.x=(LARGEUR_F/2)-(LARGEUR_BUTTON/2);
	position.y=380;
	SDL_BlitSurface(modeIA, NULL, ecran, &position);
	position.y=530;
	SDL_BlitSurface(modeJoVsJO, NULL, ecran, &position);
	position.y=680;
	SDL_BlitSurface(rules, NULL, ecran, &position);

	SDL_Flip(ecran); 
	/*on attend que le joueur clique sur un des trois boutons*/															
	int choix = pause_welcome_screen(ecran);

	SDL_FreeSurface(background);
	SDL_FreeSurface(modeIA);
	SDL_FreeSurface(modeJoVsJO);
	SDL_FreeSurface(rules);

	return choix;
}
/**
 * @brief      Ecran qui affiche les règles
 * @param      SDL_Surface * ecran
 * @details    La fonction attend que le joueur clique sur le bouton ok
 * @return     void
 */
void rules_screen(SDL_Surface * ecran){
	SDL_Rect position;
	position.x=0;
	position.y=0;

	SDL_Surface *background = IMG_Load("img/Regles.jpg");
	SDL_Surface *retour = IMG_Load("img/bouton_retour.png");

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
 * @param      Uint32 colors[]
 * @param      char *titre	texte qui décrit l'action attendue par le joueur
 * @param      char *error 	texte qui affiche une error s'il y en a besoin
 * @param      char *sens_txt  texte qui permet d'indiquer le sens de placement des bateaux
 * @param      int *ligne 	l'index de la ligne de la case cliquée
 * @param      int *col 	l'index de la col de la case cliquée
 * @param      Joueur *jo 	joueur courant
 * @param      int placement	Gestion des grilles : 1 pour la grille de placement des bateaux ,2 pour la grille de jeu
 * @return     int action du joueur (-1 = quitter, 0 = case cliquée, 1 = espace)
 */
int game_screen(SDL_Surface * ecran, Uint32 colors[], char * title, char * error,  char *sens_txt, int *ligne, int *col, Joueur * jo, int placement){

	/*VARIABLES*/
	SDL_Surface *grid[10][10];
	SDL_Surface *cols[10] = {NULL};
	SDL_Surface *rows[10] = {NULL};
	SDL_Surface *title_surf = NULL;
	SDL_Surface *error_surf = NULL;
	SDL_Surface *sens_surf = NULL;
	SDL_Surface *background = IMG_Load("img/Fond_Neutre.jpg");

	SDL_Rect position;

	int choix;

	TTF_Font *police_grille = NULL, *police_txt = NULL;
	police_grille = TTF_OpenFont("polices/batmfa__.ttf", 30);
	police_txt = TTF_OpenFont("polices/Starjedi.ttf", 20);

	SDL_Color couleurJaune = {255, 208, 45};
	SDL_Color couleurRouge = {255, 84, 0};
	 
	int i,j;
	char string [80];
	int  is_bateau;

	/*ALLOC SURFACES*/
	position.x=0;
	position.y=0;
	SDL_BlitSurface(background,NULL,ecran,&position);

	/*titre txt*/
	position.x=DECALAGE;
	position.y=650;
	title_surf = TTF_RenderText_Blended(police_txt, title, couleurJaune);
	SDL_BlitSurface(title_surf, NULL, ecran, &position);

	/*sens txt*/
	position.x=DECALAGE;
	position.y=700;
	sens_surf = TTF_RenderText_Blended(police_txt, sens_txt, couleurJaune);
	SDL_BlitSurface(sens_surf, NULL, ecran, &position);

	/*error txt*/
	if(strlen(error)!=0){
		position.x=DECALAGE;
		position.y=750;
		error_surf = TTF_RenderText_Blended(police_txt, error, couleurRouge);
		SDL_BlitSurface(error_surf, NULL, ecran, &position);				
	}

	/*grille index*/
	position.x=DECALAGE+TAILLE_CELL;
	position.y=DECALAGE;
	for (i = 0; i < 10; i++) /*colonnes index*/
	{
		sprintf(string,"%d",i);
		cols[i] = TTF_RenderText_Blended(police_grille, string, couleurJaune);
    	SDL_BlitSurface(cols[i], NULL, ecran, &position); /* Blit du texte */
		position.x += TAILLE_CELL;
	}
	position.x=DECALAGE;
	position.y=DECALAGE+TAILLE_CELL;
	for (i = 0; i < 10; i++) /*lignes index txt*/
	{		
		sprintf(string,"%c",'A'+i);
		rows[i] = TTF_RenderText_Blended(police_grille, string, couleurJaune);
    	SDL_BlitSurface(rows[i], NULL, ecran, &position); /* Blit du texte */
		position.y += TAILLE_CELL;	
	}

	/*grille cases*/
	position.y = DECALAGE + TAILLE_CELL;
	position.x = DECALAGE + TAILLE_CELL;
	for (i = 0; i < 10; i++) 
	{
		for (j = 0; j < 10; j++)
		{
			is_bateau = is_case_bateau(j,i,jo->bateaux);
			/*grille placement bateaux*/
			if (placement <= 1 && is_bateau != -1){
				sprintf(string,"%d",is_bateau);
				grid[i][j]=TTF_RenderText_Blended(police_grille, string, couleurJaune);
			}
			/*grille jeu*/
			else if(placement == 2 && jo->historique[i][j]!='.'){ /*si case bateau*/
				if(jo->historique[i][j]=='o')
					grid[i][j]=IMG_Load("img/espace.png"); /*eau*/
				else if (jo->historique[i][j]=='X') /*couley*/
					grid[i][j]=IMG_Load("img/coule.png");
				else /*touchey*/
					grid[i][j]=IMG_Load("img/touche.png");

			}
			else { /*case inconnue*/
				grid[i][j]=IMG_Load("img/inconnu.png");
			}

			SDL_BlitSurface(grid[i][j], NULL, ecran, &position); 
			position.y += TAILLE_CELL;
		}
		position.x += TAILLE_CELL;
		position.y = DECALAGE + TAILLE_CELL;
	}
	printf("Init Grid ok\n");

	SDL_Flip(ecran);
	choix = pause_game(ecran, ligne,col); /*-1 = quitter, 0 = case, 1 = espace*/


	/*FREE SURFACES*/
	SDL_FreeSurface(error_surf);
	SDL_FreeSurface(title_surf);
	for (i = 0; i < 10; i++)
    {
    	for (j = 0; j < 10; j++)
    		SDL_FreeSurface(grid[i][j]); 

    }
    for (i = 0; i < 10; i++)
    	SDL_FreeSurface(rows[i]);
    for (i = 0; i < 10; i++)
    	SDL_FreeSurface(cols[i]);

    TTF_CloseFont(police_grille); /* Doit être avant TTF_Quit() */
    TTF_CloseFont(police_txt);
    return choix;
}

/**
 * @brief      Ecran qui affiche une chaine donnée
 * @param      SDL_Surface * ecran
 * @param      char * chaine à écrire
 * @details    La fonction attend que le joueur clique sur le bouton ok
 * @return     int	choix du joueur (-1 si échap/quitter, 0 si clic sur continuer/ok)
 */
int simple_screen(SDL_Surface * ecran, char * chaine){
	SDL_Rect position;
	position.x=0;
	position.y=0;


	TTF_Font *police = NULL;
	police = TTF_OpenFont("polices/batmfa__.ttf", 40);

	SDL_Color couleurBlanc = {255, 255, 255};

	SDL_Surface *background = IMG_Load("img/Fond_Neutre.jpg");
	SDL_Surface *retour = IMG_Load("img/bouton_continuer.png");

	SDL_BlitSurface(background,NULL,ecran,&position);
	
	position.x=LARGEUR_F-LARGEUR_BUTTON-30;
	position.y=30;
	SDL_BlitSurface(retour, NULL, ecran, &position);

	SDL_Surface *texte = TTF_RenderText_Blended(police, chaine, couleurBlanc);
	position.x = (LARGEUR_F/2)-(texte->w/2);
	position.y = (HAUTEUR_F/2)-(HAUTEUR_BUTTON/2);
    SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */

	SDL_Flip(ecran); 															
	int choix = pause_simple_screen(ecran);

	SDL_FreeSurface(background);
	SDL_FreeSurface(retour);
	SDL_FreeSurface(texte);
	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */

	return choix;

}
/**
 * @brief      Gestion des events sur l'ecran d'accueil
 * @param      SDL_Surface *ecran
 * @details    5 events possibles : fermer programme/touche échap/clic sur bouton 1/clic sur bouton 2/clic sur bouton 3/
 * @return     int -1 pour fermer le programme/toucher échap, 1 pour jouer en solo, 2 pour jouer en multi, 3 pour afficher les regles
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
						if(y>380 && y<480){
							choix=1;
							continuer = 0;
						}
						else if(y>530 && y<630){
							choix=2;
							continuer = 0;
						}
						else if(y>680 && y<780){
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
 * @return     int choix du joueur (-1 ou 0)
 */
int pause_simple_screen(SDL_Surface *ecran){
	int continuer = 1, x,y;
	SDL_Event event;

	while (continuer == 1)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = -1;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
		            case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
						continuer = -1;
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
	return continuer;
}
/**
 * @brief      Gestion des events sur l'écran de jeu
 * @param      SDL_Surface *ecran
 * @param      int * index ligne
 * @param      int * index col
 * @return     int	choix du joueur (-1 pour quitter, 0 pour le clic d'une case, 1 pour la barre espace)
 */
int pause_game(SDL_Surface *ecran, int* ind_rows,int* ind_cols){
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
					case SDLK_SPACE:
						continuer = 0; choix = 1;
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT){
					x=event.button.x;
					y=event.button.y;
					if(x>(TAILLE_CELL + DECALAGE) && x<(TAILLE_CELL + DECALAGE)+(10*TAILLE_CELL) && y>(TAILLE_CELL + DECALAGE) && y<(TAILLE_CELL + DECALAGE)+(10*TAILLE_CELL)){
						get_grid_index(x,y,ind_rows,ind_cols);
						printf("GRID TOUUUUUCH  %c %d\n",(*ind_rows)+'A',*ind_cols);
						continuer = 0;
					}
				}
				break;
		}
	}
	return choix;
}


/**
 * @brief      Initialise le joueur
 * @param      j, le joueur
 * @details    Le joueur saisit son nom. L'historique est alloué est initialisé à O. Les bateaux sont alloués puis saisis.
 * @return     EXIT_FAILURE si les malloc fail, EXIT_SUCESS sinon
 */
int initialiser_joueur(Joueur *j){
	int i,k;
	/*pseudo*/
	printf("init joueur\n");
	/*historique - grille de jeu - allocation*/
	j->historique = malloc((NB_LIGNES)*sizeof(int*));
	if(j->historique == NULL)
		return EXIT_FAILURE;
	else {
		for (i = 0; i < NB_LIGNES; i++){
    		j->historique[i] = malloc(sizeof(int) * NB_COLONNES+1);
    		if(j->historique[i]==NULL)
    			return EXIT_FAILURE;
		}
	}
	/*historique - initialisation*/
	for (i = 0; i < NB_LIGNES; i++)
	{
		for (k = 0; k <= NB_COLONNES; k++)
		{
			j->historique[i][k]='.'; 
		}
	}	
	/*bateaux*/
	j->bateaux = malloc(NB_BATEAUX * sizeof(Bateau));
	if(j->bateaux == NULL)
		return EXIT_FAILURE;
	for (i= 0; i< NB_BATEAUX; i++){
		(j->bateaux+i)->ligne = ' ';
		(j->bateaux+i)->colonne = NB_COLONNES+10;
	}
	return EXIT_SUCCESS;
}

/**
 * @brief      libère la mémoire allouée au joueur
 * @param      j, le joueur
 * @return     void
 */
void free_joueur(Joueur *j){
	int i;
	free(j->bateaux);
	for (i = 0; i < NB_LIGNES; i++)
	{
		free(j->historique[i]);		
	}
	free(j->historique);
}

/**
 * @brief      le joueur saisit les emplacements de ses bateaux
 * @param      j, le joueur
 * @param      SDL_Surface * ecran
 * @param      int32 colors[]
 * @details    le joueur choisi une case. Si le choix est mauvais, un message d'erreur s'affiche et on réitère
 * @return     void
 */
void saisir_bateaux(Joueur *j, SDL_Surface* ecran, Uint32 colors[]){
	int i,tailles[NB_BATEAUX]={3,2}; /*!< Règles : 1 bateau de taille 5, 1 de taille 4, 2 de taille 3, 1 de taille 2*/
	int colonne=NB_COLONNES+10, ligne=' ', sens=0, choix, saisie=0; /*!< SENS 0 = vers le bas (par défaut) et 1 = vers la droite */
	char titre[MAX_SAISIE], error[MAX_SAISIE] = "", sens_txt[MAX_SAISIE];

	for (i = 0; i < NB_BATEAUX; i++)
	{
		(j->bateaux+i)->id=i+1; 
		do {
			saisie = 0;
			sprintf(titre,"%s ! Saisie du bateau %d, taille %d !",j->name,i+1,tailles[i]);
			sprintf(sens_txt, "Sens : %s (barre espace pour changer)",sens==0?"vers le bas":"vers la droite");
			choix = game_screen(ecran,colors,titre,error, sens_txt, &ligne, &colonne,j,1);
			if (choix ==-1)
				exit(1); /*echap ou quitter*/
			else if(choix ==1) /*changement de sens*/
				sens = sens==1?0:1;
			else 
				saisie = verifier_saisie_bateaux(error,ligne, colonne, sens,tailles[i],*j);
			/*tq saisie mauvaise*/
		}while(saisie==0);

		/*initialisation bateau*/
		(j->bateaux+i)->taille=tailles[i];
		(j->bateaux+i)->etat = 1;
		(j->bateaux+i)->ligne = ligne;
		(j->bateaux+i)->colonne = colonne;
		(j->bateaux+i)->sens = sens;	

		sprintf(error," ");	
	}
	/*affichage grille finale*/
	choix = game_screen(ecran,colors,"Placement des navires ok ! Appuyez sur espace pour continuer !","", "",&ligne,&colonne,j,0);
	if (choix ==-1)
		exit(1); /*echap ou quitter*/	

}

/**
 * @brief      vérifie le placement d'un bateau
 * @param      l, un entier pour la ligne
 * @param 	   c, un entier pour la colonne
 * @param 	   s, un entier pour l'orientation
 * @param 	   taille, un entier pour la taille du bateau concerné
 * @param 	   j, le joueur
 * @details    Pour qu'un placement soit valide, il faut que la saisie soit correcte, conforme à la grille (le bateau ne sort pas). Il faut que la case ne chevauche pas un autre bateau ET qu'elle ne touche pas un autre bateau.
 * @return     booléen. FALSe si mauvais placement, TRUE sinon
 */
int verifier_saisie_bateaux(char error[], int  l, int c, int  s, int taille, Joueur j){

	/* l_index : code ascii de la ligne dans la matrice de la grille, l est l'index de la ligne*/
	int l_index = l + 'A' ;
	int i; 
	printf("l_ind %c c %d s %d taille %d\n",l_index,c,s,taille);
	/*conforme à la grille, le bateau ne sort pas*/
	if(dans_la_grille(l_index,c,s,taille) == 0) {
		sprintf(error,"Placement hors de la grille");
		return 0;
	}
	/*conforme aux regles (pas de chevauchement de bateaux et pas de bateau qui se touchent)*/
	/*on part du principe que c'est bon et on cherche les exceptions.*/

	/*il faut le faire pour chaque case du bateau*/

	/*parcourir vers le bas*/
	if (s == 0) {
		for(i = l; i<l+taille; i++) {
			printf("touche bateau = %d\n",touche_bateau(i,c,j.bateaux));
			if(touche_bateau(i,c,j.bateaux) == 1) {
				printf("touche bateau\n");
				sprintf(error,"Erreur - Les bateaux ne doivent pas se toucher ni se chevaucher!");
				return 0;
			}
		
		}
	}
	/*parcourir vers la droite*/
	else if (s == 1) {
		for(i = c; i<c+taille; i++) {
			if(touche_bateau(l,i,j.bateaux)) {
				sprintf(error,"Erreur - Les bateaux ne doivent pas se toucher ni se chevaucher!");
				return 0;
			}
		
		}
	}		
	return (1);

}


/**
 * @brief      regarde si un bateau occupe la case donnée
 * @param      l, un entier de 0 à NB_LIGNES-1 pour la ligne (PAS LE CODE ASCII DE LA LETTRE)
 * @param      c, un entier pour la colonne
 * @param      b, tableau de bateaux du joueur
 * @return     -1 si la case est libre, bateau.id sinon
 */
int is_case_bateau(int l, int c, Bateau *b){
	int i, resultat = -1;
	for (i = 0; i < NB_BATEAUX; i++)
	{	
		/*printf("b ligne = %c b col = %d\n",(b+i)->ligne+'A', (b+i)->colonne);
		printf("l = %c et c = %d\n",l+'A',c );*/
		/*premiere case*/
		if((b+i)->ligne+'A' == 'A'+l && (b+i)->colonne == c) {
			resultat = (b+i)->id;
		}

		/*case en bas*/	
		else if ((b+i)->sens == 0 && 
			(b+i)->colonne == c && 
			'A'+l>(b+i)->ligne+'A' &&
			'A'+l<=(b+i)->ligne+'A'+((b+i)->taille-1)) {
			resultat = (b+i)->id;
		}

		/*case à droite*/
		else if ((b+i)->sens == 1 && 
			(b+i)->ligne+'A' == 'A'+l && 
			c > (b+i)->colonne &&
			c <=(b+i)->colonne+((b+i)->taille-1)) {
			resultat = (b+i)->id;
		}
	}
	return resultat;
}

/**
 * @brief      regarde si un bateau sort de la grille
 * @param      l, un entier pour la ligne
 * @param 	   c, un entier pour la colonne
 * @param 	   s, un entier pour l'orientation
 * @param 	   taille, un entier pour la taille du bateau concerné
 * @return     booléen, FALSE si ça sort de la grille
 */
int dans_la_grille(int l, int c, int s,int taille){

	/*case en bas*/
	/*printf("l = %c l+taille = %c, max = %c\n",l,l+taille-1,'A'+NB_LIGNES-1 );*/

	if (s == 0 && l+taille-1 <= 'A'+NB_LIGNES-1){
		return 1;
	}
	/*case à droite*/
	else if (s == 1 && c+taille <= NB_COLONNES+1)
		return 1;
	return 0;
}

/**
 * @brief      regarde si une case donnée est déjà occupée ou touche une case déjà occcupée par un bateau du joueur
 * @param      l, un entier pour la ligne (correspondant à l'index de la ligne : 0 à NB_LIGNE-1, pas au code ASCII)
 * @param 	   c, un entier pour la colonne
 * @param 	   b, tableau de bateaux du joueur
 * @details    la fonction regarde toutes les cases mitoyennes à la case donnée et vérifie si ce sont des cases occupées ou non
 * @return     booléen
 */
int touche_bateau(int l, int c, Bateau *b){
		/*
		 *g = l, c-1
		 *d = l, c+1
		 *h = l-1, c
		 *b = l+1, c
		 *diag_hg = l-1,c-1
		 *diag_hd = l-1,c+1
		 *diag_bg = l+1,c-1
		 *diag_bd = l+1,c+1
		*/
	return (
		is_case_bateau(l, c-1, b)!=-1 ||
		is_case_bateau(l, c+1, b)!=-1 ||
		is_case_bateau(l-1, c, b)!=-1 ||
		is_case_bateau(l+1, c, b)!=-1 ||
		is_case_bateau(l-1, c-1, b)!=-1 ||
		is_case_bateau(l-1, c+1, b)!=-1 ||
		is_case_bateau(l+1, c-1, b)!=-1 ||
		is_case_bateau(l+1, c+1, b)!=-1 
		);
}