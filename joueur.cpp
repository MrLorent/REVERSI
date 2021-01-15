#include <iostream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;

void initJoueur(Joueur * unJoueur, char uneCouleur){
	cout << "Veuillez entrer le nom du joueur:" << endl;
	cin >> unJoueur->nom;
	unJoueur->nbJeton = 0;
	unJoueur->couleur = uneCouleur;
}

void ajouteJetonJoueur(Joueur * unJoueur, Jeton unJeton){
	unJeton.couleur = unJoueur->couleur;
	unJoueur->listeJetons[unJoueur->nbJeton] = unJeton;
	(unJoueur->nbJeton)++;
}

void ajouteJetonJoueur(Joueur * unJoueur, int coordonnees[2]){
	Jeton unJeton;
	initJeton(&unJeton, unJoueur->couleur, coordonnees);
	
	unJoueur->listeJetons[unJoueur->nbJeton] = unJeton;
	(unJoueur->nbJeton)++;
}

void afficheJoueur(Joueur joueur){
	cout << "AFFICHAGE DES INFORMATIONS D'UN JOUEUR" << endl;
	cout << "Nom: " << joueur.nom << endl;
	cout << "Nombre de jetons: " << joueur.nbJeton << endl;
}