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
bool placementValide(char plateau[MAXLARGEUR][MAXLARGEUR], int caseSouhaitee[2], char couleurJoueur );
bool jetonCapture(char plateau[MAXLARGEUR][MAXLARGEUR], int caseCourante[2], int uneDirection, int coorJetonsPris[8][2], int * count, char couleurJoueur, char couleurAdversaire);
void convertCoordonnees(char saisieUt[2], int saisieTraduite[2]);

#endif