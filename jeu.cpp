#include <iostream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;

void initJeu(Jeu * unJeu){
	int coor1[2]={3,3}, coor2[2]={4,4}, coor3[2]={3,4}, coor4[2]={4,3};


	// Initialisation du premier joueur et de ses deux premiers jetons
	cout << endl;
	cout << "ENREGISTREMENT DU PREMIER JOUEUR :" << endl;
	initJoueur(&unJeu->joueur1, 'b');
	ajouteJetonJoueur(&unJeu->joueur1, coor1);
	ajouteJetonJoueur(&unJeu->joueur1, coor2);

	// Initialisation du second joueur et de ses deux premiers jetons
	cout << endl;
	cout << "ENREGISTREMENT DU SECOND JOUEUR :" << endl;
    initJoueur(&unJeu->joueur2, 'n');
	ajouteJetonJoueur(&unJeu->joueur2, coor3);
	ajouteJetonJoueur(&unJeu->joueur2, coor4);

	// Initialisation du joueur courant
	unJeu->joueurCourant = &unJeu->joueur1;
	unJeu->joueurEnAttente = &unJeu->joueur2;

	// Initialisation du plateau de jeu
	initPlateau(unJeu->plateau);
}

void initJeton(Jeton * unJeton, char couleur, int coordonnees[2]){
	unJeton->couleur = couleur;
	unJeton->coordonnees[0] = coordonnees[0];
	unJeton->coordonnees[1] = coordonnees[1];
}

void initMarqueur(Marqueur * unMarqueur, int coordonnees[2]){
	unMarqueur->couleur = 'v';
	unMarqueur->coordonnees[0] = coordonnees[0];
	unMarqueur->coordonnees[1] = coordonnees[1];
}

void changeJoueurCourant(Jeu * unJeu){
	if(strcmp(unJeu->joueurCourant->nom, (*unJeu).joueur1.nom) == 0 ){
		unJeu->joueurCourant = &unJeu->joueur2;
		unJeu->joueurEnAttente = &unJeu->joueur1;
	}else{
		unJeu->joueurCourant = &unJeu->joueur1;
		unJeu->joueurEnAttente = &unJeu->joueur2;
	}
}

void enregistreCoupJouable(ListeCoupsJouables * liste, Marqueur * emplacement, ListeCaptures * captures, int nbCaptures){
	if(estEnregistre(liste, emplacement->coordonnees) >= 0){
		CoupJouable * tmp = *liste;
		while(tmp != NULL){
			if((tmp)->emplacement->coordonnees[0] == emplacement->coordonnees[0] && (tmp)->emplacement->coordonnees[1] == emplacement->coordonnees[1]){
				concatCaptures(&(tmp->captures), captures);
				tmp->nbCaptures = tmp->nbCaptures + nbCaptures;
			}
		tmp = tmp->suivant;
		}
	}else{
		Capture * tmp = *captures;
		CoupJouable * nouveauCoup = new CoupJouable;
		nouveauCoup->emplacement = emplacement;
		
		while(tmp != NULL){
			ajouteJetonCapture(&(nouveauCoup->captures), tmp->jeton);
			tmp = tmp->suivant;
		}
		nouveauCoup->nbCaptures = nbCaptures;
			
		if(liste != NULL){
			nouveauCoup->suivant = *liste;
		}else{
			nouveauCoup->suivant = NULL;
		}
		*liste = nouveauCoup;
	}
}

void ajouteJetonCapture(ListeCaptures * liste, Jeton * jetonCapture){
	Capture * nouvelleCapture = new Capture;
	nouvelleCapture->jeton = jetonCapture;
		
	if(liste != NULL){
		nouvelleCapture->suivant = *liste;
	}else{
		nouvelleCapture->suivant = NULL;
	}
	*liste = nouvelleCapture;
}

void videListe(ListeCaptures * uneListe){
	Capture * tmp = *uneListe;

	while(tmp != NULL){
		*uneListe = (*uneListe)->suivant;
		free(tmp);
		tmp = *uneListe;
	}
}

void concatCaptures(ListeCaptures * liste1, ListeCaptures * liste2){
	Capture * tmp = *liste2;

	while(tmp != NULL){
		ajouteJetonCapture(liste1, tmp->jeton);
		tmp = tmp->suivant;
	}
}

int estEnregistre(ListeCoupsJouables * coupsJouables, int coorEmplacement[2]){
	int rang = 0;
	bool present = false;
	CoupJouable * tmp = *coupsJouables;

	while(tmp != NULL && !present){
		if((tmp)->emplacement->coordonnees[0] == coorEmplacement[0] && (tmp)->emplacement->coordonnees[1] == coorEmplacement[1]){
			present = true;
		}
		rang++;
		tmp = tmp->suivant;
	}
	if(present){
		return rang;
	}else{
		return -1;
	}
}