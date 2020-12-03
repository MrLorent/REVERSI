#include "main.h"

int main(){
    Joueur joueur1, joueur2;
    initJoueur(&joueur1);
    initJoueur(&joueur2);
    afficheJoueur(joueur1);
    afficheJoueur(joueur2);

    char plateau[MAXLARGEUR][MAXLARGEUR];
    initPlateau(plateau);
    affichePlateau(plateau);
    return 0;
}