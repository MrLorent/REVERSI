#include "main.h"

void initJeu(Jeu * unJeu){
	Jeton jetonBlanc1, jetonBlanc2, jetonNoir1, jetonNoir2;
	int coor1[2]={3,3}, coor2[2]={4,4}, coor3[2]={3,4}, coor4[2]={4,3};

	// initialisation du premier joueur et de ses deux premiers jetons
	initJoueur(&(*unJeu).joueur1);
	initJeton(&jetonBlanc1, 'b', coor1);
	ajouteJeton(&(*unJeu).joueur1, &jetonBlanc1);
	initJeton(&jetonBlanc2, 'b', coor2);
	ajouteJeton(&(*unJeu).joueur1, &jetonBlanc2);

	// initialisation du second joueur et de ses deux premiers jetons
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