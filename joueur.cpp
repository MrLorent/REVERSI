#include <iostream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"
#include "couleur.h"


using namespace std;

// MODELES
void initJoueur(Joueur * unJoueur, char uneCouleur){
	cout << MAGENTA << "Veuillez entrer le nom du joueur:" << ANNULE_COULEUR << endl;
	cin >> unJoueur->nom;
	unJoueur->couleur = uneCouleur;
	unJoueur->nbJeton = 0;
	unJoueur->listeJetons = NULL;
}

void initOrdinateur(Joueur * unJoueur){
	char nomOrdi[8] = {'M','i','c','h','e','l','l','e'};
	
	for(int i=0; i<8;i++){
		unJoueur->nom[i] = nomOrdi[i];
	}
	unJoueur->couleur = 'n';
	unJoueur->nbJeton = 0;
	unJoueur->listeJetons = NULL;
}

// VUES
void afficheJoueur(Joueur joueur){
	cout << "AFFICHAGE DES INFORMATIONS D'UN JOUEUR" << endl;
	cout << "Nom: " << joueur.nom << endl;
	cout << "Nombre de jetons: " << joueur.nbJeton << endl;
}

// CONTROLEURS
void ajouteJetonJoueur(Joueur * unJoueur, int coordonnees[2]){
	Jeton * nouveauJeton = new Jeton;
	initJeton(nouveauJeton, unJoueur->couleur, coordonnees);
	nouveauJeton->suivant = unJoueur->listeJetons;
	unJoueur->listeJetons = nouveauJeton;
	(unJoueur->nbJeton)++;
}

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