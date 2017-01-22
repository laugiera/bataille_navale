/**
 * @file      init.h
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 D�cembre 2016
 * @brief     D�finis les structures et les m�thodes du jeu - Ici se trouvent toutes les fonctions n�cessaires � l'initialisation du jeu
 */
#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

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
	int id; /*!< Commence � 1*/
	int ligne;
	int colonne;
	int taille;
	int sens; /*!< 0 vertical; 1 horizontal; */
	int etat; /*!< 1(true) en vie; 0(false) coul�����; */
} Bateau;

/**
 * @brief      Joueur
 * @details
 * @champs : historique = grille de jeu (0 � NB_LIGNES-1 lignes, 1 � NB_COLONNES colonnes).
 * La valeur vaut '.' � l'initialisation
 * puis '%d' bateau.id (touch�), ou 'o' (eau), 'X' (coul�)
 * ATTENTION : La grille du joueur 1 fonctionne avec les bateaux du Joueur 2 et vice-versa !
 */
typedef struct Joueur{
	char name[MAX_SAISIE];
	struct Bateau *bateaux; /*!< Tableau de NB_BATEAUX bateaux allou�e dynamiquement*/
	int **historique; /*!< Matrice de jeu allou�e dynamiquement. */
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
void saisir_bateaux(Joueur *j, int plmt);
int verifier_saisie_bateaux(int l, int c, int s, int taille, Joueur j);
int verifier_lignes(int s);
int verifier_colonne(int s);
int verifier_sens(int s);
int is_case_bateau(int l, int c, Bateau *b);
int dans_la_grille(int l, int c, int s,int taille);
int touche_bateau(int l, int c, Bateau *b);

#endif
