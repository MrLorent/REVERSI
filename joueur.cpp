#include "main.h"

void initJoueur(Joueur * unJoueur){
	cout << "ENREGISTREMENT D'UN JOUEUR" << endl;
	cout << "Veuillez entrer le nom du joueur:" << endl;
	cin >> (*unJoueur).nom;
	(*unJoueur).nbJeton = 0;
}

void ajouteJeton(Joueur * unJoueur, Jeton * unJeton){
	if((*unJoueur).listeJetons == NULL){
		(*unJoueur).listeJetons = unJeton;
	}else{
		(*unJeton).suivant = (*unJoueur).listeJetons;
		(*unJoueur).listeJetons = unJeton;
		((*unJoueur).nbJeton)++;
	}
}

void afficheJoueur(Joueur joueur){
	cout << "AFFICHAGE DES INFORMATIONS D'UN JOUEUR" << endl;
	cout << "Nom: " << joueur.nom << endl;
	cout << "Nombre de jetons: " << joueur.nbJeton << endl;
}