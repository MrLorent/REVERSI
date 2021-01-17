#ifndef CONTROLEUR_H
#define CONTROLEUR_H

// JEU
void changeJoueurCourant(Jeu * unJeu);
void enregistreCoupJouable(ListeCoupsJouables * liste, Marqueur * emplacement, ListeCaptures * Captures, int nbCaptures);
void ajouteJetonCapture(ListeCaptures * liste, Jeton * jetonCapture);
void concatCaptures(ListeCaptures * liste1, ListeCaptures * liste2);
int estEnregistre(ListeCoupsJouables * coupsJouables, int coorEmplacement[2]);
void videListe(ListeCaptures * uneListe);

// PLATEAU
void ajouteJetonPlateau(Joueur * unJoueur, Jeton * lePlateau[MAXLARGEUR][MAXLARGEUR]);
bool coupJouable(Jeu * leJeu, ListeCoupsJouables * coupsJouables, int caseSouhaitee[2]);
bool directionJouable(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], int caseDepart[2], int uneDirection, ListeCaptures * jetonsCaptures, int * count, char couleurAdversaire, char objectif);
bool analyseCoupsJouables(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], Joueur * joueurCourant, Joueur * adversaire, ListeCoupsJouables * coupsJouables);
void ajouteCoupsJouablesPlateau(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], ListeCoupsJouables * coupsJouables);
void retireCoupsJouablesPlateau(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], ListeCoupsJouables * coupsJouables);
bool caseExiste(int x, int y);

// JOUEUR
void ajouteJetonJoueur(Joueur * unJoueur, int coordonnees[2]);
void supprimeJetonJoueur(Joueur * unJoueur, int coordonnees[2]);

// MAIN
bool saisieCorrecte(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], char saisieUt[2], int coorCase[2]);
void convertCoordonnees(char saisieUt[2], int saisieTraduite[2]);

#endif