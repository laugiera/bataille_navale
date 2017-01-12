/**
 * @file      init.h
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 Décembre 2016
 * @brief     Définis les structures et les méthodes du jeu - Ici se trouvent toutes les fonctions nécessaires à l'initialisation du jeu
 */
#ifndef INIT_H_
#define INIT_H_

/* CONSTANT MACROS */
#define LARGEUR_F	1024
#define HAUTEUR_F	800
#define LARGEUR_BUTTON	200
#define HAUTEUR_BUTTON	100
#define TAILLE_CELL	50

#define NB_LIGNES 10 
#define NB_COLONNES 10 

#define NB_BATEAUX 2

#define MAX_SAISIE 20
#define BLOC_MALLOC 100


/**
 * @brief      Bateau du joueur
 * @details   
 */
typedef struct Bateau{
	int id; /*!< Commence à 1*/
	int ligne;
	int colonne;
	int taille;
	int sens; /*!< 0 vertical; 1 horizontal; */
	int etat; /*!< 1(true) en vie; 0(false) coulééééé; */
	int row_position; /*!< position en pixels sur la grille de jeu */
	int col_position; /*!< position en pixels sur la grille de jeu */
} Bateau;

/**
 * @brief      Joueur
 * @details   
 * @champs : historique = grille de jeu (0 à NB_LIGNES-1 lignes, 1 à NB_COLONNES colonnes). 
 * La valeur vaut '.' à l'initialisation
 * puis '%d' bateau.id (touché), ou 'o' (eau), 'X' (coulé)
 * ATTENTION : La grille du joueur 1 fonctionne avec les bateaux du Joueur 2 et vice-versa !
 */
typedef struct Joueur{
	char name[MAX_SAISIE];
	struct Bateau *bateaux; /*!< Tableau de NB_BATEAUX bateaux allouée dynamiquement*/
	int **historique; /*!< Matrice de jeu allouée dynamiquement. */
} Joueur;

int get_grid_index(int x_position, int y_position, int *index_row, int *index_cols);
void welcome_screen(SDL_Surface * ecran, Uint32 colors[]);
void rules_screen(SDL_Surface * ecran);
void game_screen(SDL_Surface * ecran);
void stroke_screen(SDL_Surface * ecran);
void pause(SDL_Surface *ecran);

#endif