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
void affichePlateau(char plateau[MAXLARGEUR][MAXLARGEUR]);
void afficheLigneTransition();

int main(){
    char plateau[MAXLARGEUR][MAXLARGEUR];
    initPlateau(plateau);
    affichePlateau(plateau);
    return 0;
}

void initPlateau(char plateau[MAXLARGEUR][MAXLARGEUR]){
    // Initialisation de chaque case à "vide"
    for(int l=0;l<MAXLARGEUR;l++){
        for(int c=0;c<MAXLARGEUR;c++){
            plateau[l][c]='v';
        }
    }

    // Initialisation des quatres premiers jetons au centre
    // C'est provisoire, il faudrait qu'ils soient placés via lecture de la liste de jeton
    plateau[3][3] = 'b';
    plateau[3][4] = 'n';
    plateau[4][3] = 'n';
    plateau[4][4] = 'b';
}

void affichePlateau(char plateau[MAXLARGEUR][MAXLARGEUR]){
    const char tabLettres[MAXLARGEUR] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
    const char tabChiffres[MAXLARGEUR] = { '1', '2', '3', '4', '5', '6', '7', '8' };

    // Affichage de la première ligne de lettres
    cout << "  ";
    for(int i=0; i<MAXLARGEUR;i++){
        if(i == MAXLARGEUR-1){
            cout << "   " << tabLettres[MAXLARGEUR-1] << "  " << endl;
        }else
        {
            cout << "   " << tabLettres[i];
        }
    }
    afficheLigneTransition();

    // Affichage du plateau
    for(int l=0; l < MAXLARGEUR; l++){
        //on affiche le numéro de ligne
        cout << " " << tabChiffres[l] << " |";
        for(int c=0; c < MAXLARGEUR; c++){
            switch (plateau[l][c])
            {
            case 'b':
                cout << " * |";
                break;
            case 'n':
                cout << " 0 |";
                break;
            default:
                cout << "   |";
                break;
            }
        }
        cout << endl;
        afficheLigneTransition();
    }
}

void afficheLigneTransition(){
    cout << "   ";
    for(int l=0; l < MAXLARGEUR-1; l++){
        cout << "+---";
    }
    cout << "+---+" << endl;
}