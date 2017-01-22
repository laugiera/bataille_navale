/**
 * @file      game.c
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 D�cembre 2016
 * @brief     Fonctions n�cessaires � l'algo du jeu
 * @details    ~
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "init.h"
#include "game.h"
#include "IA.h"

/**
 * @brief      cherche si un coup a d�j� �t� jou�
 * @param      l le charact�re de la ligne
 * @param	   c l'entier de la colonne
 * @param	   int ** grille de jeu
 * @return     boolean, vrai si d�j� jou�, faux sinon
 */
int deja_joue(int l, int c, int ** historique){
		if(historique[l-'A'][c]!='.'){
				printf("Vous avez d�j� jou� cette case, recommencez la saisie.\n");
				return 1;
			}
		return 0;
}

/**
 * @brief      donne le r�sultat d'un coup jou� (� l'eau ou touch�) et l'affiche
 * @param      l le charact�re de la ligne
 * @param	   c l'entier de la colonne
 * @param	   btx_adverses
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
		/*on retrouve le bateau touch� en recherchant son id dans le tableau*/
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
 * @brief      Saisis une case et v�rifie la saisie
 * @param      *l le caract�re de la ligne
 * @param	   *c l'entier de la colonne
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
 * @brief      cherche si le joueur a gagne ou non
 * @param	   Bateau* les bateaux adverses
 * @details    Pour que le joueur gagne, il faut que l'�tat de tous les btx adverses soient � 0 (coul�s)
 * @return     boolean	true si gagn�, false sinon
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
 * @brief      affiche l'�tat des bateaux du joueur courant
 * @param	   Bateau* les bateaux
 * @return     void
 */
void affiche_etat_bateaux(Bateau * bateaux){
	printf("\n\nVoici l'Etat de vos bateaux :\n");
	int i;
	for(i=0; i<NB_BATEAUX; i++){
		printf("Le bateau %d est %s\n",(bateaux+i)->id,(bateaux+i)->etat==0?"coul�":"en vie" );
	}
}

/**
 * @brief      Verifie si le bateau donn� est coul� ou non
 * @param      int** historique	la grille de jeu du joueur
 * @param	   Bateau* le bateau
 * @details    La fonction parcourt la matrice de jeu et compte le nombre d'occurence de l'id du bateau.
 * Si le nombre d'occurence = � la taillle du bateau alors il est coul�.
 * Si le bateau est coul�, son �tat est actualis� � false et la grille de jeu mise � jour
 * @return     boolean	true si coul�, false sinon
 */
int is_coule(int **historique, Bateau * b){
	int i,k, nb =0;
	for (i = 0; i < NB_LIGNES; i++)
	{
		for (k = 0; k < NB_COLONNES; k++)
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
 * @brief      Boucle de jeu principale
 * @details
 algo :
	initialisation du jeu :
		->saisir les joueurs et leurs bateaux
		->decider qui commence (aleatoire)
	jeu :
		->afficher la grille de jeu du joueur qui commence
		->saisir choix de la case
		->v�rifier saisie
			>> si mauvaise saisie : retour � l'�tape du dessus
		->afficher le resultat du coup
		->mettre � jour la grille de jeu
		->v�rifier si le joueur n'a pas gagn�
			>> si le joueur a gagn� : *fin de la boucle et du jeu
		->passer au joueur suivant
		->again and again
 * @return    void
 */
void game(void) {
	srand(time(NULL));

	welcome_screen();
	rules_screen();
	int IA = menu_screen();

	Joueur joueurs[2];
	int plmt = menu_screenPlacemnt();
	Bateau * btx_adverses;
	int joueur_courant, res_coup, l, c;
	int jouer = 1;

	/*VS Joueur*/
	if(IA == 1){
		printf ("\n==========================[JOUEUR 1 - BIENVENUE !]=============================\n\n");
	    initialiser_joueur(&joueurs[0], plmt);
	    system_message("                      Faites ENTRER pour continuer");
		cls();
	    printf ("\n==========================[JOUEUR 2 - BIENVENUE !]=============================\n\n");
	    initialiser_joueur(&joueurs[1], plmt);
	    system_message("                      Faites ENTRER pour continuer");
		cls();
		printf ("\n============================[DEBUT DU JEU]===================================\n\n");

		joueur_courant = (rand()%2); /*1 ou 0*/

		printf("C'est le Joueur %s qui commence ! \n",joueurs[joueur_courant].name);

		while(jouer) /*condition � changer*/
		{
			printf ("\n=========================[A VOTRE TOUR %s!]==============================\n",joueurs[joueur_courant].name);

			affiche_etat_bateaux(joueurs[joueur_courant].bateaux);

			/*saisie de la case*/
			afficher_grille(joueurs[joueur_courant],1);
			saisir_coup(&l,&c,joueurs[joueur_courant].historique);

			/*on r�cup�re les bateaux adverses pour comparer avec la case choisie*/
			if(joueur_courant == 1)
				btx_adverses = joueurs[0].bateaux;
			else
				btx_adverses = joueurs[1].bateaux;
			res_coup = resultat_coup(l,c,btx_adverses,joueurs[joueur_courant].historique);

			/*on met � jour la grille de jeu*/
			joueurs[joueur_courant].historique[l-'A'][c] = res_coup;
			afficher_grille(joueurs[joueur_courant],1);

                /*si le joueur a gagne on sort de la boucle*/
                if(gagne(btx_adverses)){

                    printf("\n=============================[VOUS AVEZ GAGNE !]================================\n");
                    printf("\n=============================[FIN DE LA PARTIE !]===============================\n");
                    jouer = 0;

                }

                /*sinon on continue et on passe au joueur suivant*/
                else {

                    system_message("                      Faites ENTRER pour continuer");
                    cls();
                    /*on passe au joueur adverse*/
                    if(joueur_courant == 1)
                        joueur_courant = 0;
                    else
                        joueur_courant = 1;
            }

            free_joueur(&joueurs[0]);
            free_joueur(&joueurs[1]);
        }
	}

	/*VS IA*/
	else if (IA == 2){

        printf ("\n==========================[JOUEUR 1 - BIENVENUE !]=============================\n\n");
	    initialiser_joueur(&joueurs[0], plmt);
	    system_message("                      Faites ENTRER pour continuer");
		cls();

        initialiser_IA (&joueurs[1], plmt);

        joueur_courant = (rand()%2); /*1 ou 0*/
		printf("C'est le Joueur %s qui commence ! \n",joueurs[joueur_courant].name);

		while(jouer) /*condition � changer*/
		{
			printf ("\n=========================[A VOTRE TOUR %s!]==============================\n",joueurs[joueur_courant].name);

			affiche_etat_bateaux(joueurs[joueur_courant].bateaux);

			/*saisie de la case*/
			afficher_grille(joueurs[joueur_courant],1);

			void tir () {
                if (joueur_courant == 0)
                    saisir_coup(&l,&c,joueurs[joueur_courant].historique);
                else
                    Niveau0(&l,&c,joueurs[joueur_courant].historique);
			}

			/*on r�cup�re les bateaux adverses pour comparer avec la case choisie*/
			if(joueur_courant == 1)
				btx_adverses = joueurs[0].bateaux;
			else
				btx_adverses = joueurs[1].bateaux;
			res_coup = resultat_coup(l,c,btx_adverses,joueurs[joueur_courant].historique);

			/*on met � jour la grille de jeu*/
			joueurs[joueur_courant].historique[l-'A'][c] = res_coup;
			afficher_grille(joueurs[joueur_courant],1);

                /*si le joueur a gagne on sort de la boucle*/
                if(gagne(btx_adverses)){

                    printf("\n=============================[VOUS AVEZ GAGNE !]================================\n");
                    printf("\n=============================[FIN DE LA PARTIE !]===============================\n");
                    jouer = 0;

                }

                /*sinon on continue et on passe au joueur suivant*/
                else {

                    system_message("                      Faites ENTRER pour continuer");
                    cls();
                    /*on passe au joueur adverse*/
                    if(joueur_courant == 1)
                        joueur_courant = 0;
                    else
                        joueur_courant = 1;
            }

            free_joueur(&joueurs[0]);
            free_joueur(&joueurs[1]);
        }
	}

}

