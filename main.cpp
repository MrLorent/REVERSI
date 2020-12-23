#include "main.h"

int main(){
    Jeu leJeu;
    char tourSuivant ='y';

    initJeu(&leJeu);
    
    do{
        // DÉBUT DU TOUR
        // Affichage des informations sur le joueur courant
        cout << endl;
        cout << "NOUVEAU TOUR DE JEU:" << endl;
        cout << "Joueur courant: " << leJeu.joueurCourant->nom << endl;
        cout << "Nombre de jeton du joueur courant: " << leJeu.joueurCourant->nbJeton << endl;

        // Mise à jour des données du plateau
        ajouteJetonPlateau(leJeu.joueur1, leJeu.plateau);
        ajouteJetonPlateau(leJeu.joueur2, leJeu.plateau);
        
        // Affichage du plateau
        affichePlateau(leJeu.plateau);

        // DÉROULÉ DU TOUR

        // FIN DU TOUR
        // Passage au tour suivant
        changeJoueurCourant(&leJeu);
        cout << "Passer au tour suivant ? (y/n)" << endl;
        cin >> tourSuivant;
    }while(tourSuivant == 'y');

    return 0;
}