#include "main.h"

int main(){
    Jeu leJeu;
    char tourSuivant ='y';

    initJeu(&leJeu);
    afficheJoueur(leJeu.joueur1);
    afficheJoueur(leJeu.joueur2);
    
    do{
        cout << "Joueur courant: " << (*leJeu.joueurCourant).nom << endl;
        cout << "Nombre de jeton du joueur courant: " << (*leJeu.joueurCourant).nbJeton << endl;
        ajouteJetonPlateau(leJeu.joueur1, leJeu.plateau);
        ajouteJetonPlateau(leJeu.joueur2, leJeu.plateau);
        affichePlateau(leJeu.plateau);

        changeJoueurCourant(&leJeu);
        cout << "Passer au tour suivant ? (y/n)" << endl;
        cin >> tourSuivant;
    }while(tourSuivant == 'y');

    return 0;
}