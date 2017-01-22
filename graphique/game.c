/**
 * @file      game.c
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 Décembre 2016
 * @brief     Fonctions nécessaires à l'algo du jeu
 * @details    ~
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "init.h"
#include "game.h"


/**
 * @brief      Boucle de jeu principale
 * @details    
 algo :
	initialisation du jeu : 
		->saisir les joueurs et leurs bateaux 
		->decider qui commence (aleatoire)
	jeu :
		->afficher la grille de jeu du joueur qui commence
		->saisir choix de la case
		->vérifier saisie
			>> si mauvaise saisie : retour à l'étape du dessus
		->afficher le resultat du coup 
		->mettre à jour la grille de jeu
		->vérifier si le joueur n'a pas gagné
			>> si le joueur a gagné : *fin de la boucle et du jeu
		->passer au joueur suivant
		->again and again 
 * @return    void
 */
void game(int solo, SDL_Surface * ecran, Uint32 colors[]) {
	
	/*variables utiles*/
	Joueur joueurs[2];
	Bateau * btx_adverses;
	int joueur_courant, res_coup, l, c;
	int jouer = 1, choix;
	int dj_joue = 0;
	char chaine[MAX_SAISIE], error[MAX_SAISIE] = " ";

	/*MODE VS Joueur*/
	if(solo == 0){
		if(simple_screen(ecran,"BIENVENUE, Joueur 1 !") == -1)
			exit(1);
		initialiser_joueur(&joueurs[0]);
	    sprintf(joueurs[0].name, "Joueur 1");
	    saisir_bateaux(&joueurs[0],ecran,colors);
	    if(simple_screen(ecran,"BIENVENUE, Joueur 2 !") == -1)
			exit(1);
	    initialiser_joueur(&joueurs[1]);
	    sprintf(joueurs[1].name, "Joueur 2");
	    saisir_bateaux(&joueurs[1],ecran,colors);
		joueur_courant = (rand()%2); 
		sprintf(chaine,"C'est le  %s qui commence !",joueurs[joueur_courant].name);
		if(simple_screen(ecran,chaine)== -1)
			exit(1);
		

		do
		{
			/*saisie de la case*/
			do {
				choix = game_screen(ecran,colors,"Cliquez sur une case !",error, "", &l, &c,&joueurs[joueur_courant],2);
				if (choix ==-1)
					exit(1); /*echap ou quitter*/
				printf("deja joue %c %d\n",l+'A',c);


				dj_joue = deja_joue(l,c,joueurs[joueur_courant].historique);
				if(dj_joue)
					sprintf(error,"Vous avez deja joue cette case !");
				else
					sprintf(error," ");

			}/*tq la case choisie est pas bonne*/
			while(dj_joue);

			/*on récupère les bateaux adverses pour comparer avec la case choisie*/
			if(joueur_courant == 1)
				btx_adverses = joueurs[0].bateaux;
			else
				btx_adverses = joueurs[1].bateaux;
			printf("res coup\n");
			res_coup = resultat_coup(l,c,btx_adverses,joueurs[joueur_courant].historique);

			/*on met à jour la grille de jeu*/
			joueurs[joueur_courant].historique[c][l] = res_coup;

			sprintf(chaine,"CASE : %c%d %s",l+'A',c,res_coup=='o'?"A l'eau !":"Touchey");
			if(simple_screen(ecran,chaine)== -1)
					exit(1);

			/*si le joueur a gagne on sort de la boucle*/
			if(gagne(btx_adverses)){
				sprintf(chaine,"THE END : Le joueur %s a gagne !\n",joueurs[joueur_courant].name);
				if(simple_screen(ecran,chaine)== -1)
					exit(1);
				jouer = 0;
			}
			/*sinon on continue et on passe au joueur suivant*/
			else {
				/*on passe au joueur adverse*/
				if(joueur_courant == 1)
					joueur_courant = 0;
				else
					joueur_courant = 1;

				sprintf(chaine,"Au tour de %s !",joueurs[joueur_courant].name);
				if(simple_screen(ecran,chaine)== -1)
					exit(1);
			}
		}while(jouer);


		free_joueur(&joueurs[0]);
		free_joueur(&joueurs[1]);
	}

	/*VS IA*/
	else if (solo == 1){

	}
}

/**
 * @brief      cherche si un coup a déjà été joué
 * @param      l le charactère de la ligne
 * @param	   c l'entier de la colonne
 * @param	   int ** grille de jeu
 * @return     boolean, vrai si déjà joué, faux sinon
 */
int deja_joue(int l, int c, int ** historique){
		if(historique[c][l]!='.'){
				printf("Vous avez déjà joué cette case, recommencez la saisie.\n");
				return 1;
		}
		return 0;
}

/**
 * @brief      donne le résultat d'un coup joué (à l'eau, touché ou coulé) et l'affiche.
 * @param      l le charactère de la ligne
 * @param	   c l'entier de la colonne
 * @param	   Bateau * btx_adverses
 * @param	   int ** grille de jeu
 * @return     int (valeur ASCII du char 'o' ou de l'id du bateau)
 */
int resultat_coup(int l, int c, Bateau * btx_adverses, int **historique){
	printf("\n\nCASE %c%d \n",l+'A',c );
	int res = is_case_bateau(l,c,btx_adverses);
	if(res == -1){
		printf("\nRESULTAT : A l'eau ! \n");
		return 'o';
	}
	else
	{	
		int i = 0;
		/*on retrouve le bateau touché en recherchant son id dans le tableau*/
		while(res != (btx_adverses+i)->id){
			i++;
		}
		Bateau * bateau_touche = btx_adverses+i;
		if(is_coule(historique,bateau_touche))
		{
			printf("\nRESULTAT : COULEYYY ! Bateau %d \n",res );
			return 'X';
		}
		else
			printf("\nRESULTAT : TOUCHEYY ! Bateau %d \n",res );
	}
	return res+'0';
}

/**
 * @brief      Verifie si le bateau donné est coulé ou non
 * @param      int** historique	la grille de jeu du joueur
 * @param	   Bateau* le bateau
 * @details    La fonction parcourt la matrice de jeu et compte le nombre d'occurence de l'id du bateau. 
 * Si le nombre d'occurence = à la taillle du bateau alors il est coulé.
 * Si le bateau est coulé, son état est actualisé à false et la grille de jeu mise à jour
 * @return     boolean	true si coulé, false sinon
 */
int is_coule(int **historique, Bateau * b){
	int i,k, nb =1;
	for (i = 0; i < NB_LIGNES; i++)
	{
		for (k = 0; k <= NB_COLONNES; k++)
		{
			if(historique[i][k]==b->id+'0')
				nb++;
		}
	}
	if(nb == b->taille){
		b->etat = 0;
		for (i = 0; i < NB_LIGNES; i++)
		{
			for (k = 0; k <= NB_COLONNES; k++)
			{
				if(historique[i][k]==b->id+'0')
					historique[i][k]='X';
			}
		}		
		return 1;	
	}
	return 0;	
}

/**
 * @brief      cherche si le joueur a gagne ou non
 * @param	   Bateau* les bateaux adverses
 * @details    Pour que le joueur gagne, il faut que l'état de tous les btx adverses soient à 0 (coulés)
 * @return     boolean	true si gagné, false sinon
 */
int gagne(Bateau * btx_adverses){
	int i, res = 1;
	for(i=0; i < NB_BATEAUX; i++){
		if((btx_adverses+i)->etat == 1)
			res = 0;
	}
	return res;
}


