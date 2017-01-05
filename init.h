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

#define NB_LIGNES 10
#define NB_COLONNES 10

#define NB_BATEAUX 2

#define MAX_SAISIE 20
#define BLOC_MALLOC 100

#if defined WIN32
#define CLEAN_SCREEN "CLS"
#elif defined __linux
#define CLEAN_SCREEN "clear"
#endif

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

void f_purge(FILE *fp);
void cls(void);
void system_message (char *message);
void welcome_screen (void);
void rules_screen (void);
int menu_screen(void);
int menu_screenPlacemnt(void);
void afficher_grille(Joueur jo, int etat);
void afficher_joueur(Joueur j);
void afficher_bateaux(Bateau *b);
int initialiser_joueur(Joueur *j, int plmt);
void free_joueur(Joueur *j);
void saisir_bateaux(Joueur *j, int plmnt);
int verifier_saisie_bateaux(int l, int c, int s, int taille, Joueur j);
int verifier_lignes(int s);
int verifier_colonne(int s);
int verifier_sens(int s);
int is_case_bateau(int l, int c, Bateau *b);
int dans_la_grille(int l, int c, int s,int taille);
int touche_bateau(int l, int c, Bateau *b);

#endif
