#include <stdio.h>   /* pour les entr�es-sorties */
#include <string.h>  /* pour les manipulations de cha�nes de caract�res */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compl�ter votre nom ici                                                */
/*   Nom :  Berthebaud                       Pr�nom : Yanis               */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le r�pertoire stock� en m�moire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compl�ter code ici pour tableau
	if (rep->nb_elts < MAX_ENREG)
	{
		modif = true;
		rep->tab[rep->nb_elts] = enr;    //si la condition est bien v�rifi�e, on ajoute le contact � la fin du tableau
		rep->nb_elts++;   //on augmente le nbre de valeur
		return (OK);
	}
	else {
		return(ERROR);
	}

	
#else
#ifdef IMPL_LIST
	
	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts++;     //on ajoute l'�lement en queue
			modif = true;
			rep->est_trie = false;
			return(OK);
		}

	}


#endif
	
#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du r�pertoire l'enregistrement dont l'indice est donn� en */
  /*   param�tre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire *rep, int indice) {

	// compl�ter code ici pour tableau
	if (rep->nb_elts >= 1)		/* s'il y a au moins un element ds le tableau */
	{						/* et que l'indice pointe a l'interieur */
		for (int i = indice; i < rep->nb_elts-1; i++) {   //on d�cale tout le tableau sur la gauche � partir de l'indice jusque nb_elts-1
			rep->tab[i] = rep->tab[i + 1];
		}
		rep->nb_elts --;		/* ds ts les cas, il y a un element en moins */
		modif = true;
	}

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du r�pertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif � vrai                              */
  /************************************************************************/
  // complet

	int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem) {
	
	int ret=DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0); 
	}
#endif
#endif


  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement sur une ligne � l'�cran  */
  /* ex Dupont, Jean                 0320304050                         */
  /**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	// code � compl�ter ici
	printf("\n|");
	printf("%s", enr.nom);
	for (int i = strlen(enr.nom); i < MAX_NOM; i++) {
		printf(" ");
	}
	printf("|");
	printf("%s", enr.prenom);
	for (int i = strlen(enr.prenom); i < MAX_NOM; i++) {       //pour aligner tous les nom et pr�nom on compl�te avec des espaces jusque max nom
		printf(" ");
	}
	printf("|");
	printf("%s\n", enr.tel);
	return;
	return;

} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	printf("\n|");
	printf("%s", enr.nom);
	for (int i = strlen(enr.nom); i < MAX_NOM; i++) {       //pour aligner tous les nom et pr�nom on compl�te avec des espaces jusque max nom
		printf(" ");
	}
	printf("|");
	printf("%s", enr.prenom);
	for (int i = strlen(enr.prenom); i < MAX_NOM; i++) {
		printf(" ");
	}
	printf("|");
	printf("%s\n", enr.tel);
	return;
} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	// code � compl�ter ici
	char tmp1[MAX_NOM];                                             //on copie les noms et les prenoms dans des variables temporaires et on les passe en majuscule
	strncpy_s(tmp1, _countof(tmp1), enr2.nom, _TRUNCATE);
	_strupr_s(tmp1, strlen(tmp1) + 1);
	char tmp2[MAX_NOM];
	strncpy_s(tmp2, _countof(tmp2), enr1.nom, _TRUNCATE);
	_strupr_s(tmp2, strlen(tmp2) + 1);
	char tmp3[MAX_NOM];
	strncpy_s(tmp3, _countof(tmp3), enr2.prenom, _TRUNCATE);
	_strupr_s(tmp3, strlen(tmp3) + 1);
	char tmp4[MAX_NOM];
	strncpy_s(tmp4, _countof(tmp4), enr1.prenom, _TRUNCATE);
	_strupr_s(tmp4, strlen(tmp4) + 1);

		
	if (strcmp((tmp1), (tmp2)) < 0) return (true);   //si tmp1 est plus haut dans l'ordre alphab�tique ont return true
	if (strcmp((tmp1), (tmp2)) > 0) return (false);  //sinon on v�rifie si elle est plus haute, si c'est le cas on return false
	                                                                     
	if (strcmp((tmp3), (tmp4)) < 0) return (true);   //on refait pareil qu'avant avec les pr�noms si jamais les noms sont les m�mes
	if (strcmp((tmp3), (tmp4)) > 0) return (false);
	
	return(false);
	
}
 
/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire *rep)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	for (int j = 0; j < rep->nb_elts; j++) {
		for (int i = 0; i < rep->nb_elts - 1 - j; i++) {
			// si enr1 > enr2, echange des enr
			//printf("%s < %s = %d\n", rep->tab[i].nom, rep->tab[i+1].nom, est_sup(*(rep->tab + i), *(rep->tab + i + 1)));
			if (est_sup(rep->tab[i + 1], rep->tab[i]) == false) {
				printf("ECHANGE %s %s\n", rep->tab[i].nom, rep->tab[i + 1].nom);
				Enregistrement tmp = rep->tab[i + 1];
				rep->tab[i + 1] = rep->tab[i];
				rep->tab[i] = tmp;
			}
		}
	}


	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien � faire !
	// la liste est toujours tri�e
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le r�pertoire d'un enregistrement correspondant au  */
  /*   nom � partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au crit�re ou*/
  /*   un entier n�gatif si la recherche est n�gative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire *rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de d�but de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;		


#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	ind_fin = rep->nb_elts;
	strncpy_s(tmp_nom, _countof(tmp_nom), nom, _TRUNCATE);    //on copie nom dans tmp_nom, et on le passe en majuscule
	_strupr_s(tmp_nom, strlen(tmp_nom) +1);
	while (trouve == false && i < ind_fin) {  //on va comparer a chaque nom du r�pertoire jusqu'au dernier
		
		strncpy_s(tmp_nom2, _countof(tmp_nom2), rep->tab[i].nom, _TRUNCATE);   //on copie dans tmp_nom2 le nom du r�pertoire et on le passe en maj
		_strupr_s(tmp_nom2, strlen(tmp_nom2)+1);
		if (strcmp(tmp_nom, tmp_nom2) == 0) trouve = true; //comparaison de la chaine de charactere on return true si c'est le m�me
		else i++;  //sinon on passe au suivant
	}
	
	
	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour tableau
	ind_fin = rep->nb_elts;
	strncpy_s(tmp_nom, _countof(tmp_nom), nom, _TRUNCATE);    //on copie nom dans tmp_nom, et on le passe en majuscule
	_strupr_s(tmp_nom, strlen(tmp_nom) + 1);
	while (trouve == false && i < ind_fin) {  //on va comparer a chaque nom du r�pertoire jusqu'au dernier

		strncpy_s(tmp_nom2, _countof(tmp_nom2), GetElementAt(rep->liste,i)->pers.nom, _TRUNCATE);   //on copie dans tmp_nom2 le nom du r�pertoire et on le passe en maj
		_strupr_s(tmp_nom2, strlen(tmp_nom2) + 1);
		if (strcmp(tmp_nom, tmp_nom2) == 0) trouve = true; //comparaison de la chaine de charactere on return true si c'est le m�me
		else i++;  //sinon on passe au suivant
	}
	
#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non num�riques de la chaines        */
  /*********************************************************************/
void compact(char* s)
{
	int i = 0;
	int j = 0;
	while (s[i] != '\0') {  //on parcours toute la chaine
		if (s[i] < 0x30 || s[i] > 0x39) {   //codage ascii de 0 � 9, si �a n'appartient pas � �a, on le supprime
			j = i;
			while (s[j + 1] != '\0') {    //on �crase la valeur en d�calant tout vers la gauche
				*(s + j) = *(s + j + 1);  
				j++;
			}
		}
		else i++;
	}
	return;
}

/**********************************************************************/
/* sauvegarde le r�pertoire dans le fichier dont le nom est pass� en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionn� ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire* rep, char nom_fichier[])
{
	errno_t err;
	FILE* fic_rep;                    /* le fichier */
#ifdef IMPL_TAB
	if (fopen_s(&fic_rep, nom_fichier, "w") != 0 || fic_rep == NULL) {   //on v�rifie que le fichier est ouvert
		err = ERROR;
		return err;
	}
	for (int i = 0; i < rep->nb_elts; i++) {      //pour tous les �l�ments du tableau
		fprintf(fic_rep, "%s%c", rep->tab[i].nom, SEPARATEUR);           //on �crit dans le fichier les info du contact
		fprintf(fic_rep, "%s%c", rep->tab[i].prenom, SEPARATEUR);
		fprintf(fic_rep, "%s\n", rep->tab[i].tel);

	}
	if (feof(fic_rep)) {
		fclose(fic_rep);
	}
	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	if (fopen_s(&fic_rep, nom_fichier, "w") != 0 || fic_rep == NULL) {   //on v�rifie que le fichier est ouvert
		err = ERROR;
		return err;
	}
	for (int i = 0; i < rep->nb_elts; i++) {      //pour tous les �l�ments du tableau
		fprintf(fic_rep, "%s%c", GetElementAt(rep->liste, i)->pers.nom, SEPARATEUR);           //on �crit dans le fichier les info du contact
		fprintf(fic_rep, "%s%c", GetElementAt(rep->liste, i)->pers.prenom, SEPARATEUR);
		fprintf(fic_rep, "%s\n", GetElementAt(rep->liste, i)->pers.tel);

	}
	if (feof(fic_rep)) {
		fclose(fic_rep);
	}
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le r�pertoire le contenu du fichier dont le nom est  */
  /*   pass� en argument                                                */
  /*   retourne OK si le chargement a fonctionn� et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char *char_nw_line;
	
	_set_errno(0);
	if ( ((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL) )
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element � priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
														// ajouter code implemention liste
				Enregistrement enr;
				if (lire_champ_suivant(buffer, &idx, enr.nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, enr.prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, enr.tel, MAX_TEL, SEPARATEUR) == OK) {
							
							InsertElementAt(rep->liste, num_rec, enr);
							num_rec++;		/* element � priori correct, on le comptabilise */
						}
							
					}
				}

#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */