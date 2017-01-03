/**
 * @file      init.h
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 Décembre 2016
 * @brief     Fonctions nécessaires à l'algo du jeu
 */
#ifndef GAME_H_
#define GAME_H_

void game(void);
void saisir_coup(int* l, int* c);
int resultat_coup(int l, int c, Bateau * btx_adverses);
int is_coule(int **historique, Bateau * b);

#endif