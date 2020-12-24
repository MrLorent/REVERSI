#include <iostream>
#include <cstring>

using namespace std;

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
void ajouteJetonPlateau(Joueur unJoueur, char lePlateau[MAXLARGEUR][MAXLARGEUR]);
// Affichage
void affichePlateau(char plateau[MAXLARGEUR][MAXLARGEUR]);
void afficheLigneTransition();

// JOUEUR
// Constructeurs
void initJoueur(Joueur * unJoueur, char uneCouleur);
// Accesseurs
void ajouteJetonJoueur(Joueur * unJoueur, Jeton unJeton);
// Affichage
void afficheJoueur(Joueur joueur);

// JETON
// Constructeurs
void initJeton(Jeton * unJeton, char couleur, int coordonnees[2]);
// Accesseurs
// Affichage

// MAIN
// Gestion des saisies utilisateur
int verifSaisie(char plateau[MAXLARGEUR][MAXLARGEUR], char saisieUt[2], int saisieTraduite[2]);
void convertCoordonnees(char saisieUt[2], int saisieTraduite[2]);