#include "main.h"

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