/**
 * @file      init.c
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 D�cembre 2016
 * @brief     D�finis les structures et les m�thodes du jeu
 * @details    ~
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "init.h"



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
 * @brief   Efface tout ce qu'il y a affich� � l'�cran
 * @return    void
 */
 void cls (void)
{
   system(CLEAN_SCREEN);
}

/**
 * @brief     Affiche un message � l'utilisateur et lui demande d'appuyer sur entr�e
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
 * @brief      Ecran des r�gles
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
 * @return    2 (Joueur vs Ordinateur) or 1 (Joueur vs joueur)
 */
int menu_screen(void){
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
 * @return    1 (manuel) or 2 (al�atoire)
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
 * @details    La grille et les bateaux de @a jo ('.' inconnu; 'o' eau; '%d' bateau; 'X' coul�)
 * @param    jo		Joueur correspondant � la grille
 * @param      etat	Bool�en : 0 = grille de placement des bateaux du joueur et 1 = grille de jeu du joueur
 * @return    void
 */
void afficher_grille(Joueur jo, int etat){ //modifier chiffre colonne
	int i,j,k,lettre='A';
	printf("   |");
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
 * @details    Le joueur saisit son nom. L'historique est allou� est initialis� � O. Les bateaux sont allou�s puis saisis.
 * @return     EXIT_FAILURE si les malloc fail, EXIT_SUCESS sinon
 */

int initialiser_joueur(Joueur *j, int plmt){

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
	saisir_bateaux(j, plmt);
	return EXIT_SUCCESS;
}

/**
 * @brief      lib�re la m�moire allou�e au joueur
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
 * @details    le joueur saisit une case, un sens d'orientation et le jeu v�rifie la saisie. Si la saisie est bonne, le bateau est initialis� et la grille maj affich�e
 * @return     void
 */
void saisir_bateaux(Joueur *j, int plmt){

            srand(time(NULL));
            int tailles[NB_BATEAUX]={5,4}; /*!< R�gles : 1 bateau de taille 5, 1 de taille 4, 2 de taille 3, 1 de taille 2*/
            int i,colonne,ligne,sens;
    if (plmt==1){
                printf("Saisissez vos bateaux (coordonn�es de la premi�re case et sens):\n Sens : 0 vertical (vers le bas); 1 horizontal (vers la droite); \n");
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
                }while(verifier_saisie_bateaux(ligne, colonne, sens,tailles[i],*j)==0);

                /*initialisation bateau*/
                (j->bateaux+i)->taille=tailles[i];
                (j->bateaux+i)->etat = 1;
                (j->bateaux+i)->ligne = ligne;
                (j->bateaux+i)->colonne = colonne;
                (j->bateaux+i)->sens = sens;
                /*grille mise � jour */
                afficher_grille(*j,0);

            } //Fin for
        }//Fin if
    else
    {

            afficher_grille(*j,0);
            for (i = 0; i < NB_BATEAUX; i++)
            {
                int nbr_colonne=(rand() % (9 - 0 + 1)) + 0;
                int lettre=(rand() % (9 - 0 + 1)) + 0;
                char alphabet[] = "ABCDEFGHIJ";

                (j->bateaux+i)->id=i+1;
                do {
                        if (nbr_colonne>5 && lettre<=5)
                        {
                            sens=0;
                        }
                        else if (lettre>5 && nbr_colonne<=5)
                        {
                            sens=1;
                        }
                        else if (nbr_colonne<=5 && lettre<=5)
                        {
                            sens=(rand()%2);
                        }
                        else if (lettre>5 && nbr_colonne>5)
                        {
                             nbr_colonne=(rand() % (9 - 0 + 1)) + 0;
                             lettre=(rand() % (9 - 0 + 1)) + 0;
                        }
                        ligne = alphabet[lettre];
                        colonne=nbr_colonne;

                }while(verifier_saisie_bateaux(ligne, colonne, sens,tailles[i],*j)==0);

                /*initialisation bateau*/
                (j->bateaux+i)->taille=tailles[i];
                (j->bateaux+i)->etat = 1;
                (j->bateaux+i)->ligne = ligne;
                (j->bateaux+i)->colonne = colonne;
                (j->bateaux+i)->sens = sens;
                /*grille mise � jour */
                afficher_grille(*j,0);

            } //Fin for
    }

}

/**
 * @brief      v�rifie le placement d'un bateau
 * @param      l, un entier pour la ligne
 * @param 	   c, un entier pour la colonne
 * @param 	   s, un entier pour l'orientation
 * @param 	   taille, un entier pour la taille du bateau concern�
 * @param 	   j, le joueur
 * @details    Pour qu'un placement soit valide, il faut que la saisie soit correcte, conforme � la grille (le bateau ne sort pas). Il faut que la case ne chevauche pas un autre bateau ET qu'elle ne touche pas un autre bateau.
 * @return     bool�en. FALSe si mauvais placement, TRUE sinon
 */
int verifier_saisie_bateaux(int  l, int c, int  s, int taille, Joueur j){

	/* l_index : index de la ligne dans la matrice de la grille, l est le code ASCII de la ligne*/
	int l_index = l - 'A' ;
	int i;

	/*saisie correcte */
	if(verifier_lignes(l)==0 ||
		verifier_colonne(c)==0 || verifier_sens(s)==0){
		printf("Erreur de saisie - \n");
		return 0;
	}
	/*conforme � la grille, le bateau ne sort pas*/
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
				printf("Erreur - Les bateaux ne doivent pas se toucher ni se chevaucher!!! GROS COQUIN!!!! m'enfin voyons\n");
				return 0;
			}

		}
	}
	/*parcourir vers la droite*/
	else if (s == 1) {
		for(i = c; i<c+taille; i++) {
			if(touche_bateau(l_index,i,j.bateaux)) {
				printf("Erreur - Les bateaux ne doivent pas se toucher ni se chevaucher!!! GROS COQUIN!!!! m'enfin voyons\n");
				return 0;
			}

		}
	}

	return (1);

}

/**
 * @brief      v�rifie qu'une ligne saisie est conforme � la grille
 * @param      s, un entier pour la ligne
 * @details    la ligne est entre 'A' et 'A'+NB_LIGNES
 * @return     bool�en
 */
int verifier_lignes(int  s){
	return (s >='A'&& s <=('A'+NB_LIGNES));
}

/**
 * @brief      v�rifie qu'une colonne saisie est conforme � la grille
 * @param      s, un entier pour la colonne
 * @details    la colonne est entre 1 et NB_COLONNES
 * @return     bool�en
 */
int verifier_colonne(int s){
	return (s >= 0 && s < NB_COLONNES);
}

/**
 * @brief      v�rifie que le sens/orientation saisi est r�alisable
 * @param      s, un entier pour le sens
 * @details    0 haut; 1 droite;
 * @return     bool�en
 */
int verifier_sens(int s){
	return (s ==0 || s == 1);
}

/**
 * @brief      regarde si un bateau occupe la case donn�e
 * @param      l, un entier de 0 � NB_LIGNES-1 pour la ligne (PAS LE CODE ASCII DE LA LETTRE)
 * @param      c, un entier pour la colonne
 * @param      b, tableau de bateaux du joueur
 * @return     -1 si la case est libre, 0 s'il n'y a aucun bateau plac� sur la grille (initialisation), bateau.id sinon
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

		/*case � droite*/
		else if ((b+i)->sens == 1 &&
			(b+i)->ligne == 'A'+l &&
			c > (b+i)->colonne &&
			c <=(b+i)->colonne+((b+i)->taille-1)) {
			resultat = (b+i)->id;
		}
	}
	if(b->id==0)
		resultat = 0;
	return resultat;
}

/**
 * @brief      regarde si un bateau sort de la grille
 * @param      l, un entier pour la ligne
 * @param 	   c, un entier pour la colonne
 * @param 	   s, un entier pour l'orientation
 * @param 	   taille, un entier pour la taille du bateau concern�
 * @return     bool�en, FALSE si �a sort de la grille
 */
int dans_la_grille(int l, int c, int s,int taille){

	/*case en bas*/
	/*printf("l = %c l+taille = %c, max = %c\n",l,l+taille,'A'+NB_LIGNES );*/
	if (s == 0 && l+taille <= 'A'+NB_LIGNES){
		return 1;
	}
	/*case � droite*/
	else if (s == 1 && c+taille < NB_COLONNES+1)
		return 1;
	return 0;
}

/**
 * @brief      regarde si une case donn�e est d�j� occup�e ou touche une case d�j� occcup�e par un bateau du joueur
 * @param      l, un entier pour la ligne (correspondant � l'index de la ligne : 0 � NB_LIGNE-1, pas au code ASCII)
 * @param 	   c, un entier pour la colonne
 * @param 	   b, tableau de bateaux du joueur
 * @details    la fonction regarde toutes les cases mitoyennes � la case donn�e et v�rifie si ce sont des cases occup�es ou non
 * @return     bool�en
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
