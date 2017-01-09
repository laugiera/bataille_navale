/**
 * @file      game.c
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 Décembre 2016
 * @brief     Fonctions nécessaires à l'algo du jeu
 * @details    ~
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "init.h"
#include "game.h"


/**
 * @brief      Boucle de jeu principale
 * @details    
 algo :
	initialisation du jeu : 
		->saisir les joueurs et leurs bateaux 
		->decider qui commence (aleatoire)
	jeu :
		->afficher la grille de jeu du joueur qui commence
		->saisir choix de la case
		->vérifier saisie
			>> si mauvaise saisie : retour à l'étape du dessus
		->afficher le resultat du coup 
		->mettre à jour la grille de jeu
		->vérifier si le joueur n'a pas gagné
			>> si le joueur a gagné : *fin de la boucle et du jeu
		->passer au joueur suivant
		->again and again 
 * @return    void
 */
void game(void) {
	srand(time(NULL));

	/*ecrans d'accueil*/
	welcome_screen();
	rules_screen();
	int IA = menu_screen();

	/*variables utiles*/
	Joueur joueurs[2];
	Bateau * btx_adverses;
	int joueur_courant, res_coup, l, c;
	int jouer = 1;

	/*MODE VS Joueur*/
	if(IA == 1){
		printf ("\n============================[JOUEUR 1 - BIENVENUE !]===================================\n");
	    initialiser_joueur(&joueurs[0]);
	    system_message("Entrée pour continuer");
		cls();
	    printf ("\n============================[JOUEUR 2 - BIENVENUE !]===================================\n");
	    initialiser_joueur(&joueurs[1]);
	    system_message("Entrée pour continuer");
		cls();
		printf ("\n============================[DEBUT DU JEU]=============================================\n");
		joueur_courant = (rand()%2); /*1 ou 0*/

		printf("C'est le Joueur %s qui commence ! \n",joueurs[joueur_courant].name);

		while(jouer) 
		{
			printf("\n============================[A VOTRE TOUR %s!]==========================================\n",joueurs[joueur_courant].name);
			affiche_etat_bateaux(joueurs[joueur_courant].bateaux);
			/*saisie de la case*/
			afficher_grille(joueurs[joueur_courant],1);
			saisir_coup(&l,&c,joueurs[joueur_courant].historique);
			/*on récupère les bateaux adverses pour comparer avec la case choisie*/
			if(joueur_courant == 1)
				btx_adverses = joueurs[0].bateaux;
			else
				btx_adverses = joueurs[1].bateaux;
			res_coup = resultat_coup(l,c,btx_adverses,joueurs[joueur_courant].historique);
			/*on met à jour la grille de jeu*/
			joueurs[joueur_courant].historique[l-'A'][c] = res_coup;
			afficher_grille(joueurs[joueur_courant],1);
			/*si le joueur a gagne on sort de la boucle*/
			if(gagne(btx_adverses)){
				printf("\n=============================[VOUS AVEZ GAGNE !]======================================\n");
				printf("\n=============================[FIN DE LA PARTIE !]=====================================\n");
				jouer = 0;
			}
			/*sinon on continue et on passe au joueur suivant*/
			else {
				system_message("Entrée pour continuer");
				cls();
				/*on passe au joueur adverse*/
				if(joueur_courant == 1)
					joueur_courant = 0;
				else
					joueur_courant = 1;
			}
		}

		free_joueur(&joueurs[0]);
		free_joueur(&joueurs[1]);
	}

	/*VS IA*/
	else if (IA == 2){

	}
}

/**
 * @brief      Saisis une case et vérifie la saisie
 * @param      *l le caractère de la ligne
 * @param	   *c l'entier de la colonne
 * @param	   int ** grille de jeu
 * @return     void
 */
void saisir_coup(int* l, int* c, int **historique){
	do{
		printf("Saisir une ligne (A - %c):\n",'A'+NB_LIGNES-1);
		(*l) = fgetc(stdin);
		f_purge(stdin);
		printf("Saisir une colonne (1-%d):\n",NB_COLONNES);
		scanf("%d",c);
		f_purge(stdin);
	}while(verifier_lignes(*l)==0 || verifier_colonne(*c)==0 || deja_joue(*l,*c,historique));

}
/**
 * @brief      cherche si un coup a déjà été joué
 * @param      l le charactère de la ligne
 * @param	   c l'entier de la colonne
 * @param	   int ** grille de jeu
 * @return     boolean, vrai si déjà joué, faux sinon
 */
int deja_joue(int l, int c, int ** historique){
		if(historique[l-'A'][c]!='.'){
				printf("Vous avez déjà joué cette case, recommencez la saisie.\n");
				return 1;
			}
		return 0;
}

/**
 * @brief      donne le résultat d'un coup joué (à l'eau, touché ou coulé) et l'affiche.
 * @param      l le charactère de la ligne
 * @param	   c l'entier de la colonne
 * @param	   Bateau * btx_adverses
 * @param	   int ** grille de jeu
 * @return     int (valeur ASCII du char 'o' ou de l'id du bateau)
 */
int resultat_coup(int l, int c, Bateau * btx_adverses, int **historique){
	printf("\n\nCASE %c%d \n",l,c );
	int res = is_case_bateau(l-'A',c,btx_adverses);
	if(res == -1){
		printf("\nRESULTAT : A l'eau ! \n");
		return 'o';
	}
	else
	{	
		int i = 0;
		/*on retrouve le bateau touché en recherchant son id dans le tableau*/
		while(res != (btx_adverses+i)->id){
			i++;
		}
		Bateau * bateau_touche = btx_adverses+i;
		if(is_coule(historique,bateau_touche))
		{
			printf("\nRESULTAT : COULEYYY ! Bateau %d \n",res );
			return 'X';
		}
		else
			printf("\nRESULTAT : TOUCHEYY ! Bateau %d \n",res );
	}
	return res+'0';
}

/**
 * @brief      Verifie si le bateau donné est coulé ou non
 * @param      int** historique	la grille de jeu du joueur
 * @param	   Bateau* le bateau
 * @details    La fonction parcourt la matrice de jeu et compte le nombre d'occurence de l'id du bateau. 
 * Si le nombre d'occurence = à la taillle du bateau alors il est coulé.
 * Si le bateau est coulé, son état est actualisé à false et la grille de jeu mise à jour
 * @return     boolean	true si coulé, false sinon
 */
int is_coule(int **historique, Bateau * b){
	int i,k, nb =1;
	for (i = 0; i < NB_LIGNES; i++)
	{
		for (k = 1; k <= NB_COLONNES; k++)
		{
			if(historique[i][k]==b->id+'0')
				nb++;
		}
	}
	if(nb == b->taille){
		b->etat = 0;
		for (i = 0; i < NB_LIGNES; i++)
		{
			for (k = 1; k <= NB_COLONNES; k++)
			{
				if(historique[i][k]==b->id+'0')
					historique[i][k]='X';
			}
		}		
		return 1;	
	}
	return 0;	
}

/**
 * @brief      cherche si le joueur a gagne ou non
 * @param	   Bateau* les bateaux adverses
 * @details    Pour que le joueur gagne, il faut que l'état de tous les btx adverses soient à 0 (coulés)
 * @return     boolean	true si gagné, false sinon
 */
int gagne(Bateau * btx_adverses){
	int i, res = 1;
	for(i=0; i < NB_BATEAUX; i++){
		if((btx_adverses+i)->etat == 1)
			res = 0;
	}
	return res;
}

/**
 * @brief      affiche l'état des bateaux du joueur courant
 * @param	   Bateau* les bateaux
 * @return     void
 */
void affiche_etat_bateaux(Bateau * bateaux){
	printf("\n\nVoici l'état de vos bateaux :\n");
	int i;
	for(i=0; i<NB_BATEAUX; i++){
		printf("Le bateau %d est %s\n",(bateaux+i)->id,(bateaux+i)->etat==0?"coulé":"en vie" );
	}
}

