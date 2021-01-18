#include <iostream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;

// MODÈLE
void initPlateau(Jeton * plateau[MAXLARGEUR][MAXLARGEUR]){
    // Chaque case est remplie d'un marqueur indiquant que la case est "vide"
    for(int l=0;l<MAXLARGEUR;l++){
        for(int c=0;c<MAXLARGEUR;c++){
            plateau[l][c]= new Marqueur;
            int coor[2] = {c , l};
            initMarqueur(plateau[l][c], coor);
        }
    }
}

// VUES
void affichePlateau(Jeton * plateau[MAXLARGEUR][MAXLARGEUR]){
    const char tabLettres[MAXLARGEUR] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
    const char tabChiffres[MAXLARGEUR] = { '1', '2', '3', '4', '5', '6', '7', '8' };

    // Espacement
    cout << endl;
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
            switch (plateau[l][c]->couleur)
            {
            case 'b':
                cout << " X |";
                break;
            case 'n':
                cout << " O |";
                break;
            case 'j':
                cout << " * |";
                break;
            default:
                cout << "   |";
                break;
            }
        }
        cout << endl;
        afficheLigneTransition();
    }
    // Espacement
    cout << endl;
}

void afficheLigneTransition(){
    cout << "   ";
    for(int l=0; l < MAXLARGEUR-1; l++){
        cout << "+---";
    }
    cout << "+---+" << endl;
}

// CONTROLEURS
void ajouteJetonPlateau(Joueur * unJoueur, Jeton * lePlateau[MAXLARGEUR][MAXLARGEUR]){
    Jeton * tmp = unJoueur->listeJetons;
    
    while(tmp != NULL){
        // ATTENTION: Ici pour des questions d'affichages du plateau, les ordonnées sont données en PREMIER, et les abscisses en SECOND!
        lePlateau[tmp->coordonnees[1]][tmp->coordonnees[0]] = tmp;
        tmp = tmp->suivant;
    }
}

void ajouteCoupsJouablesPlateau(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], ListeCoupsJouables * coupsJouables){
    CoupJouable * tmp = *coupsJouables;

    while(tmp != NULL){
        tmp->emplacement->couleur = 'j';
        tmp = tmp->suivant;
    }
}

void retireCoupsJouablesPlateau(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], ListeCoupsJouables * coupsJouables){
    CoupJouable * tmp = *coupsJouables;

    while(tmp != NULL){
        if(tmp->emplacement->couleur == 'j'){
            tmp->emplacement->couleur = 'v';
        }
        tmp = tmp->suivant;
    }

    videListeCoupsJouables(coupsJouables);
}

bool caseExiste(int x, int y){
    return (x >= 0 && x <= 7) && (y >= 0 && y <= 7);
}