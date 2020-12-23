#include "main.h"

void initJeton(Jeton * unJeton, char couleur, int coordonnees[2]){
	(*unJeton).couleur = couleur;
	(*unJeton).coordonnees[0] = coordonnees[0];
	(*unJeton).coordonnees[1] = coordonnees[1];
}