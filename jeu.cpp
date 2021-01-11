#include <iostream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;

void initJeu(Jeu * unJeu){
	Jeton jetonBlanc1, jetonBlanc2, jetonNoir1, jetonNoir2;
	int coor1[2]={3,3}, coor2[2]={4,4}, coor3[2]={3,4}, coor4[2]={4,3};

	// Initialisation du premier joueur et de ses deux premiers jetons
	cout << endl;
	cout << "ENREGISTREMENT DU PREMIER JOUEUR :" << endl;
	initJoueur(&unJeu->joueur1, 'b');
	initJeton(&jetonBlanc1, unJeu->joueur1.couleur, coor1);
	ajouteJetonJoueur(&unJeu->joueur1, jetonBlanc1);
	initJeton(&jetonBlanc2, unJeu->joueur1.couleur, coor2);
	ajouteJetonJoueur(&unJeu->joueur1, jetonBlanc2);

	// Initialisation du second joueur et de ses deux premiers jetons
	cout << endl;
	cout << "ENREGISTREMENT DU SECOND JOUEUR :" << endl;
    initJoueur(&unJeu->joueur2, 'n');
	initJeton(&jetonNoir1, unJeu->joueur2.couleur, coor3);
	ajouteJetonJoueur(&unJeu->joueur2, jetonNoir1);
	initJeton(&jetonNoir2, unJeu->joueur2.couleur, coor4);
	ajouteJetonJoueur(&unJeu->joueur2, jetonNoir2);

	// Initialisation du joueur courant
	unJeu->joueurCourant = &unJeu->joueur1;

	// Initialisation du plateau de jeu
	initPlateau(unJeu->plateau);
}

void initJeton(Jeton * unJeton, char couleur, int coordonnees[2]){
	unJeton->couleur = couleur;
	unJeton->coordonnees[0] = coordonnees[0];
	unJeton->coordonnees[1] = coordonnees[1];
}

void changeJoueurCourant(Jeu * unJeu){
	if(strcmp(unJeu->joueurCourant->nom, (*unJeu).joueur1.nom) == 0 ){
		unJeu->joueurCourant = &unJeu->joueur2;
	}else{
		unJeu->joueurCourant = &unJeu->joueur1;
	}
}