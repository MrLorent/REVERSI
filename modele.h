#ifndef MODELE_H
#define MODELE_H

const int HAUT_GAUCHE = 0;
const int HAUT_MILIEU = 1;
const int HAUT_DROIT = 2;
const int MILIEU_GAUCHE = 3;
const int MILIEU_DROIT = 4;
const int BAS_GAUCHE = 5;
const int BAS_MILIEU = 6;
const int BAS_DROIT = 7;

const int VECTEURS[8][2] = {
    {-1, -1},
    {0, -1},
    {1, -1},
    {-1, 0},
    {1, 0},
    {-1, 1},
    {0, 1},
    {1, 1}
};


typedef struct Jeton{
    char couleur; //'b' = blanc, 'n' = noir
    int coordonnees[2]; // abscisse, ordonné
    struct Jeton * suivant;
}Jeton, Marqueur, *ListeJetons, *ListeMarqueurs;

typedef struct CoupJouable{
    Marqueur * emplacement;
    ListeJetons jetonsCaptures;
    int nbCaptures;
    struct CoupJouable * suivant;
}CoupJouable, *ListeCoupsJouables;

typedef struct Joueur{
    char nom[20];
    char couleur;
    int nbJeton;
    ListeJetons listeJetons;
}Joueur;

const int MAXLARGEUR = 8;
typedef struct Jeu{
    Joueur joueur1;
    Joueur joueur2;
    Joueur * joueurCourant;
    Joueur * joueurEnAttente;
    ListeCoupsJouables coupsJouables;
    Jeton * plateau[MAXLARGEUR][MAXLARGEUR];
}Jeu;

// JEU
void initJeu(Jeu * unJeu);

// PLATEAU
void initPlateau(Jeton * plateau[MAXLARGEUR][MAXLARGEUR]);

// JETON
void initJeton(Jeton * unJeton, char couleur, int coordonnees[2]);
void initMarqueur(Marqueur * unMarqueur, int coordonnees[2]);

// JOUEUR
void initJoueur(Joueur * unJoueur, char uneCouleur);

#endif