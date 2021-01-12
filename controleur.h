#ifndef CONTROLEUR_H
#define CONTROLEUR_H

// JEU
void changeJoueurCourant(Jeu * unJeu);

// PLATEAU
void ajouteJetonPlateau(Joueur unJoueur, char lePlateau[MAXLARGEUR][MAXLARGEUR]);

// JOUEUR
void ajouteJetonJoueur(Joueur * unJoueur, Jeton unJeton);

// MAIN
bool saisieCorrecte(char plateau[MAXLARGEUR][MAXLARGEUR], char saisieUt[2], int coorCase[2], char couleurJoueur);
bool verifPlacement(char plateau[MAXLARGEUR][MAXLARGEUR], int caseSouhaitee[2], char couleurJoueur );
void convertCoordonnees(char saisieUt[2], int saisieTraduite[2]);

#endif