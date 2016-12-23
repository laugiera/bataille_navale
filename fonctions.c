/**
 * @file      fonctions.c
 * @author    LAUGIER AA - REYES Laura - LANDRY-LINET Lou
 * @version   1.0
 * @date      23 Décembre 2016
 * @brief     Définis les structures et les méthodes du jeu
 * @details    ~
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

/**
 * @brief      Affiche la grille de jeu
 * @details    La grille et les bateaux de @a jo ('.' inconnu; 'o' eau; '%d' bateau; 'c' coulé)
 *             des coordonnées des points. (cf #Point)
 * @param    jo		Joueur correspondant à la grille
 * @return    void
 */
void afficher_grille(Joueur jo){
	int i,j,k,lettre='A';
	printf("   |");
	for (k = 1; k <= NB_COLONNES; k++)
		printf(" %d |",k );
	printf("\n");
	for (i = 0; i <= NB_LIGNES; i++)
	{
		printf(" %c |",lettre);
		lettre++;
		for (j = 1; j <= NB_COLONNES; j++)
		{
			int case_b = is_case_bateau(i,j,jo.bateaux);
			if(case_b!= -1) //si case de bateau
				printf(" %d |",case_b );
			else	//sinon
				printf(" . |");
		}
		printf("\n");
	}
}

/**
 * @brief      Affiche le joueur, ses bateaux et son historique de coups
 * @param    j		Joueur correspondant 
 * @return    void
 */
void afficher_joueur(Joueur j){
	int i;
	printf("Joueur %s\n",j.name);
	printf("Bateaux :\n");
	afficher_bateaux(j.bateaux);
	printf("nb coups : %d\n",j.nb_coups);
	printf("Historique :\n");
	for (i = 0; i < j.nb_coups; i++)
	{
		printf("\tCoup %d : %c %d %c\n",i,
			(j.historique+i)->ligne,
			(j.historique+i)->colonne,
			(j.historique+i)->resultat );
	}
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
 * @brief      Initialise le joueur
 * @param      j, le joueur
 * @details    Le joueur saisit son nom. L'historique est alloué est initialisé à O. Les bateaux sont alloués puis saisis.
 * @return     EXIT_FAILURE si les malloc fail, EXIT_SUCESS sinon
 */
int initialiser_joueur(Joueur *j){
	int i;
	//pseudo
	printf("Quel est ton pseudo ?\n");
	scanf("%s",j->name);
	f_purge(stdin);
	//historique
	j->nb_coups=0;
	j->historique = calloc(BLOC_MALLOC,sizeof(Coup));
	if(j->historique == NULL)
		return EXIT_FAILURE;
	//bateaux
	j->bateaux = malloc(NB_BATEAUX * sizeof(Bateau));
	if(j->bateaux == NULL)
		return EXIT_FAILURE;
	saisir_bateaux(j);

	return EXIT_SUCCESS;
}

/**
 * @brief      libère la mémoire allouée au joueur
 * @param      j, le joueur
 * @return     void
 */
void free_joueur(Joueur *j){
	free(j->bateaux);
	free(j->historique);
}

/**
 * @brief      le joueur saisit les emplacements de ses bateaux
 * @param      j, le joueur
 * @details    le joueur saisit une case, un sens d'orientation et le jeu vérifie la saisie. Si la saisie est bonne, le bateau est initialisé et la grille maj affichée
 * @return     void
 */
void saisir_bateaux(Joueur *j){
	printf("Saisissez vos bateaux (coordonnées de la première case et sens):\n SENS : 0 haut; 1 droite; 2 bas; 3 gauche; \n");
	int tailles[NB_BATEAUX]={5,4,3,3,2}; /*!< Règles : 1 bateau de taille 5, 1 de taille 4, 2 de taille 3, 1 de taille 2*/
	int i,colonne,ligne,sens;
	for (i = 0; i < NB_BATEAUX; i++)
	{
		printf("Saisie du bateau %d, taille %d\n",i,tailles[i]);
		do {
			printf("ligne : ");
			scanf("%c",&ligne);
			f_purge(stdin);
			printf("colonne : ");
			scanf("%d",&colonne);
			f_purge(stdin);
			printf("sens : ");
			scanf("%d",&sens);
			f_purge(stdin);
			//tq saisie mauvaise
		}while(verifier_saisie_bateaux(ligne, colonne, sens,tailles[i],*j)==0);

		//initialisation bateau
		(j->bateaux+i)->id=i+1;
		(j->bateaux+i)->taille=tailles[i];
		(j->bateaux+i)->etat = 1;
		(j->bateaux+i)->ligne = ligne;
		(j->bateaux+i)->colonne = colonne;
		(j->bateaux+i)->sens = sens;
		//grille mise à jour
		afficher_grille(*j);

	}

}

/**
 * @brief      vérifie le placement d'un bateau
 * @param      l, un entier pour la ligne
 * @param 	   c, un entier pour la colonne
 * @param 	   s, un entier pour l'orientation
 * @param 	   taille, un entier pour la taille du bateau concerné
 * @param 	   j, le joueur
 * @details    Pour qu'un placement soit valide, il faut que la saisie soit correcte, conforme à la grille (le bateau ne sort pas). Il faut que la case ne chevauche pas un autre bateau ET qu'elle ne touche pas un autre bateau.
 * @return     booléen. FALSe si mauvais placement, TRUE sinon
 */
int verifier_saisie_bateaux(int  l, int c, int  s, int taille, Joueur j){
	int saisie = 0, placement = 0, regles = 0;
	//saisie correcte 
	if(verifier_lignes(l) && 
		verifier_colonne(c) && verifier_sens(s))
		saisie = 1;
	else 
		printf("Erreur de saisie - \n");
	//conforme à la grille, le bateau ne sort pas
	if(dans_la_grille(l,c,s,taille) == 1)
		placement = 1;
	else
		printf("Placement hors de la grille\n");
	//conforme aux regles (pas de chevauchement de bateaux)
	if(is_case_bateau(l,c,j.bateaux)!= -1)
		regles = 1;
	else
		printf("Erreur - Pas de chevauchement de bateaux, PETIT COQUIN\n");
	//conforme aux regles (pas de bateaux qui se touchent)
	if(touche_bateau(l,c,j.bateaux) == 0){
		printf("Erreur - Les bateaux ne doivent pas se toucher\n");
		regles = 0;
	}
	return (saisie && placement && regles);

}

/**
 * @brief      vérifie qu'une ligne saisie est conforme à la grille
 * @param      s, un entier pour la ligne 
 * @details    la ligne est entre 'A' et 'A'+NB_LIGNES
 * @return     booléen
 */
int verifier_lignes(int  s){
	return (s >='A'&& s <=('A'+NB_LIGNES));
}

/**
 * @brief      vérifie qu'une colonne saisie est conforme à la grille
 * @param      s, un entier pour la colonne 
 * @details    la colonne est entre 1 et NB_COLONNES
 * @return     booléen
 */
int verifier_colonne(int s){
	return (s >= 1 && s <= NB_COLONNES);
}

/**
 * @brief      vérifie que le sens/orientation saisi est réalisable
 * @param      s, un entier pour le sens
 * @details    0 haut; 1 droite; 2 bas; 3 gauche; 
 * @return     booléen
 */
int verifier_sens(int s){
	return (s >=0 && s <= 3);
}

/**
 * @brief      regarde si un bateau occupe la case donnée
 * @param      l, un entier pour la ligne
 * @param      c, un entier pour la colonne
 * @param      b, tableau de bateaux du joueur
 * @return     -1 si la case est libre, 0 s'il n'y a aucun bateau, bateau.id sinon
 */
int is_case_bateau(int l, int c, Bateau *b){
	int i, resultat = -1;
	for (i = 0; i < NB_BATEAUX; i++)
	{	
		//premiere case
		if((b+i)->ligne == 'A'+l && (b+i)->colonne == c)
			resultat = (b+i)->id;
		//case en haut
		else if((b+i)->sens == 0 && 
			(b+i)->colonne == c && 
			'A'+l<(b+i)->ligne &&
			'A'+l>='A'+(b+i)->ligne-('A'+((b+i)->taille-1)))
			resultat = (b+i)->id;
		//case en bas
		else if ((b+i)->sens == 2 && 
			(b+i)->colonne == c && 
			'A'+l>(b+i)->ligne &&
			'A'+l<=(b+i)->ligne+((b+i)->taille-1))
			resultat = (b+i)->id;
		//case à gauche
		else if ((b+i)->sens == 3 && 
			(b+i)->ligne == 'A'+l && 
			c < (b+i)->colonne &&
			c >=(b+i)->colonne-((b+i)->taille-1))
			resultat = (b+i)->id;
		//case à droite
		else if ((b+i)->sens == 1 && 
			(b+i)->ligne == 'A'+l && 
			c > (b+i)->colonne &&
			c <=(b+i)->colonne+((b+i)->taille-1))
			resultat = (b+i)->id;
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
 * @param 	   taille, un entier pour la taille du bateau concerné
 * @return     booléen, FALSE si ça sort de la grille
 */
int dans_la_grille(int l, int c, int s,int taille){
		//case en haut
	if(s == 0 && l-(taille-1) >= 'A')
		return 1;
		//case en bas
	else if (s == 2 && l+(taille-1) <= 'A'+NB_LIGNES)
		return 1;
		//case à gauche
	else if (s == 3 && c-taille >= 0)
		return 1;
		//case à droite
	else if (s == 1 && c+taille <= NB_COLONNES)
		return 1;
	return 0;
}

/**
 * @brief      regarde si une case donnée touche une case déjà occcupée par un bateau du joueur
 * @param      l, un entier pour la ligne
 * @param 	   c, un entier pour la colonne
 * @param 	   b, tableau de bateaux du joueur
 * @details    la fonction regarde toutes les cases mitoyenne à la case donnée et vérifie si ce sont des cases occupées ou non
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
		is_case_bateau(l, c-1, b)!=-1 &&
		is_case_bateau(l, c+1, b)!=-1 &&
		is_case_bateau(l-1, c, b)!=-1 &&
		is_case_bateau(l+1, c, b)!=-1 &&
		is_case_bateau(l-1, c-1, b)!=-1 &&
		is_case_bateau(l-1, c+1, b)!=-1 &&
		is_case_bateau(l+1, c-1, b)!=-1 &&
		is_case_bateau(l+1, c+1, b)!=-1 
		);
}