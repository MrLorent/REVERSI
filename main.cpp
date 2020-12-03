#include "main.h"

/*---------------PROTOTYPES-------------*/
void affichePlateau(char plateau[MAXLARGEUR][MAXLARGEUR]);
void afficheLigneTransition();

int main(){
    char plateau[MAXLARGEUR][MAXLARGEUR];
    initPlateau(plateau);
    affichePlateau(plateau);
    return 0;
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