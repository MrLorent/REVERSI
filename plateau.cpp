#include <iostream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;

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

bool captureJeton(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], int caseSouhaitee[2], Joueur * joueurCourant, Joueur * adversaire){
    bool coupValide = false;

    for(int i=0; i<8;i++){
        if(caseExiste(caseSouhaitee[0]+VECTEURS[i][0], caseSouhaitee[1]+VECTEURS[i][1])
        && plateau[caseSouhaitee[1]+VECTEURS[i][1]][caseSouhaitee[0]+VECTEURS[i][0]]->couleur == adversaire->couleur){
            // count servira lorsque l'on voudra voir quel coup capture le plus de jeton pour l'IA 
            int nbJetonsPris = 0;
            int coorJetonsPris[8][2];

            if(directionValide(plateau, caseSouhaitee, i, coorJetonsPris, &nbJetonsPris, adversaire->couleur, joueurCourant->couleur)){
                coupValide = true;
                for(int i=0; i < nbJetonsPris; i++){
                    supprimeJetonJoueur(adversaire, coorJetonsPris[i]);
                    ajouteJetonJoueur(joueurCourant, coorJetonsPris[i]);
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
    Jeton * contenuCaseSuivante;
    int caseSuivante[2];
    
    if(caseExiste(caseDepart[0] + VECTEURS[uneDirection][0], caseDepart[1] + VECTEURS[uneDirection][1])){
        contenuCaseSuivante = plateau[caseDepart[1] + VECTEURS[uneDirection][1]][caseDepart[0] + VECTEURS[uneDirection][0]];
        caseSuivante[0] = caseDepart[0] + VECTEURS[uneDirection][0];
        caseSuivante[1] = caseDepart[1] + VECTEURS[uneDirection][1];

        if(contenuCaseSuivante->couleur == couleurAdversaire){
            coorJetonsPris[*count][0] = caseSuivante[0];
            coorJetonsPris[*count][1] = caseSuivante[1];
            (*count)++;
            return directionValide(plateau, caseSuivante, uneDirection, coorJetonsPris, count, couleurAdversaire, objectif);
        }else{
            if(contenuCaseSuivante->couleur == objectif){
                return true;
            }else{
                return false;
            }
        }
    }else{
        return false;
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
    CoupJouable * tmp;

    while(*coupsJouables != NULL){
        if((*coupsJouables)->emplacement->couleur = 'j'){
            (*coupsJouables)->emplacement->couleur = 'v';
        }
        tmp = *coupsJouables;
        *coupsJouables = (*coupsJouables)->suivant;
        free(tmp);
    }
}

bool analyseCoupsJouables(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], Joueur * joueurCourant, Joueur * adversaire, ListeCoupsJouables * coupsJouables){
    int positionJeton[2];
    bool unCoupJouable = false;

    for(int i = 0; i < joueurCourant->nbJeton; i++){
        positionJeton[0] = joueurCourant->listeJetons[i].coordonnees[0];
        positionJeton[1] = joueurCourant->listeJetons[i].coordonnees[1];

        for(int j=0; j<8;j++){
        if(caseExiste(positionJeton[0]+VECTEURS[j][0], positionJeton[1]+VECTEURS[j][1]) && plateau[positionJeton[1]+VECTEURS[j][1]][positionJeton[0]+VECTEURS[j][0]]->couleur == adversaire->couleur){
            // count servira lorsque l'on voudra voir quel coup capture le plus de jeton pour l'IA 
            int count = 0;

            if(directionJouable(plateau, positionJeton, j, &count, adversaire->couleur, 'v')){
                unCoupJouable = true;
                count++;
                enregistreCoupJouable(coupsJouables, plateau[positionJeton[1]+VECTEURS[j][1]*count][positionJeton[0]+VECTEURS[j][0]*count]);
                }
            }
        }
    }

    return unCoupJouable;
}

bool directionJouable(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], int caseDepart[2], int uneDirection, int * count, char couleurAdversaire, char objectif){
    Jeton * contenuCaseSuivante;
    int caseSuivante[2];
    
    if(caseExiste(caseDepart[0] + VECTEURS[uneDirection][0], caseDepart[1] + VECTEURS[uneDirection][1])){
        contenuCaseSuivante = plateau[caseDepart[1] + VECTEURS[uneDirection][1]][caseDepart[0] + VECTEURS[uneDirection][0]];
        caseSuivante[0] = caseDepart[0] + VECTEURS[uneDirection][0];
        caseSuivante[1] = caseDepart[1] + VECTEURS[uneDirection][1];

        if(contenuCaseSuivante->couleur == couleurAdversaire){
            (*count)++;
            return directionJouable(plateau, caseSuivante, uneDirection, count, couleurAdversaire, objectif);
        }else{
            if(contenuCaseSuivante->couleur == objectif){
                return true;
            }else{
                return false;
            }
        }
    }else{
        return false;
    }
}

bool caseExiste(int x, int y){
    return (x >= 0 && x <= 7) && (y >= 0 && y <= 7);
}