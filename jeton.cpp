#include <iostream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;

// MODÈLES
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

// CONTROLEURS
void ajouteJetonCapture(ListeJetons * liste, int coorJetonCapture[2]){
	cout << "11" << endl;
	Jeton * nouvelleCapture = new Jeton;
	cout << "12" << endl;
	nouvelleCapture->coordonnees[0] = coorJetonCapture[0];
	nouvelleCapture->coordonnees[1] = coorJetonCapture[1];
	if(liste != NULL){
		nouvelleCapture->suivant = *liste;
	}else{
		nouvelleCapture->suivant = NULL;
	}
	*liste = nouvelleCapture;
}

void ajouteJetonsCaptures(ListeJetons * liste1, ListeJetons * liste2){
	Jeton * tmp = *liste2;

	while(tmp != NULL){
		ajouteJetonCapture(liste1, tmp->coordonnees);
		tmp = tmp->suivant;
	}
}

void videListeJetons(ListeJetons * uneListe){
	Jeton * tmp = *uneListe;
	while(tmp != NULL){
		*uneListe = (*uneListe)->suivant;
		cout << "ici" << endl;
		free(tmp);
		cout << "pas après" << endl;
		tmp = *uneListe;
	}
}