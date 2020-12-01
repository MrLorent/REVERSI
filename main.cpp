#include <iostream>
#include <cstring>

using namespace std;

typedef struct Jeton{
    char couleur; //'B' = blanc, 'N' = noir
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
void affichePlateau(char plateau[MAXLARGEUR][MAXLARGEUR]);

int main(){
    char plateau[MAXLARGEUR][MAXLARGEUR];
    affichePlateau(plateau);

    return 0;
}

void initPlateau(int plateau[MAXLARGEUR][MAXLARGEUR]){
    for
}

void affichePlateau(int plateau[MAXLARGEUR][MAXLARGEUR]){
    const char tabLettres[MAXLARGEUR] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
    const char tabChiffres[MAXLARGEUR] = { '1', '2', '3', '4', '5', '6', '7', '8' };

    // Affichage de la première ligne: celle des lettres
    for(int i=0; i<=MAXLARGEUR;i++){
        switch (i)
        {
        case 0:
            cout << "  ";
            break;
        case MAXLARGEUR:
            cout << "   " << tabLettres[i-1] << "  " << endl;
            break;
        default:
            cout << "   " << tabLettres[i-1];
            break;
        }
    }
    for(int l=0; l <= MAXLARGEUR; l++){
            switch (l)
            {
            case 0:
                cout << "   ";
                break;
            case MAXLARGEUR:
                cout << "+---+" << endl;
                break;
            default:
                cout << "+---";
                break;
            }
        }

    // Affichage des huits lignes du plateau
    for(int h=0; h < MAXLARGEUR; h++){
        for(int l=0; l <= MAXLARGEUR; l++){
            switch (l)
            {
            case 0:
                cout << " " << tabChiffres[h];
                break;
            case MAXLARGEUR:
                cout << " |   |" << endl;
                break;
            default:
                cout << " |  ";
                break;
            }
        }
        for(int l=0; l <= MAXLARGEUR; l++){
            switch (l)
            {
            case 0:
                cout << "   ";
                break;
            case MAXLARGEUR:
                cout << "+---+" << endl;
                break;
            default:
                cout << "+---";
                break;
            }
        }
    }
}