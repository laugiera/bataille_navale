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

/* main pour test
int main() {
	int i;
	int taille = 3;
	int col = 0;
	int ligne = 0;
	int sens = 0;
	for(i=0; i<5; i++) {
	placement_aleatoire(taille, &col, &ligne, &sens);
	printf("col : %d\nligne : %c\n, sens : %d\n\n", col, ligne, sens);
	}
	return 1;
}
*/


/**
 * @brief      fournit des coordonées aléatoires pour un bateau
 * @param      taille, un entier pour la taille du bateau
 * @param 	   c, un entier pour la colonne
 * @param 	   s, un entier pour l'orientation
 * @param 	   taille, un entier pour la taille du bateau concerné
 * @param 	   j, le joueur
 * @details    Pour qu'un placement soit valide, il faut que la saisie soit correcte, conforme à la grille (le bateau ne sort pas). Il faut que la case ne chevauche pas un autre bateau ET qu'elle ne touche pas un autre bateau.
 * @return     booléen. FALSe si mauvais placement, TRUE sinon
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