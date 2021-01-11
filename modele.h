#ifndef MODELE_H
#define MODELE_H

typedef struct Jeton{
    char couleur; //'b' = blanc, 'n' = noir
    int coordonnees[2]; // abscisse, ordonné
}Jeton;

typedef struct Joueur{
    char nom[20];
    char couleur;
    Jeton listeJetons[64];
    int nbJeton;
}Joueur;

const int MAXLARGEUR = 8;
typedef struct Jeu{
    Joueur joueur1;
    Joueur joueur2;
    Joueur * joueurCourant;
    char plateau[MAXLARGEUR][MAXLARGEUR];
}Jeu;

// JEU
void initJeu(Jeu * unJeu);
void initJeton(Jeton * unJeton, char couleur, int coordonnees[2]);

// PLATEAU
void initPlateau(char plateau[MAXLARGEUR][MAXLARGEUR]);

// JOUEUR
void initJoueur(Joueur * unJoueur, char uneCouleur);

#endif