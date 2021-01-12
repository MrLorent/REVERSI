#include <iostream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;

int main(){
    Jeu leJeu;
    Jeton nouveauJeton;
    char saisieUt[2];
    int casePrise[2];
    bool partieTerminee = false;

    initJeu(&leJeu);
    
    do{
        // DÉBUT DU TOUR
        // Affichage des informations sur le joueur courant
        //system("cls");
        cout << "NOUVEAU TOUR DE JEU:" << endl;
        cout << "Joueur courant: " << leJeu.joueurCourant->nom << endl;
        cout << "Nombre de jeton du joueur courant: " << leJeu.joueurCourant->nbJeton << endl;

        // Mise à jour des données du plateau
        ajouteJetonPlateau(leJeu.joueur1, leJeu.plateau);
        ajouteJetonPlateau(leJeu.joueur2, leJeu.plateau);
        
        // Affichage du plateau
        affichePlateau(leJeu.plateau);

        // DÉROULÉ DU TOUR
        cout << "Quelle case souhaitez-vous prendre " << leJeu.joueurCourant->nom << " ?" << endl;
        do{
            cin >> saisieUt;
        }while(!saisieCorrecte(leJeu.plateau, saisieUt, casePrise, leJeu.joueurCourant->couleur));
        cout << casePrise[0] << endl;
        cout << casePrise[1] << endl;

        // FIN DU TOUR
        initJeton(&nouveauJeton, leJeu.joueurCourant->couleur, casePrise);
        ajouteJetonJoueur(leJeu.joueurCourant, nouveauJeton);
        // Passage au tour suivant
        changeJoueurCourant(&leJeu);
    }while(!partieTerminee);

    return 0;
}

bool saisieCorrecte(char plateau[MAXLARGEUR][MAXLARGEUR], char saisieUt[2], int coorCase[2], char couleurJoueur){
    // On traite le cas où les coordonnées sont saisies dans l'ordre inverse
    if((saisieUt[1] >= 'A' && saisieUt[1] <= 'H') || (saisieUt[1] >= 'a' && saisieUt[1] <= 'h')){
        int tmp;
        tmp = saisieUt[0];
        saisieUt[0] = saisieUt[1];
        saisieUt[1] = tmp;
    }

    // Dans un premier temps, on vérifie que la case saisie fait bien partie du tableau
    saisieUt[0] = tolower(saisieUt[0]);
    if(!(saisieUt[0] >= 'a' && saisieUt[0] <= 'h') || !(saisieUt[1] >= '1' && saisieUt[1] <= '8')){
        cout << "Erreur: la case saisie n'existe pas dans la grille." << endl;
        cout << "Veuillez saisir une nouvelle case :" << endl;
        return false;
    }else{
        // Dans un second temps, on traduit l'entrée utilisateur en coordonnées pour vérifier si la case est disponible
        convertCoordonnees(saisieUt, coorCase);
        // ATTENTION: Ici pour des questions d'affichages du plateau, les ordonnées sont données en PREMIER, et les abscisses en SECOND!
        if(plateau[coorCase[1]][coorCase[0]] != 'v'){
            cout << "Erreur: la case saisie est déjà occupée." << endl;
            cout << "Veuillez saisir une nouvelle case :" << endl;
            return false;
        }else{
            if(verifPlacement(plateau, coorCase, couleurJoueur)){
                return true;
            }else{
                cout << "Placement incorrect" << endl;
                return false;
            }
            
        }
    }
}

bool verifPlacement(char plateau[MAXLARGEUR][MAXLARGEUR], int caseSouhaitee[2], char couleurJoueur ){
    bool coupValide = false;
    char couleurAdversaire;
    int directionsPossible[8][2];

    directionsPossible[HAUT_GAUCHE][0] = caseSouhaitee[0]-1;
    directionsPossible[HAUT_GAUCHE][1] = caseSouhaitee[1]-1;

    directionsPossible[HAUT_MILIEU][0] = caseSouhaitee[0];
    directionsPossible[HAUT_MILIEU][1] = caseSouhaitee[1]-1;

    directionsPossible[HAUT_DROIT][0] = caseSouhaitee[0]+1;
    directionsPossible[HAUT_DROIT][1] = caseSouhaitee[1]-1;

    directionsPossible[MILIEU_GAUCHE][0] = caseSouhaitee[0]-1;
    directionsPossible[MILIEU_GAUCHE][1] = caseSouhaitee[1];

    directionsPossible[MILIEU_DROIT][0] = caseSouhaitee[0]+1;
    directionsPossible[MILIEU_DROIT][1] = caseSouhaitee[1];

    directionsPossible[BAS_GAUCHE][0] = caseSouhaitee[0]-1;
    directionsPossible[BAS_GAUCHE][1] = caseSouhaitee[1]+1;

    directionsPossible[BAS_MILIEU][0] = caseSouhaitee[0];
    directionsPossible[BAS_MILIEU][1] = caseSouhaitee[1]+1;

    directionsPossible[BAS_DROIT][0] = caseSouhaitee[0]+1;
    directionsPossible[BAS_DROIT][1] = caseSouhaitee[1]+1;


    if(couleurJoueur == 'b'){
        couleurAdversaire = 'n';
    }else{
        couleurAdversaire = 'b';
    }

    for(int i=0; i<8;i++){
        if(plateau[directionsPossible[i][1]][directionsPossible[i][0]] == couleurAdversaire){
            int count = 0;

            switch (i)
            {
            case HAUT_GAUCHE:
                do{
                    count++;
                }while(plateau[directionsPossible[i][1]-count][directionsPossible[i][0]-count] == couleurAdversaire);

                if(plateau[directionsPossible[i][1]-count][directionsPossible[i][0]-count] == couleurJoueur){
                    coupValide = true;
                }
                break;

            case HAUT_MILIEU:
                do{
                    count++;
                }while(plateau[directionsPossible[i][1]-count][directionsPossible[i][0]] == couleurAdversaire);

                if(plateau[directionsPossible[i][1]-count][directionsPossible[i][0]] == couleurJoueur){
                    coupValide = true;
                }
                break;

            case HAUT_DROIT:
                do{
                    count++;
                }while(plateau[directionsPossible[i][1]-count][directionsPossible[i][0]+count] == couleurAdversaire);

                if(plateau[directionsPossible[i][1]-count][directionsPossible[i][0]+count] == couleurJoueur){
                    coupValide = true;
                }
                break;

            case MILIEU_GAUCHE:
                do{
                    count++;
                }while(plateau[directionsPossible[i][1]][directionsPossible[i][0]-count] == couleurAdversaire);
                
                if(plateau[directionsPossible[i][1]][directionsPossible[i][0]-count] == couleurJoueur){
                    coupValide = true;
                }
                break;

            case MILIEU_DROIT:
                do{
                    count++;
                }while(plateau[directionsPossible[i][1]][directionsPossible[i][0]+count] == couleurAdversaire);
                
                if(plateau[directionsPossible[i][1]][directionsPossible[i][0]+count] == couleurJoueur){
                    coupValide = true;
                }
                break;

            case BAS_GAUCHE:
                do{
                    count++;
                }while(plateau[directionsPossible[i][1]+count][directionsPossible[i][0]-count] == couleurAdversaire);
                
                if(plateau[directionsPossible[i][1]+count][directionsPossible[i][0]-count] == couleurJoueur){
                    coupValide = true;
                }
                break;

            case BAS_MILIEU:
                do{
                    count++;
                }while(plateau[directionsPossible[i][1]+count][directionsPossible[i][0]] == couleurAdversaire);
                
                if(plateau[directionsPossible[i][1]+count][directionsPossible[i][0]] == couleurJoueur){
                    coupValide = true;
                }
                break;

            case BAS_DROIT:
                do{
                    count++;
                }while(plateau[directionsPossible[i][1]+count][directionsPossible[i][0]+count] == couleurAdversaire);
                
                if(plateau[directionsPossible[i][1]+count][directionsPossible[i][0]+count] == couleurJoueur){
                    coupValide = true;
                }
                break;

            default:
                cout << "error" << endl;
                break;
            }
        }
    }

    return coupValide;
}

void convertCoordonnees(char saisieUt[2], int coorCase[2]){
    switch (saisieUt[0])
        {
        case 'a':
            coorCase[0] = 0;
            break;
        case 'b':
            coorCase[0] = 1;
            break;
        case 'c':
            coorCase[0] = 2;
            break;
        case 'd':
            coorCase[0] = 3;
            break;
        case 'e':
            coorCase[0] = 4;
            break;
        case 'f':
            coorCase[0] = 5;
            break;
        case 'g':
            coorCase[0] = 6;
            break;
        default:
            coorCase[0] = 7;
            break;
        }
    coorCase[1] = ((int)(saisieUt[1] - '0')) - 1;
}