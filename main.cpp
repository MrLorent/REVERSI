#include "main.h"

int main(){
    Jeu jeuEnCours;
    Joueur * joueurCourant = &jeuEnCours.joueur1;
    char tourSuivant ='y';

    initJeu(&jeuEnCours);
    afficheJoueur(jeuEnCours.joueur1);
    afficheJoueur(jeuEnCours.joueur2);
    
    do{
        cout << "Joueur courant: " << (*joueurCourant).nom << endl;
        cout << "Nombre de jeton du joueur courant: " << (*joueurCourant).nbJeton << endl;
        affichePlateau(jeuEnCours.plateau);

        // On change de joueur entre chaque tour
        if((*joueurCourant).nom == jeuEnCours.joueur1.nom){
            joueurCourant = &jeuEnCours.joueur2;
        }else{
            joueurCourant = &jeuEnCours.joueur1;
        }
        cout << "Passer au tour suivant ? (y/n)" << endl;
        cin >> tourSuivant;
    }while(tourSuivant == 'y');


    return 0;
}