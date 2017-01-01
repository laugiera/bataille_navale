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
void game(void) {
	srand(time(NULL));
	welcome_screen();
	rules_screen();
	int IA = menu_screen();
	Joueur joueurs[2];
	int joueur_courant;

	/*VS Joueur*/
	if(IA == 1){
		printf ("\n============================[JOUEUR 1 - BIENVENUE !]===================================\n");
	    initialiser_joueur(&joueurs[0]);
	    system_message("Entrée pour continuer");
		cls();
	    printf ("\n============================[JOUEUR 2 - BIENVENUE !]===================================\n");
	    initialiser_joueur(&joueurs[1]);
	    system_message("Entrée pour continuer");
		cls();
		printf ("\n============================[DEBUT DU JEU]===================================\n");
		joueur_courant = (rand()%2); /*1 ou 0*/

		printf("C'est le Joueur %s qui commence ! \n",joueurs[joueur_courant].name);

		while(1) /*condition à changer*/
		{
			int l,c;
			printf ("\n============================[A VOTRE TOUR %s!]===================================\n",joueurs[joueur_courant].name);
			afficher_grille(joueurs[joueur_courant],1);
			saisir_coup(&l,&c);

			system_message("Entrée pour continuer");
			cls();
			if(joueur_courant == 1)
				joueur_courant = 0;
			else
				joueur_courant = 1;
		}

		free_joueur(&joueurs[0]);
		free_joueur(&joueurs[1]);
	}

	/*VS IA*/
	else if (IA == 2){

	}
}

void saisir_coup(int* l, int* c){
	do{
		printf("Saisir une ligne (A - %c):\n",'A'+NB_LIGNES-1);
		(*l) = fgetc(stdin);
		f_purge(stdin);
		printf("Saisir une colonne (1-%d):\n",NB_COLONNES);
		scanf("%d",c);
		f_purge(stdin);
	}while(verifier_lignes(*l)==0 || verifier_colonne(*c)==0);
}

int resultat_coup(int l, int c, Bateau * btx_adverses){
	return 0;
}
