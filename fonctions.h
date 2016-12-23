/**
 * @file      fonctions.h
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 Décembre 2016
 * @brief     Définis les structures et les méthodes du jeu
 */
#ifndef FONCTIONS_H_
#define FONCTIONS_H_

#define NB_LIGNES 10
#define NB_COLONNES 10
#define NB_JOUEURS 2
#define NB_BATEAUX 5
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
	int sens; /*!< 0 haut; 1 droite; 2 bas; 3 gauche; */
	int etat; /*!< 1(true) en vie; 0(false) coulééééé; */
} Bateau;

/**
 * @brief      Coup joué
 * @details    Stocke les informations sur un coup joué (case visée et résultat)
 */
typedef struct Coup{
	int ligne;
	int colonne;
	int resultat; /*!< '.' inconnu; 'o' eau; '%d' bateau; 'c' coulé */
} Coup;

/**
 * @brief      Joueur
 * @details    
 */
typedef struct Joueur{
	char name[MAX_SAISIE];
	struct Bateau *bateaux; /*!< Tableau de NB_BATEAUX bateaux alloué dynamiquement */
	struct Coup *historique; /*!< Tableau de coups alloué dynamiquement. A l'initilisation, seulement BLOC_MALLOC cases sont allouées.*/
	int nb_coups; /*!< nombre de coups déjà joués par le joueur*/
} Joueur;

void afficher_grille(Joueur jo);
void afficher_joueur(Joueur j);
void afficher_bateaux(Bateau *b);
int initialiser_joueur(Joueur *j);
void free_joueur(Joueur *j);
void saisir_bateaux(Joueur *j);
int verifier_saisie_bateaux(int l, int c, int s, int taille, Joueur j);
int verifier_lignes(int s);
int verifier_colonne(int s);
int verifier_sens(int s);
int is_case_bateau(int l, int c, Bateau *b);
int dans_la_grille(int l, int c, int s,int taille);
int touche_bateau(int l, int c, Bateau *b);

/*
BIREF :
fonction initialisation
-afficher grille vide (test) = OK
-saisir joueur = OK
-initaliser le joueur = OK
-afficher joueur = OK
-saisir bateaux = OK
-afficher grille avec bateau = OK

fonction jeu
-saisir choix de la case
-fonction gagner (booleen)
-fonction jouer_coup qui prend un choix de case et vérifie dans le tableau de tableaux
-fonction afficher_resultat

algo :
	initialisation du jeu : 
		->saisir un joueur et ses bateaux (attention aux regles de placement)
		->afficher sa grille
	jeu :
		->afficher la grille avec l'historique de coups du joueur
		->saisir choix de la case
		->vérifier saisie
		->afficher le resultat du coup 
		->vérifier si le joueur n'a pas gagné
		->mettre à jour l'historique de coups
		->passer au joueur suivant
		->again and again 
		

*/

#endif