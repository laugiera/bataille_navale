#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "init.h"
#include "game.h"



void game(void);
void saisir_coup(int* l, int* c, int **historique);
int deja_joue(int l, int c, int **historique);
int resultat_coup(int l, int c, Bateau * btx_adverses, int **historique);
int is_coule(int **historique, Bateau * b);
int gagne(Bateau * btx_adverses);
void affiche_etat_bateaux(Bateau * bateaux);

#endif
