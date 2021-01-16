#ifndef CONTROLEUR_H
#define CONTROLEUR_H

// JEU
void changeJoueurCourant(Jeu * unJeu);
void enregistreCoupJouable(ListeCoupsJouables * liste, Marqueur * emplacement);

// PLATEAU
void ajouteJetonPlateau(Joueur * unJoueur, Jeton * lePlateau[MAXLARGEUR][MAXLARGEUR]);
bool captureJeton(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], int caseSouhaitee[2], Joueur * joueurCourant, Joueur * adversaire);
bool directionValide(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], int caseDepart[2], int uneDirection, int coorJetonsPris[8][2], int * count, char couleurAdversaire, char objectif);
bool directionJouable(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], int caseDepart[2], int uneDirection, int * count, char couleurAdversaire, char objectif);
bool analyseCoupsJouables(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], Joueur * joueurCourant, Joueur * adversaire, ListeCoupsJouables * coupsJouables);
void ajouteCoupsJouablesPlateau(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], ListeCoupsJouables * coupsJouables);
void retireCoupsJouablesPlateau(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], ListeCoupsJouables * coupsJouables);
bool caseExiste(int x, int y);

// JOUEUR
void ajouteJetonJoueur(Joueur * unJoueur, Jeton unJeton);
void ajouteJetonJoueur(Joueur * unJoueur, int coordonnees[2]);

// MAIN
bool saisieCorrecte(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], char saisieUt[2], int coorCase[2]);
void convertCoordonnees(char saisieUt[2], int saisieTraduite[2]);

#endif