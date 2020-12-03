#include "main.h"

void initJeu(Jeu * unJeu){
	initJoueur(&(*unJeu).joueur1);
    initJoueur(&(*unJeu).joueur2);
	initPlateau((*unJeu).plateau);
}