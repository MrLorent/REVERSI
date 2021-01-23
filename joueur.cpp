#include <iostream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;

// MODELES

/**
 * Initialise un joueur à partir des données fournies en paramètre et d'une la saisie utilisateur
*/
void initJoueur(Joueur * unJoueur, char uneCouleur){
	cout << MAGENTA << "Veuillez entrer le nom du joueur:" << ANNULE_COULEUR << endl;
	cin >> unJoueur->nom;
	unJoueur->couleur = uneCouleur;
	unJoueur->nbJeton = 0;
	unJoueur->listeJetons = NULL;
}

/**
 * Initialise un joueur artificiel
*/
void initOrdinateur(Joueur * unJoueur){
	char nomOrdi[8] = {'M','i','c','h','e','l','l','e'};
	
	for(int i=0; i<8;i++){
		unJoueur->nom[i] = nomOrdi[i];
	}
	unJoueur->couleur = 'n';
	unJoueur->nbJeton = 0;
	unJoueur->listeJetons = NULL;
}

// CONTROLEURS

/**
 * Créer un nouveau jeton à partir des coordonnées fournies en paramètre, et l'ajoute à la liste de jeton du joueur indiqué
*/
void ajouteJetonJoueur(Joueur * unJoueur, int coordonnees[2]){
	Jeton * nouveauJeton = new Jeton;
	initJeton(nouveauJeton, unJoueur->couleur, coordonnees);
	nouveauJeton->suivant = unJoueur->listeJetons;
	unJoueur->listeJetons = nouveauJeton;
	(unJoueur->nbJeton)++;
}

/**
 * Supprime le jeton correspondant aux coordonnées fournies en paramètre de la liste de jeton du joueur indiqué
*/
void supprimeJetonJoueur(Joueur * unJoueur, int coordonnees[2]){
	Jeton * tmp = unJoueur->listeJetons;
	Jeton * precedent = NULL;
	bool supprime = false;

	while(tmp != NULL && !supprime){
		if(tmp->coordonnees[0] == coordonnees[0] && tmp->coordonnees[1] == coordonnees[1]){
			if(precedent == NULL){
				unJoueur->listeJetons = unJoueur->listeJetons->suivant;
				free(tmp);
			}else{
				precedent->suivant = tmp->suivant;
				free(tmp);
			}
			unJoueur->nbJeton = unJoueur->nbJeton -1;

			supprime = true;
		}
		precedent = tmp;
		tmp = tmp->suivant;
	}
}

/**
 * Identifie le coups à jouer permettant de capturer le plus de jetons adverse, et le joue
*/
int ordinateurJoue(Jeu * leJeu){
	int nbCoupsJouables = 0;
	bool coupsIdentiques = true;
	CoupJouable * coupAJouer = leJeu->coupsJouables;
	CoupJouable * tmp = leJeu->coupsJouables;

	// On parcourt la liste de coups à jouer en ne retenant que le coups capturant le plus de jetons adverses
	while(tmp != NULL){
		if(tmp->nbCaptures > coupAJouer->nbCaptures){
			coupAJouer = tmp;
			coupsIdentiques = false;
		}
		nbCoupsJouables++;
		tmp = tmp->suivant;
	}

	tmp = leJeu->coupsJouables;

	// Si tous le coups à jouer permettent de capturer le même nombre de jetons, alors on en choisi un au hasard dans la liste
	if(coupsIdentiques){
		int rang = rand()%nbCoupsJouables;
		for(int i=0; i<rang; i++){
			tmp = tmp->suivant;
		}
		coupAJouer = tmp;
	}

	// On joue le coup choisi
	joueLeCoup(leJeu->plateau, coupAJouer->emplacement->coordonnees, &leJeu->joueur2, &leJeu->joueur1);

	return coupAJouer->nbCaptures;
}