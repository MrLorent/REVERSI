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
        cout << "Joueur en attente: " << leJeu.joueurEnAttente->nom << endl;

        // Mise à jour des données du plateau
        ajouteJetonPlateau(leJeu.joueur1, leJeu.plateau);
        ajouteJetonPlateau(leJeu.joueur2, leJeu.plateau);
        
        // Affichage du plateau
        affichePlateau(leJeu.plateau);

        // DÉROULÉ DU TOUR
        cout << "Quelle case souhaitez-vous prendre " << leJeu.joueurCourant->nom << " ?" << endl;
        do{
            cin >> saisieUt;
        }while(!saisieCorrecte(leJeu.plateau, saisieUt, casePrise) || !captureJeton(leJeu.plateau, casePrise, leJeu.joueurCourant, leJeu.joueurEnAttente));

        // FIN DU TOUR
        initJeton(&nouveauJeton, leJeu.joueurCourant->couleur, casePrise);
        ajouteJetonJoueur(leJeu.joueurCourant, nouveauJeton);
        // Passage au tour suivant
        changeJoueurCourant(&leJeu);
    }while(!partieTerminee);

    return 0;
}

bool saisieCorrecte(char plateau[MAXLARGEUR][MAXLARGEUR], char saisieUt[2], int coorCase[2]){
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
            return true;
        }
    }
}

bool captureJeton(char plateau[MAXLARGEUR][MAXLARGEUR], int caseSouhaitee[2], Joueur * joueurCourant, Joueur * adversaire){
    bool coupValide = false;

    for(int i=0; i<8;i++){
        if(plateau[caseSouhaitee[1]+VECTEURS[i][1]][caseSouhaitee[0]+VECTEURS[i][0]] == adversaire->couleur){
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

                            Jeton nouveauJeton;
                            initJeton(&nouveauJeton, joueurCourant->couleur,coorJetonsPris[i]);
                            ajouteJetonJoueur(joueurCourant, nouveauJeton);
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

bool directionValide(char plateau[MAXLARGEUR][MAXLARGEUR], int caseDepart[2], int uneDirection, int coorJetonsPris[8][2], int * count, char couleurAdversaire, char objectif){
    char contenuCaseSuivante;
    int caseSuivante[2];
    
    contenuCaseSuivante = plateau[caseDepart[1] + VECTEURS[uneDirection][1]][caseDepart[0] + VECTEURS[uneDirection][0]];
    caseSuivante[0] = caseDepart[0] + VECTEURS[uneDirection][0];
    caseSuivante[1] = caseDepart[1] + VECTEURS[uneDirection][1];

    if(contenuCaseSuivante == couleurAdversaire){
        coorJetonsPris[*count][0] = caseSuivante[0];
        coorJetonsPris[*count][1] = caseSuivante[1];
        (*count)++;
        return directionValide(plateau, caseSuivante, uneDirection, coorJetonsPris, count, couleurAdversaire, objectif);
    }else{
        if(contenuCaseSuivante == objectif){
            return true;
        }else{
            return false;
        }
    }
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