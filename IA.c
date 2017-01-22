#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "init.h"
#include "game.h"
#include "IA.h"


int ligne;
int colonne;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Ordinateur Initialise */

int initialiser_IA(Joueur *j, int plmt){

	int i,k;
	/*pseudo*/
	printf("Quel est le nom de l'ordinateur ?\n");
	scanf("%s",j->name);
	f_purge(stdin);
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
	saisir_bateaux(j, plmt=2);
	return EXIT_SUCCESS;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Jeu aléatoire */
void Niveau0(int* l, int* c, int **historique)
    {
        do{
            int nbr_colonne=(rand() % (9 - 0 + 1)) + 0;
            int lettre=(rand() % (9 - 0 + 1)) + 0;
            char alphabet[] = "ABCDEFGHIJ";

            ligne = alphabet[lettre];
            ligne = *l;
            f_purge(stdin);

            colonne=nbr_colonne;
            nbr_colonne = *c;
            f_purge(stdin);

        }while(verifier_lignes(*l)==0 || verifier_colonne(*c)==0 || deja_joue(*l,*c,historique));


    }
