#include <iostream>
#include <cstring>

using namespace std;

typedef struct Jeton{
    char couleur; //'b' = blanc, 'n' = noir
    int coordonnees[2]; // abscisse, ordonné
}Jeton;

typedef struct Joueur{
    string nom;
    Jeton listeJeton[64];
    int nbJeton;
}Joueur;

const int MAXLARGEUR = 8;
typedef struct Jeu{
    Joueur joueur1;
    Joueur joueur2;
    int plateau[MAXLARGEUR][MAXLARGEUR];
}Jeu;

/*---------------PROTOTYPES-------------*/
void initPlateau(char plateau[MAXLARGEUR][MAXLARGEUR]);