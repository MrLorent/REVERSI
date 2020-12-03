#include "main.h"

void initJoueur(Joueur * joueur){
	cout << "ENREGISTREMENT D'UN JOUEUR" << endl;
	cout << "Veuillez entrer le nom du joueur:" << endl;
	cin >> (*joueur).nom;
	(*joueur).nbJeton = 0;
}

void afficheJoueur(Joueur joueur){
	cout << "AFFICHAGE DES INFORMATIONS D'UN JOUEUR" << endl;
	cout << "Nom: " << joueur.nom << endl;
	cout << "Nombre de jetons: " << joueur.nbJeton << endl;
}