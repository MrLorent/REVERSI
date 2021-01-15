#include <iostream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;

void initPlateau(Jeton * plateau[MAXLARGEUR][MAXLARGEUR]){
    // Initialisation de chaque case à "vide"
    for(int l=0;l<MAXLARGEUR;l++){
        for(int c=0;c<MAXLARGEUR;c++){
            plateau[l][c] = NULL;
        }
    }
}

void ajouteJetonPlateau(Joueur * unJoueur, Jeton * lePlateau[MAXLARGEUR][MAXLARGEUR]){
    for(int i=0; i < unJoueur->nbJeton; i++){
        // ATTENTION: Ici pour des questions d'affichages du plateau, les ordonnées sont données en PREMIER, et les abscisses en SECOND!
        lePlateau[unJoueur->listeJetons[i].coordonnees[1]][unJoueur->listeJetons[i].coordonnees[0]] = &(unJoueur->listeJetons[i]);
    }
}

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
            if(plateau[l][c] == NULL){
                cout << "   |";
            }else{
                switch (plateau[l][c]->couleur)
                {
                case 'b':
                    cout << " * |";
                    break;
                case 'n':
                    cout << " 0 |";
                    break;
                case 'j':
                    cout << " # |";
                    break;
                default:
                    cout << "   |";
                    break;
                }
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

bool captureJeton(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], int caseSouhaitee[2], Joueur * joueurCourant, Joueur * adversaire){
    bool coupValide = false;

    for(int i=0; i<8;i++){
        if(plateau[caseSouhaitee[1]+VECTEURS[i][1]][caseSouhaitee[0]+VECTEURS[i][0]] != NULL && plateau[caseSouhaitee[1]+VECTEURS[i][1]][caseSouhaitee[0]+VECTEURS[i][0]]->couleur == adversaire->couleur){
            // count servira lorsque l'on voudra voir quel coup capture le plus de jeton pour l'IA 
            int nbJetonsPris = 0;
            int coorJetonsPris[8][2];

            if(directionValide(plateau, caseSouhaitee, i, coorJetonsPris, &nbJetonsPris, adversaire->couleur, joueurCourant->couleur)){
                coupValide = true;
                for(int i=0;i<nbJetonsPris;i++){
                    int count = 0;
                    bool transfere = false;

                    while(count < adversaire->nbJeton && !transfere){
                        if(adversaire->listeJetons[count].coordonnees[0] == coorJetonsPris[i][0] && adversaire->listeJetons[count].coordonnees[1] == coorJetonsPris[i][1]){
                            adversaire->listeJetons[count] = adversaire->listeJetons[adversaire->nbJeton - 1];
                            adversaire->nbJeton = adversaire->nbJeton -1;

                            Jeton unJeton;
                            initJeton(&unJeton, joueurCourant->couleur, coorJetonsPris[i]);
                            ajouteJetonJoueur(joueurCourant, unJeton);
                            transfere = true;
                        }
                        count++;
                    }
                }
            }
        }
    }

    if(!coupValide){
        cout << "Erreur: vous devez prendre possession d'un moins un jeton adverse." << endl;
        cout << "Veuillez saisir une nouvelle case :" << endl;
    }

    return coupValide;
}

bool directionValide(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], int caseDepart[2], int uneDirection, int coorJetonsPris[8][2], int * count, char couleurAdversaire, char objectif){
    char contenuCaseSuivante;
    int caseSuivante[2];
    
    if(plateau[caseDepart[1] + VECTEURS[uneDirection][1]][caseDepart[0] + VECTEURS[uneDirection][0]] != NULL){
        contenuCaseSuivante = plateau[caseDepart[1] + VECTEURS[uneDirection][1]][caseDepart[0] + VECTEURS[uneDirection][0]]->couleur;
        caseSuivante[0] = caseDepart[0] + VECTEURS[uneDirection][0];
        caseSuivante[1] = caseDepart[1] + VECTEURS[uneDirection][1];
        if(contenuCaseSuivante == couleurAdversaire){
            coorJetonsPris[*count][0] = caseSuivante[0];
            coorJetonsPris[*count][1] = caseSuivante[1];
            (*count)++;
            return directionValide(plateau, caseSuivante, uneDirection, coorJetonsPris, count, couleurAdversaire, objectif);
        }else{
            return true;
        }
    }else{
        return false;
    }
}

void ajouteCoupsJouablesPlateau(char plateau[MAXLARGEUR][MAXLARGEUR], int coupsJouables[10][2], int nbCoupsJouables){
    for(int i=0; i < nbCoupsJouables; i++){
        plateau[coupsJouables[i][1]][coupsJouables[i][0]] = 'j';
    }
}

// void analyseCoupsJouables(char plateau[MAXLARGEUR][MAXLARGEUR], Joueur * joueurCourant, Joueur * adversaire, int coupsJouables[10][2], int * nbCoupsJouables){
//     int positionJeton[2];
//     for(int i = 0; i < joueurCourant->nbJeton; i++){
//         positionJeton[0] = joueurCourant->listeJetons[i].coordonnees[0];
//         positionJeton[1] = joueurCourant->listeJetons[i].coordonnees[1];

//         for(int j=0; j<8;j++){
//         if(plateau[positionJeton[1]+VECTEURS[j][1]][positionJeton[0]+VECTEURS[j][0]] == adversaire->couleur){
//             // count servira lorsque l'on voudra voir quel coup capture le plus de jeton pour l'IA 
//             int count = 0;
//             int coorJetonsPris[8][2];

//             if(directionValide(plateau, positionJeton, j, coorJetonsPris, &count, adversaire->couleur, 'v')){
//                 count++;
//                 coupsJouables[*nbCoupsJouables][0] = positionJeton[0]+VECTEURS[j][0]*count;
//                 coupsJouables[*nbCoupsJouables][1] = positionJeton[1]+VECTEURS[j][1]*count;
//                 (*nbCoupsJouables)++;
//                 }
//             }
//         }
//     }
// }