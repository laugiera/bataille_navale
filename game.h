/**
 * @file      init.h
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 Décembre 2016
 * @brief     Fonctions nécessaires à l'algo du jeu
 */
#ifndef GAME_H_
#define GAME_H_

/* a cause de mon pb de link*/
 typedef enum {
	mode_aleatoire,
	mode_cible
} ModeIA;
typedef enum {
	vertical,
	horizontal,
	gauche,
	droite
} Direction;

void game(void);
void saisir_coup(int* l, int* c, int **historique);
int deja_joue(int l, int c, int **historique);
int resultat_coup(int l, int c, Bateau * btx_adverses, int **historique);
int is_coule(int **historique, Bateau * b);
int gagne(Bateau * btx_adverses);
void affiche_etat_bateaux(Bateau * bateaux);

#endif