/**
 * @file      ia.c
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      22 Janvier 2017
 * @brief     Définis les structures et les méthodes de l'IA et des placement aléatoires
 * @details    ~
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ia.h"
#include "init.h"
#include "game.h"



/**
 * @brief      fournit des coordonées aléatoires pour un bateau
 * @param      taille, un entier pour la taille du bateau
 * @param 	   *col, pointeur sur la variable colonne
 * @param 	   *ligne, pointeur sur la variable ligne (code ASCII)
 * @param 	   *sens, pointeur sur le sens
 * @details    à besoin d'une initialisation de rand préalable, renvoie un code ASCII pour la ligne
 * @return     rien
 */
void placement_aleatoire(int taille, int *col, int *ligne, int *sens) {
    char alphabet[] = "ABCDEFGHIJ";
    *sens = rand()%2;
    if(*sens == 1) {
    	*col = rand()%(10-taille+1);
    	*ligne = alphabet[rand()%10];
    } else {
    	*col = rand()%10;
    	*ligne = alphabet[rand()%(10-taille+1)];
    }
}

/**
 * @brief      Initialise l'IA
 * @param      j, l'IA
 * @param      mode_placement, doit être défini comme aléatoire (=2) avant d'appeler la fct
 * @details    Le nom est défini. L'historique est alloué est initialisé à O. Les bateaux sont alloués puis positionnés aléatoirement. Possibilité de coupler dans une condition avec la fct init_joueur, à voir...
 * @return     EXIT_FAILURE si les malloc fail, EXIT_SUCESS sinon
 */

int initialiser_ia(Joueur *j, int mode_placement){

	int i,k;
	/*pseudo*/
	strcpy(j->name, "R2D2");
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
		for (k = 0; k < NB_COLONNES; k++)
		{
			j->historique[i][k]='.';
		}
	}
	/*bateaux*/
	j->bateaux = malloc(NB_BATEAUX * sizeof(Bateau));
	if(j->bateaux == NULL)
		return EXIT_FAILURE;
	saisir_bateaux(j, mode_placement);
	return EXIT_SUCCESS;
}


/**
 * @brief      génère des coordonnées aléatoires pour le coup que l'IA tire
 * @param      l, pointeur vers le caractère de la ligne
 * @param      c, pointeur vers l'int de la colone
 * @param      historique, grille de jeu de l'ia
 * @details    génère de nouvelles coordonnées jusqu'à tomber sur une case qui n'a pas encore été jouée
 * @return     void
 */
void coup_ia_random(int *l, int *c, int **historique) {
	do{
		*c = rand()%10;
    	*l = 'A'+rand()%10;
	}while(verifier_lignes(*l)==0 || verifier_colonne(*c)==0 || deja_joue(*l,*c,historique));
}

/*
TO DO : 
- associer init_ia avec init_jouer et ajouter un param IA dans saisir_bateau pour empecher l'affichage de la grille de l'IA
- empecher le message d'erreur de deja_joue avec IA
-enlever verif_lign et col dans coup_ia_random
*/