#ifndef CONTROLEUR_H
#define CONTROLEUR_H

// JEU
void changeJoueurCourant(Jeu * unJeu);

// PLATEAU
void ajouteJetonPlateau(Joueur unJoueur, char lePlateau[MAXLARGEUR][MAXLARGEUR]);

// JOUEUR
void ajouteJetonJoueur(Joueur * unJoueur, Jeton unJeton);

// MAIN
int verifSaisie(char plateau[MAXLARGEUR][MAXLARGEUR], char saisieUt[2], int saisieTraduite[2]);
void convertCoordonnees(char saisieUt[2], int saisieTraduite[2]);

#endif