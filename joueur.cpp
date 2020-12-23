#include "main.h"

void initJoueur(Joueur * unJoueur){
	cout << "ENREGISTREMENT D'UN JOUEUR" << endl;
	cout << "Veuillez entrer le nom du joueur:" << endl;
	cin >> (*unJoueur).nom;
	(*unJoueur).nbJeton = 0;
}

void ajouteJetonJoueur(Joueur * unJoueur, Jeton unJeton){
	(*unJoueur).listeJetons[(*unJoueur).nbJeton] = unJeton;
	((*unJoueur).nbJeton)++;
}

void afficheJoueur(Joueur joueur){
	cout << "AFFICHAGE DES INFORMATIONS D'UN JOUEUR" << endl;
	cout << "Nom: " << joueur.nom << endl;
	cout << "Nombre de jetons: " << joueur.nbJeton << endl;
}