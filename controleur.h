#ifndef CONTROLEUR_H
#define CONTROLEUR_H

// JEU
void changeJoueurCourant(Jeu * unJeu);

// PLATEAU
void ajouteJetonPlateau(Joueur unJoueur, char lePlateau[MAXLARGEUR][MAXLARGEUR]);
bool captureJeton(char plateau[MAXLARGEUR][MAXLARGEUR], int caseSouhaitee[2], Joueur * joueurCourant, Joueur * adversaire);
bool directionValide(char plateau[MAXLARGEUR][MAXLARGEUR], int caseDepart[2], int uneDirection, int coorJetonsPris[8][2], int * count, char couleurAdversaire, char objectif);
void analyseCoupsJouables(char plateau[MAXLARGEUR][MAXLARGEUR], Joueur * joueurCourant, Joueur * adversaire, int coupsJouables[10][2], int * nbCoupsJouables);
void ajouteCoupsJouablesPlateau(char plateau[MAXLARGEUR][MAXLARGEUR], int coupsJouables[10][2], int nbCoupJouables);

// JOUEUR
void ajouteJetonJoueur(Joueur * unJoueur, Jeton unJeton);
void ajouteJetonJoueur(Joueur * unJoueur, int coordonnees[2]);

// MAIN
bool saisieCorrecte(char plateau[MAXLARGEUR][MAXLARGEUR], char saisieUt[2], int coorCase[2]);
void convertCoordonnees(char saisieUt[2], int saisieTraduite[2]);

#endif