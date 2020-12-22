#include "main.h"

void initJeu(Jeu * unJeu){
	initJoueur(&(*unJeu).joueur1);
    initJoueur(&(*unJeu).joueur2);
	(*unJeu).joueurCourant = &(*unJeu).joueur1;
	initPlateau((*unJeu).plateau);
}

void changeJoueurCourant(Jeu * unJeu){
	if(strcmp((*(*unJeu).joueurCourant).nom, (*unJeu).joueur1.nom) == 0 ){
		(*unJeu).joueurCourant = &(*unJeu).joueur2;
	}else{
		(*unJeu).joueurCourant = &(*unJeu).joueur1;
	}
}