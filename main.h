#include <iostream>
#include <cstring>

using namespace std;

typedef struct Jeton{
    char couleur; //'b' = blanc, 'n' = noir
    int coordonnees[2]; // abscisse, ordonné
    Jeton * suivant;
}Jeton;

typedef struct Joueur{
    char nom[20];
    Jeton * listeJetons;
    int nbJeton;
}Joueur;

const int MAXLARGEUR = 8;
typedef struct Jeu{
    Joueur joueur1;
    Joueur joueur2;
    Joueur * joueurCourant;
    char plateau[MAXLARGEUR][MAXLARGEUR];
}Jeu;

/*-------------------- PROTOTYPES ------------------*/

// JEU
// Constructeurs
void initJeu(Jeu * unJeu);
// Accesseurs
void changeJoueurCourant(Jeu * unJeu);
// Affichage

// PLATEAU
// Constructeurs
void initPlateau(char plateau[MAXLARGEUR][MAXLARGEUR]);
// Accesseurs
// Affichage
void affichePlateau(char plateau[MAXLARGEUR][MAXLARGEUR]);
void afficheLigneTransition();

// JOUEUR
// Constructeurs
void initJoueur(Joueur * joueur);
// Accesseurs
void ajouteJeton(Joueur * unJoueur, Jeton * unJeton);
// Affichage
void afficheJoueur(Joueur joueur);

// JETON
// Constructeurs
void initJeton(Jeton * unJeton, char couleur, int coordonnees[2]);
// Accesseurs
// Affichage