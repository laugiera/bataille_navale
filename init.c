/**
 * @file      init.c
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 Décembre 2016
 * @brief     Définis les structures et les méthodes du jeu
 * @details    ~
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "init.h"

#include "ia.h"




/**
 * @brief      Purge le buffer pour la saisie au clavier
 * @param      stdin (dans notre cas)
 * @return     void
 */
void f_purge(FILE *fp)
{
	if (fp != NULL)
	{
		int c;

		while ((c = fgetc(fp)) != '\n' && c != EOF)
		{
		}
	}
}
/**
 * @brief   Efface tout ce qu'il y a affiché à l'écran
 * @return    void
 */
 void cls (void)
{
   system(CLEAN_SCREEN);
}

/**
 * @brief     Affiche un message à l'utilisateur et lui demande d'appuyer sur entrée
 * param 	char *, le message a afficher
 * @return    void
 */
void system_message (char *message) {
	char ch = '\0';
	printf ("%s", message);
    scanf  ("%c", &ch);
}

/**
 * @brief      Ecran de bienvenue
 * @return    void
 */
void welcome_screen (void) {
    printf ("\n\n");
    printf ("=============================================================================\n");
	printf ("  = XXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX      XXXXX XX  XX XX XXXX   =\n");
	printf ("  = XX  XX XX  XX   XX     XX   XX     XX         XX     XX  XX XX XX  XX =\n");
	printf ("  = XXXXX  XX  XX   XX     XX   XX     XXXX  ====  XXXX  XXXXXX XX XXXX   =\n");
	printf ("  = XX  XX XXXXXX   XX     XX   XX     XX    ====     XX XX  XX XX XX     =\n");
	printf ("  = XXXXX  XX  XX   XX     XX   XXXXXX XXXXXX     XXXXX  XX  XX XX XX     =\n");
	printf ("=============================================================================\n");
	printf ("  =                XXXXXX     XXXX    XX     XX   XXXXXX                  =\n");
	printf ("  =                XX        XX  XX   XXXX XXXX   XX                      =\n");
	printf ("  =                XX  XXXX  XX  XX   XX  X  XX   XXXX                    =\n");
	printf ("  =                XX   XX   XXXXXX   XX     XX   XX                      =\n");
	printf ("  =                XXXXXXX   XX  XX   XX     XX   XXXXXX                  =\n");
	printf ("  =                                                                       =\n");
	printf ("==================[the most epic war in this fucking world]==================\n");
	printf ("\n\n");
	printf("**** VIENS TESTER TES APTITUDES JEUNE ELU PADAWAN DU ROYAUME DES COOCKIES ****\n\n");
	printf ("\n\n");
	system_message("                      Faites ENTRER pour continuer");
	cls();
}

/**
 * @brief      Ecran des règles
 * @return    void
 */
void rules_screen (void){
    printf ("\n");
    printf ("============================[REGLES DU JEU:]===================================\n");
    printf (" |                                                                           |\n");
	printf (" | 1. C'est un jeu avec deux joueurs.                                        |\n");
	printf (" | 2. Vous etes le Joueur 1 et le Joueur 2 est un ami ou bien l'ordinateur.  |\n");
	printf (" | 3. Les bateaux seront places manuellement ou aleatoirement.               |\n");
	printf (" | 4. Il y a cinq navires a placer du plus long au plus court;               |\n");
	printf (" |   1 Carrier de 5 cases, 1 Battleship de 4 cases, 1 Cruiser de 3 cases,    |\n");
	printf (" |   1 Submarine de 3 cases, 1 Destroyer de 2 cases.                         |\n");
	printf (" | 5. L ordinateur selectionne de maniere aleatoire la personne qui va       |\n");
	printf (" |   commencer.                                                              |\n");
	printf (" | 6. Le jeu commence, chaque joueur doit tenter de deviner l'emplacement    |\n");
	printf (" |   des navires adverses sur le plateau;                                    |\n");
	printf (" | 7. Le premier joueur qui a deviney l'emplacement de tous les navires      |\n");
    printf (" |   adverses gagne.                                                         |\n");
	printf ("==============================================================================\n\n");
	system_message("                      Faites ENTRER pour continuer");
	cls();
}

/**
 * @brief     Ecran de menu
 * @return    1 (Joueur vs Ordinateur) or 2 (Joueur vs joueur)
 */
int menu_screenIA(void){
	int mode = 0;
	printf ("\n");
    printf ("============================[MENU:]===================================\n");
    printf (" |                                                                   |\n");
	printf (" | Choisissez un mode :                                              |\n");
	printf (" | 1. MODE JOUEUR VS JOUEUR                                          |\n");
	printf (" | 2. MODE JOUEUR VS ORDINATEUR.                                     |\n");
	printf ("======================================================================\n\n");
	do{
		printf("Saisir le mode (1 ou 2) :\n");
		scanf("%d",&mode);
		f_purge(stdin);
	}while(mode != 1 && mode != 2);
	system_message("                      Faites ENTRER pour continuer");
	cls();
	return mode;
}

/**
 * @brief     Ecran de menu pour placement bateaux
 * @return    1 (manuel) or 2 (aléatoire)
 */
int menu_screenPlacemnt(void){
	int mode = 0;
	printf ("\n");
    printf ("============================[MENU:]===================================\n");
    printf (" |                                                                   |\n");
	printf (" | Choisissez un mode de placement des bateaux :                     |\n");
	printf (" | 1. MODE MANUEL.                                                   |\n");
	printf (" | 2. MODE ALEATOIRE.                                                |\n");
	printf ("======================================================================\n\n");
	do{
		printf("Saisir le mode (1 ou 2) :\n");
		scanf("%d",&mode);
		f_purge(stdin);
	}while(mode != 1 && mode != 2);
	system_message("                      Faites ENTRER pour continuer");
	cls();
	return mode;
}

/**
 * @brief      Affiche la grille de jeu
 * @details    La grille et les bateaux de @a jo ('.' inconnu; 'o' eau; '%d' bateau; 'X' coulé)
 * @param    jo		Joueur correspondant à la grille
 * @param      etat	Booléen : 0 = grille de placement des bateaux du joueur et 1 = grille de jeu du joueur
 * @return    void
 */
void afficher_grille(Joueur jo, int etat){ /*modifier chiffre colonne*/
	int i,j,k,lettre='A';
	/*
	printf("\n\n   |");
	for (k = 1; k <= NB_COLONNES; k++)
	*/
	printf("\n\n   |");
	for (k = 0; k < NB_COLONNES; k++)
		printf(" %d |",k );
	printf("\n");
	for (i = 0; i < NB_LIGNES; i++)
	{
		printf(" %c |",lettre);
		lettre++;
		for (j = 0; j < NB_COLONNES; j++)
		{
			if(etat == 1) /*affichage grille de jeu*/
				printf(" %c |",jo.historique[i][j] );
			else if(etat == 0) /*affichage placement bateaux du joueur*/
			{
			  int case_b = is_case_bateau(i,j,jo.bateaux);
		      if(case_b!= -1) /*si case de bateau */
		        printf(" %d |",case_b );
		      else  /*sinon */
		        printf(" . |");
			}

		}
		printf("\n");
	}
}

/**
 * @brief      Affiche le joueur et sa grille de jeu
 * @param    j		Joueur correspondant
 * @return    void
 */
void afficher_joueur(Joueur j){
	printf("Joueur %s\n",j.name);
	printf("Bateaux :\n");
	/*afficher_bateaux(j.bateaux);*/
	printf("Historique :\n");
	afficher_grille(j,1);
}

/**
 * @brief      Affiche les bateaux d'un joueur
 * @param      b, le tableau de Bateaux du joueur
 * @return     void
 */
void afficher_bateaux(Bateau *b){
	int i;
	for (i = 0; i < NB_BATEAUX; i++)
	{
		printf("\tBateau %d de taille %d\n", (b+i)->id,(b+i)->taille);
		printf("\t\tSens : %d\n", (b+i)->sens);
		printf("\t\tLigne %c et colonne %d\n",(b+i)->ligne,(b+i)->colonne );
		printf("\t\tEtat : %d\n", (b+i)->etat);
	}
}


/**
 * @brief      Initialise le joueur
 * @param      j, le joueur
 * @details    Le joueur saisit son nom. L'historique est alloué est initialisé à O. Les bateaux sont alloués puis saisis.
 * @return     EXIT_FAILURE si les malloc fail, EXIT_SUCESS sinon
 */

int initialiser_joueur(Joueur *j, int mode_placement){

	int i,k;
	/*pseudo*/
	printf("Quel est ton pseudo ?\n");
	scanf("%s",j->name);
	f_purge(stdin);
	/*historique - grille de jeu - allocation*/
	j->historique = malloc((NB_LIGNES)*sizeof(int*));
	if(j->historique == NULL)
		return EXIT_FAILURE;
	else {
		for (i = 0; i < NB_LIGNES; i++){
    		j->historique[i] = malloc(sizeof(int) * NB_COLONNES+1);
    		if(j->historique[i]==NULL)
    			return EXIT_FAILURE;
		}
	}
	/*historique - initialisation*/
	for (i = 0; i < NB_LIGNES; i++)
	{
		for (k = 0; k < NB_COLONNES; k++)
		{
			j->historique[i][k]='.';
		}
	}
	/*bateaux*/
	j->bateaux = malloc(NB_BATEAUX * sizeof(Bateau));
	if(j->bateaux == NULL)
		return EXIT_FAILURE;
	saisir_bateaux(j, mode_placement);
	return EXIT_SUCCESS;
}

/**
 * @brief      libère la mémoire allouée au joueur
 * @param      j, le joueur
 * @return     void
 */
void free_joueur(Joueur *j){
	int i;
	free(j->bateaux);
	for (i = 0; i < NB_LIGNES; i++)
	{
		free(j->historique[i]);
	}
	free(j->historique);
}

/**
 * @brief      le joueur saisit les emplacements de ses bateaux
 * @param      j, le joueur
 * @details    le joueur saisit une case, un sens d'orientation et le jeu vérifie la saisie. Si la saisie est bonne, le bateau est initialisé et la grille maj affichée
 * @return     void
 */
void saisir_bateaux(Joueur *j, int mode_placement){

            srand(time(NULL));
            int tailles[NB_BATEAUX]={5,4,3,3,2}; /*!< Règles : 1 bateau de taille 5, 1 de taille 4, 2 de taille 3, 1 de taille 2*/
            int i,colonne,ligne,sens;
    if (mode_placement==1){
                printf("Saisissez vos bateaux (coordonnées de la première case et sens):\n Sens : 0 vertical (vers le bas); 1 horizontal (vers la droite); \n");
                afficher_grille(*j,0);
            for (i = 0; i < NB_BATEAUX; i++)
            {

                (j->bateaux+i)->id=i+1;
                printf("Saisie du bateau %d, taille %d\n",i,tailles[i]);
                do {
                    printf("ligne : ");
                    ligne = fgetc(stdin);
                    f_purge(stdin);
                    printf("colonne : ");
                    scanf("%d",&colonne);
                    f_purge(stdin);
                    printf("sens : ");
                    scanf("%d",&sens);
                    f_purge(stdin);
                    /*tq saisie mauvaise*/
                }while(verifier_saisie_bateaux(ligne, colonne, sens,tailles[i],*j, mode_placement)==0);

                /*initialisation bateau*/
                (j->bateaux+i)->taille=tailles[i];
                (j->bateaux+i)->nbTouche = 0;
                (j->bateaux+i)->etat = 1;
                (j->bateaux+i)->ligne = ligne;
                (j->bateaux+i)->colonne = colonne;
                (j->bateaux+i)->sens = sens;
                /*grille mise à jour */
                afficher_grille(*j,0);

            }
        }
    else
    {
            for (i = 0; i < NB_BATEAUX; i++)
            {	
                (j->bateaux+i)->id=i+1;
                do {
                    placement_aleatoire(tailles[i], &colonne, &ligne, &sens);
                }while(verifier_saisie_bateaux(ligne, colonne, sens,tailles[i],*j, mode_placement)==0);

                /*initialisation bateau*/
                (j->bateaux+i)->taille=tailles[i];
                (j->bateaux+i)->nbTouche = 0;
                (j->bateaux+i)->etat = 1;
                (j->bateaux+i)->ligne = ligne;
                (j->bateaux+i)->colonne = colonne;
                (j->bateaux+i)->sens = sens;
            }
            afficher_grille(*j,0);
    }

}

/**
 * @brief      vérifie le placement d'un bateau
 * @param      l, un entier pour la ligne
 * @param 	   c, un entier pour la colonne
 * @param 	   s, un entier pour l'orientation
 * @param 	   taille, un entier pour la taille du bateau concerné
 * @param 	   j, le joueur
 * @param 	   mode_placement, int 1 pour manuel, 2 pour aléatoire
 * @details    Pour qu'un placement soit valide, il faut que la saisie soit correcte, conforme à la grille (le bateau ne sort pas). Il faut que la case ne chevauche pas un autre bateau ET qu'elle ne touche pas un autre bateau. Le mode de placement décide de l'affichage ou non des messages d'erreur.
 * @return     booléen. FALSe si mauvais placement, TRUE sinon
 */
int verifier_saisie_bateaux(int  l, int c, int  s, int taille, Joueur j, int mode_placement){

	/* l_index : index de la ligne dans la matrice de la grille, l est le code ASCII de la ligne*/
	int l_index = l - 'A' ;
	int i;

	/*saisie correcte */
	if(verifier_lignes(l)==0 ||
		verifier_colonne(c)==0 || verifier_sens(s)==0){
		printf("Erreur de saisie - \n");
		return 0;
	}
	/*conforme à la grille, le bateau ne sort pas*/
	if(dans_la_grille(l,c,s,taille) == 0) {
		printf("Placement hors de la grille\n");
		return 0;
	}
	/*conforme aux regles (pas de chevauchement de bateaux et pas de bateau qui se touchent)*/
	/*on part du principe que c'est bon et on cherche les exceptions.*/

	/*il faut le faire pour chaque case du bateau*/

	/*parcourir vers le bas*/
	if (s == 0) {
		for(i = l_index; i<l_index+taille; i++) {
			if(touche_bateau(i,c,j.bateaux)) {
				if (mode_placement == 1) {
					printf("Erreur - Les bateaux ne doivent pas se toucher ni se chevaucher!!! GROS COQUIN!!!! m'enfin voyons\n");
				}
				return 0;
			}

		}
	}
	/*parcourir vers la droite*/
	else if (s == 1) {
		for(i = c; i<c+taille; i++) {
			if(touche_bateau(l_index,i,j.bateaux)) {
				if (mode_placement == 1) {
					printf("Erreur - Les bateaux ne doivent pas se toucher ni se chevaucher!!! GROS COQUIN!!!! m'enfin voyons\n");
				}
				return 0;
			}

		}
	}

	return (1);

}

/**
 * @brief      vérifie qu'une ligne saisie est conforme à la grille
 * @param      s, un entier pour la ligne
 * @details    la ligne est entre 'A' et 'A'+NB_LIGNES
 * @return     booléen
 */
int verifier_lignes(int  s){
	printf("ligne : %c, min : %c, max : %c \n",s, 'A', 'A'+NB_LIGNES-1);
	return (s >='A'&& s <('A'+NB_LIGNES));
}

/**
 * @brief      vérifie qu'une colonne saisie est conforme à la grille
 * @param      s, un entier pour la colonne
 * @details    la colonne est entre 1 et NB_COLONNES
 * @return     booléen
 */
int verifier_colonne(int s){
	return (s >= 0 && s < NB_COLONNES);
}

/**
 * @brief      vérifie que le sens/orientation saisi est réalisable
 * @param      s, un entier pour le sens
 * @details    0 haut; 1 droite;
 * @return     booléen
 */
int verifier_sens(int s){
	return (s ==0 || s == 1);
}

/**
 * @brief      regarde si un bateau occupe la case donnée
 * @param      l, un entier de 0 à NB_LIGNES-1 pour la ligne (PAS LE CODE ASCII DE LA LETTRE)
 * @param      c, un entier pour la colonne
 * @param      b, tableau de bateaux du joueur
 * @return     -1 si la case est libre, 0 s'il n'y a aucun bateau placé sur la grille (initialisation), bateau.id sinon
 */
int is_case_bateau(int l, int c, Bateau *b){
	int i, resultat = -1;
	for (i = 0; i < NB_BATEAUX; i++)
	{
		/*premiere case*/
		if((b+i)->ligne == 'A'+l && (b+i)->colonne == c) {
			resultat = (b+i)->id;
		}

		/*case en bas*/
		else if ((b+i)->sens == 0 &&
			(b+i)->colonne == c &&
			'A'+l>(b+i)->ligne &&
			'A'+l<=(b+i)->ligne+((b+i)->taille-1)) {
			resultat = (b+i)->id;
		}

		/*case à droite*/
		else if ((b+i)->sens == 1 &&
			(b+i)->ligne == 'A'+l &&
			c > (b+i)->colonne &&
			c <=(b+i)->colonne+((b+i)->taille-1)) {
			resultat = (b+i)->id;
		}
	}
	return resultat;
}

/**
 * @brief      regarde si un bateau sort de la grille
 * @param      l, un entier pour la ligne
 * @param 	   c, un entier pour la colonne
 * @param 	   s, un entier pour l'orientation
 * @param 	   taille, un entier pour la taille du bateau concerné
 * @return     booléen, FALSE si ça sort de la grille
 */
int dans_la_grille(int l, int c, int s,int taille){

	/*case en bas*/
	/*printf("l = %c l+taille = %c, max = %c\n",l,l+taille,'A'+NB_LIGNES );*/
	if (s == 0 && l+taille <= 'A'+NB_LIGNES){
		return 1;
	}
	/*case à droite*/
	else if (s == 1 && c+taille < NB_COLONNES+1)
		return 1;
	return 0;
}

/**
 * @brief      regarde si une case donnée est déjà occupée ou touche une case déjà occcupée par un bateau du joueur
 * @param      l, un entier pour la ligne (correspondant à l'index de la ligne : 0 à NB_LIGNE-1, pas au code ASCII)
 * @param 	   c, un entier pour la colonne
 * @param 	   b, tableau de bateaux du joueur
 * @details    la fonction regarde toutes les cases mitoyennes à la case donnée et vérifie si ce sont des cases occupées ou non
 * @return     booléen
 */
int touche_bateau(int l, int c, Bateau *b){
		/*
		 *g = l, c-1
		 *d = l, c+1
		 *h = l-1, c
		 *b = l+1, c
		 *diag_hg = l-1,c-1
		 *diag_hd = l-1,c+1
		 *diag_bg = l+1,c-1
		 *diag_bd = l+1,c+1
		*/
	return (
		is_case_bateau(l, c-1, b)!=-1 ||
		is_case_bateau(l, c-1, b)!=-1 ||
		is_case_bateau(l, c+1, b)!=-1 ||
		is_case_bateau(l-1, c, b)!=-1 ||
		is_case_bateau(l+1, c, b)!=-1 ||
		is_case_bateau(l-1, c-1, b)!=-1 ||
		is_case_bateau(l-1, c+1, b)!=-1 ||
		is_case_bateau(l+1, c-1, b)!=-1 ||
		is_case_bateau(l+1, c+1, b)!=-1
		);
}
