#ifndef VUE_H
#define VUE_H

#include "modele.h"

using namespace std;

// JEU

// PLATEAU
void affichePlateau(Jeton * plateau[MAXLARGEUR][MAXLARGEUR]);
void afficheLigneTransition();

// COULEURS
const string ANNULE_COULEUR = "\x1B[0m";
const string JAUNE = "\x1B[38;2;255;255;59m";
const string CYAN = "\x1B[38;2;0;255;255m";
const string VERT = "\x1B[38;2;0;255;0m";
const string MAGENTA = "\x1B[38;2;255;0;255m";

#endif