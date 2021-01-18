#ifndef MODELE_H
#define MODELE_H

const int VECTEURS[8][2] = {
    {-1, -1}, // HAUT_GAUCHE
    {0, -1}, // HAUT_MILIEU
    {1, -1}, // HAUT_DROIT
    {1, 0}, // MILIEU_DROIT
    {1, 1}, // BAS_DROIT
    {0, 1}, // BAS_MILIEU
    {-1, 1}, // BAS_GAUCHE
    {-1, 0} // MILIEU_GAUCHE
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