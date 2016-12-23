/**
 * @file      main.c
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 Décembre 2016
 * @brief     Boucle principale du jeu
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"


int main( int argc, char *argv[] ){

	printf("***********************\nEPIK WAR SHIP TADADAM !\n***********************\nBienvenue, jeune padawn !\n***********************\n");

	Joueur joueur1;
	
	int res = initialiser_joueur(&joueur1);
	afficher_joueur(joueur1);
	free_joueur(&joueur1);

	return EXIT_SUCCESS;

}