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
    Jeton * tmp = unJoueur->listeJetons;
    
    while(tmp != NULL){
        // ATTENTION: Ici pour des questions d'affichages du plateau, les ordonnées sont données en PREMIER, et les abscisses en SECOND!
        lePlateau[tmp->coordonnees[1]][tmp->coordonnees[0]] = tmp;
        tmp = tmp->suivant;
    }
}

bool caseExiste(int x, int y){
    return (x >= 0 && x <= 7) && (y >= 0 && y <= 7);
}

bool coupJouable(Jeu * leJeu, ListeCoupsJouables * coupsJouables, int caseSouhaitee[2]){
    int rang = estEnregistre(coupsJouables, caseSouhaitee);
    bool coupValide = false;
    
    if(rang >= 0){
        CoupJouable * tmp1 = *coupsJouables; 

        coupValide = true;

        for(int i=0; i<rang-1; i++){
            tmp1 = tmp1->suivant;
        }

        Capture * tmp2 = tmp1->captures;
        while(tmp2 != NULL){
            cout << "coorCaptures : x=" << tmp2->jeton->coordonnees[0] << " y=" << tmp2->jeton->coordonnees[1] << endl;
                supprimeJetonJoueur(leJeu->joueurEnAttente, tmp2->jeton->coordonnees);
                //ajouteJetonJoueur(leJeu->joueurCourant, tmp2->jeton->coordonnees);
            tmp2 = tmp2->suivant;
        }
        
    }else{
        cout << "Erreur: vous devez au moins capturer un jeton adverse." << endl;
        cout << "Veuillez saisir une nouvelle case :" << endl;
    }

    return coupValide;
}

bool analyseCoupsJouables(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], Joueur * joueurCourant, Joueur * adversaire, ListeCoupsJouables * coupsJouables){
    Jeton * tmp = joueurCourant->listeJetons;

    while(tmp != NULL){
        bool leCoupEstJouable = false;
        Jeton * leCoupJouable = NULL;
        ListeCaptures * jetonsCaptures = new ListeCaptures;
        *jetonsCaptures = NULL;

        for(int direction=0; direction<8;direction++){
            if(caseExiste(tmp->coordonnees[0]+VECTEURS[direction][0], tmp->coordonnees[1]+VECTEURS[direction][1]) && plateau[tmp->coordonnees[1]+VECTEURS[direction][1]][tmp->coordonnees[0]+VECTEURS[direction][0]]->couleur == adversaire->couleur){
                int count = 0;

                if(directionJouable(plateau, tmp->coordonnees, direction, jetonsCaptures, &count, adversaire->couleur, 'v')){
                    leCoupEstJouable = true;
                    leCoupJouable = plateau[tmp->coordonnees[1]+VECTEURS[direction][1]*(count+1)][tmp->coordonnees[0]+VECTEURS[direction][0]*(count+1)];
                    enregistreCoupJouable(coupsJouables, leCoupJouable, jetonsCaptures, count);
                    videListe(jetonsCaptures);
                }
            }
        }
        if(*jetonsCaptures != NULL){
            videListe(jetonsCaptures);
            free(jetonsCaptures);
        }

        tmp = tmp->suivant;
    }

    if(*coupsJouables != NULL){
        return true;
    }else{
        return false;
    }
    
}

bool directionJouable(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], int caseDepart[2], int uneDirection, ListeCaptures * jetonsCaptures, int * count, char couleurAdversaire, char objectif){
    Jeton * caseSuivante;
    int coorCaseSuivante[2];
    
    if(caseExiste(caseDepart[0] + VECTEURS[uneDirection][0], caseDepart[1] + VECTEURS[uneDirection][1])){
        caseSuivante = plateau[caseDepart[1] + VECTEURS[uneDirection][1]][caseDepart[0] + VECTEURS[uneDirection][0]];
        coorCaseSuivante[0] = caseDepart[0] + VECTEURS[uneDirection][0];
        coorCaseSuivante[1] = caseDepart[1] + VECTEURS[uneDirection][1];

        if(caseSuivante->couleur == couleurAdversaire){
            ajouteJetonCapture(jetonsCaptures, caseSuivante);
            (*count)++;
            return directionJouable(plateau, coorCaseSuivante, uneDirection, jetonsCaptures, count, couleurAdversaire, objectif);
        }else{
            if(caseSuivante->couleur == objectif){
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
        cout << "nbCaptures: " << tmp->nbCaptures << endl;
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
