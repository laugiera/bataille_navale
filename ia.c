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

/**
 * @brief      génère des coordonnées ciblées pour le coup que l'IA tire
 * @param      l, pointeur vers le caractère de la ligne
 * @param      c, pointeur vers l'int de la colone
 * @param      historique, grille de jeu de l'ia
 * @param      l_cible, la ligne de la cible (code ASCII)
 * @param      c_cible, la colone de la cible
 * @details    effectue un quadrillage autour d'une zone donnée par la cible en fonction de l'historique de tir
 * @return     void
 */
void coup_ia_cible(int *l, int *c, int **historique, int l_cible, int c_cible) {
	/*direction vertical: 0, horizontal: 1*/
	printf("cible : %c%d\n",l_cible, c_cible);
	Sens sens = vertical;
	if (historique[l_cible-'A'][c_cible] == '+') {
		/*si aucun adjacent n'est touché tirer au hasard*/
		if (ia_check_adjacent(historique, l_cible, c_cible, &sens) == 0) {
			coup_ia_random4cases(l, c, historique, l_cible, c_cible);
			printf("res random 4 : %c%d\n", *l, *c);
		} 
		/*si une case adjacente est déja touchée, le sens du bateau est detrminée et on frappe au hasard une des deux extremitées*/
		else {
			coup_ia_random2cases(l, c, historique, l_cible, c_cible, sens);
			printf("res random 2 : %c%d\n", *l, *c);
		}
	} else {
		printf("ERREUR choix mode, utilisation random par défaut\n");
		coup_ia_random(l, c, historique);
	}
}

/**
 * @brief      cherche a savoir si des cases adjacentes à la cible ont déja été jouées
 * @param      historique, grille de jeu de l'ia
 * @param      l_cible, la ligne de la cible (code ASCII)
 * @param      c_cible, la colone de la cible
 * @param      *sens, pointeur vers le sens du bateau
 * @details    regarde aussi si les cases adjacentes sont dans la map et donne le sens du bateau si il peut etre determiné
 * @return     int, 1 : s'il y a une cases touchée adjacente, O: sinon
 */
int ia_check_adjacent(int **historique, int l_cible, int c_cible, Sens *sens) {
	if((verifier_lignes(l_cible+1)==1 && historique[l_cible-'A'+1][c_cible] == '+') ||
	   (verifier_lignes(l_cible-1)==1 && historique[l_cible-'A'-1][c_cible] == '+')) {
		*sens = vertical;
		return 1;
	} else if ((verifier_colonne(c_cible+1)==1 && historique[l_cible-'A'][c_cible+1] == '+') ||
			   (verifier_colonne(c_cible-1)==1 && historique[l_cible-'A'][c_cible-1] == '+')) {
		*sens = horizontal;
		return 1;
	} else {
		return 0;
	}
}


/**
 * @brief      génère des coordonnées aléatoires d'une cases adjacente à la cible
 * @param      l, pointeur vers le caractère de la ligne
 * @param      c, pointeur vers l'int de la colone
 * @param      historique, grille de jeu de l'ia
 * @param      l_cible, la ligne de la cible (code ASCII)
 * @param      c_cible, la colone de la cible
 * @details    génère de nouvelles coordonnées jusqu'à tomber sur une case qui n'a pas encore été jouée
 * @return     void
 */
void coup_ia_random4cases(int *l, int *c, int **historique, int l_cible, int c_cible) {
	printf("Pas d'indice random 4 cases\n");
	do{
		Sens sens = (Sens)(rand()%2);
		if(sens == vertical) {
			*c = c_cible;
			if(rand()%2 == 0) {
				*l = l_cible-1;
			} else {
				*l = l_cible+1;
			}
		} else {
			*l = l_cible;
			if(rand()%2 == 0) {
				*c = c_cible-1;
			} else {
				*c = c_cible+1;
			}
		}
		printf("sens : %d \ncase : %c %d \n",sens,*l, *c);
	}while(verifier_lignes(*l)==0 || verifier_colonne(*c)==0 || deja_joue(*l,*c,historique));
}

/**
 * @brief      génère des coordonnées aléatoires d'une case en bout de bateau
 * @param      l, pointeur vers le caractère de la ligne
 * @param      c, pointeur vers l'int de la colone
 * @param      historique, grille de jeu de l'ia
 * @param      l_cible, la ligne de la cible (code ASCII)
 * @param      c_cible, la colone de la cible
 * @param      sens, horizontal ou vertical, sens du bateau
 * @details    génère de nouvelles coordonnées jusqu'à tomber sur une case qui n'a pas encore été jouée
 * @return     void
 */
void coup_ia_random2cases(int *l, int *c, int **historique, int l_cible, int c_cible, Sens sens) {
	int i = 0, j=0;
	printf("IA random 2 cases\n");
	if (sens == vertical) {
		*c = c_cible;
		/*trouver les extrèmes du bateau*/
		while (historique[l_cible-'A'+i][c_cible] == '+' && verifier_lignes(l_cible+i+1) == 1) {
			i++;
		}
		while (historique[l_cible-'A'-j][c_cible] == '+' && verifier_lignes(l_cible-j-1) == 1) {
			j++;
		}
		/*regarder leur état et choisir en fonction (normalement au moins un des deux doit etre inconnu sinon on aurait déjà changé de mode*/
		printf("Les desu cases sont %c%d et %c%d\n",l_cible-j, c_cible, l_cible+i, c_cible);
		if(historique[l_cible-'A'+i][c_cible] != '.') {
			*l= l_cible-j;
		} else if (historique[l_cible-'A'-j][c_cible] != '.') {
			*l= l_cible+i;
		} else if (historique[l_cible-'A'+i][c_cible] == '.' && historique[l_cible-'A'-j][c_cible] == '.'){
			if(rand()%2 == 0) {
				*l= l_cible-j;
			} else {
				*l= l_cible+i;
			}
		} else {
			printf("ERREUR : cas 2 inconnues en bout de bateau, Not possible\n");
		}
	} else {
		*l = l_cible;
		/*trouver les extrèmes du bateau*/
		while (historique[l_cible-'A'][c_cible+i] == '+' && verifier_colonne(c_cible+i+1) == 1) {
			i++;
		}
		while (historique[l_cible-'A'][c_cible-j] == '+' && verifier_colonne(c_cible-j-1) == 1) {
			j++;
		}
		printf("Les deux cases sont %c%d et %c%d\n",l_cible, c_cible-j, l_cible, c_cible+i);
		/*regarder leur état et choisir en fonction (normalement au moins un des deux doit etre inconnu sinon on aurait déjà changé de mode*/
		if(historique[l_cible-'A'][c_cible+i] != '.') {
			*c= c_cible-j;
		} else if (historique[l_cible-'A'][c_cible-j] != '.') {
			*c= c_cible+i;
		} else if(historique[l_cible-'A'][c_cible+i] == '.' && historique[l_cible-'A'][c_cible-j] == '.'){
			if(rand()%2 == 0) {
				*c= c_cible-j;
			} else {
				*c= c_cible+i;
			}
		} else {
			printf("ERREUR : cas 2 inconnues en bout de bateau, Not possible\n");
		}
	}
}

/**
 * @brief      génère des coordonnées intelligente pour le coup que l'IA tire
 * @param      l, pointeur vers le caractère de la ligne
 * @param      c, pointeur vers l'int de la colone
 * @param      historique, grille de jeu de l'ia
 * @param      mode, 1 : aléatoire, 2 : cible
 * @param      l_cible, la ligne de la cible (code ASCII)
 * @param      c_cible, la colone de la cible
 * @details    à venir
 * @return     void
 */
void coup_ia_intelligent(int *l, int *c, int **historique, ModeIA mode, int l_cible, int c_cible) {
	if (mode == mode_aleatoire) {
		coup_ia_random(l, c, historique);
		printf("coup aléatoire\n");
	} else {
		coup_ia_cible(l, c, historique, l_cible, c_cible);
		printf("res coup ciblé : %c%d\n",*l, *c );
		printf("coup ciblé\n");
	}
}


/**
 * @brief      switch entre les différents mode d'ia et ajuste la cible si besoin
 * @param      *mode_ia, pointeur vers le mode d'IA
 * @param      *l_cible, poiteur vers la ligne de la cible (code ASCII)
 * @param      *c_cible, poiteur vers la colone de la cible
 * @param      *l, poiteur vers la ligne du dernier coup tiré (code ASCII)
 * @param      *c, poiteur vers la colone du dernier coup tiré
 * @param      res_coup, resultat du coup précédent
 * @details    En fonction du resultat du coup précédent, change éventuellement de mode et/ou de cible
 * @return     void
 */
void choix_mode_ia(ModeIA *mode_ia, int *l_cible, int *c_cible, int *l, int *c, int res_coup) {
	if(*mode_ia == mode_aleatoire && res_coup == '+') {
		*mode_ia = mode_cible;
		*l_cible = *l;
		*c_cible = *c;
	} else if (*mode_ia == mode_cible && res_coup == 'X'){
		*mode_ia = mode_aleatoire;
	} 
}


/**
 * @brief      complete l'historique autour des bateaux coulés
 * @param      historique, historique de l'ia
 * @details    met des 'o' à l'eau sur les cases adjacentes aux bateaux coulés puisque deux bateaux ne peuvent pas se toucher
 * @return     void
 */
void completer_historique_ia(int **historique) {
	int i, j;
	for (i=0; i<NB_LIGNES; i++) {
		for(j=0; j<NB_COLONNES; j++){
			if (historique[i][j] == 'X') {
				if (verifier_lignes('A'+i+1)==1 && historique[i+1][j]=='.') {
					historique[i+1][j]='o';
				}
				if (verifier_lignes('A'+i-1)==1 && historique[i-1][j]=='.') {
					historique[i-1][j]='o';
				}
				if (verifier_colonne(j+1)==1 && historique[i][j+1]=='.') {
					historique[i][j+1]='o';
				}
				if (verifier_colonne(j-1)==1 && historique[i][j-1]=='.') {
					historique[i][j-1]='o';
				}
			}
		}
	}
	/*premier test pour une raison inconnue il n'a pas voulu mettre le 'o' au dessus de la premiere case
	ne marche pas en verticale*/
}


/*
TO DO : 
- associer init_ia avec init_jouer et ajouter un param IA dans saisir_bateau pour empecher l'affichage de la grille de l'IA
- empecher le message d'erreur de deja_joue avec IA
-enlever verif_lign et col dans coup_ia_random
- peut etre ajouter un truc pour bloquer si jamais qqn essaye d'augmenter le nb de bateau et qu'il y a des pb pour les placer aléatoirement
-coup ia cible : check ligne et col qui doivent etre dans la grille

Pour aléillorer l'IA
-élimination auto des cases autour d'un bateau
*/