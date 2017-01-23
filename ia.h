/**
 * @file      ia.h
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      22 Janvier 2017
 * @brief     Définis les structures et les méthodes du jeu - Ici se trouvent toutes les fonctions nécessaires au fonctionnement de l'IA et aux placement aléatoire
 */


#ifndef GAME_H_
#define GAME_H_


typedef enum {
	mode_aleatoire,
	mode_cible
} ModeIA;

typedef enum {
	vertical,
	horizontal,
} Sens;


/*main pour test
int main();
*/
void placement_aleatoire(int taille, int *col, int *ligne, int *sens);
/*
int initialiser_ia(Joueur *j, int mode_placement);
*/
void coup_ia_random(int *l, int *c, int **historique);
void coup_ia_cible(int *l, int *c, int **historique, int l_cible, int c_cible);
int ia_check_adjacent(int **historique, int l_cible, int c_cible, Sens *sens); 
void coup_ia_random4cases(int *l, int *c, int **historique, int l_cible, int c_cible);
void coup_ia_random2cases(int *l, int *c, int **historique, int l_cible, int c_cible, Sens sens);
void coup_ia_intelligent(int *l, int *c, int **historique, ModeIA mode, int l_cible, int c_cible);
void choix_mode_ia(ModeIA *mode_ia, int *l_cible, int *c_cible, int *l, int *c, int res_coup);
void completer_historique_ia(int **historique);

#endif

/*
BUG inknown type Joueur qd prototype déclaré
*/