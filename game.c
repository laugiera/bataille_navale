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

	Joueur joueur1, joueur2;

    printf ("\n============================[JOUEUR 1 - BIENVENUE !]===================================\n");
    system_message("Entrée pour continuer");
    initialiser_joueur(&joueur1);
	cls();
    printf ("\n============================[JOUEUR 2 - BIENVENUE !]===================================\n");
    system_message("Entrée pour continuer");
    initialiser_joueur(&joueur2);
	cls();

	int start = rand()%2; /*0 ou 1*/
	printf("C'est le Joueur %d qui commence ! \n",start+1);

	free_joueur(&joueur1);
	free_joueur(&joueur2);
}