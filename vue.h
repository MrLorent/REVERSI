#ifndef VUE_H
#define VUE_H

#include "modele.h"

using namespace std;

// JEU

// PLATEAU
void affichePlateau(Jeton * plateau[MAXLARGEUR][MAXLARGEUR]);
void afficheLigneTransition();

//JOUEUR
void afficheJoueur(Joueur joueur);

#endif