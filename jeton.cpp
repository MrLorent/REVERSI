#include <iostream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;

// MODÈLES

/**
 * Initialise un jeton passé en paramètre en fonction des données passées en paramètre 
*/
void initJeton(Jeton * unJeton, char couleur, int coordonnees[2]){
	unJeton->couleur = couleur;
	unJeton->coordonnees[0] = coordonnees[0];
	unJeton->coordonnees[1] = coordonnees[1];
	unJeton->suivant = NULL;
}

/**
 * Initialise un Marqueur passé en paramètre en fonction des coordonnées fournies
*/
void initMarqueur(Marqueur * unMarqueur, int coordonnees[2]){
	unMarqueur->couleur = 'v';
	unMarqueur->coordonnees[0] = coordonnees[0];
	unMarqueur->coordonnees[1] = coordonnees[1];
	unMarqueur->suivant = NULL;
}

// CONTROLEURS

/**
 * Créer un jeton à partir des coordonnées passées en paramètre, et l'ajoute à la liste chaîné fournie
*/
void ajouteJetonCapture(ListeJetons * liste, int coorJetonCapture[2]){
	Jeton * nouvelleCapture = new Jeton;

	nouvelleCapture->coordonnees[0] = coorJetonCapture[0];
	nouvelleCapture->coordonnees[1] = coorJetonCapture[1];
	nouvelleCapture->suivant = *liste;
	
	*liste = nouvelleCapture;
}

/**
 * Vide la liste chaînée de jetons fournie en paramètre
*/
void videListeJetons(ListeJetons * uneListe){
	Jeton * tmp = *uneListe;
	while(tmp != NULL){
		*uneListe = (*uneListe)->suivant;
		free(tmp);
		tmp = *uneListe;
	}
}