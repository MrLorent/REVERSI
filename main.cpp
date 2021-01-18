#include <iostream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;

int main(){
    Jeu leJeu;
    int toursPasses = 0, actionSaisie = 0;
    int coorSaisie[2];
    char passer = 'n';
    char caseSaisie[2], nomTmp[20];
    bool partieTerminee = false;

    system("clear");
    cout << "BIENVENUE DANS NOTRE JEU DE REVERSI !" << endl;
    cout << endl;
    cout << endl;
    cout << "MENU PRINCIPAL" << endl;
    cout << endl;
    cout << " 1 - Lancer une partie contre un autre joueur." << endl;
    cout << " 2 - Lancer une partie conte Michelle (Ordinateur)." << endl;
    cout << endl;
    cout << "Veuillez saisir le numéro de l'action que vous souhaitez réaliser :" << endl;
    do{
        cin >> actionSaisie;
    }while(!saisieMenuCorrecte(actionSaisie));

    leJeu.mode = actionSaisie;
    system("clear");

    initJeu(&leJeu);
    
    do{
        // DÉBUT DU TOUR
        // Affichage des informations sur le joueur courant
        cout << "NOUVEAU TOUR DE JEU:" << endl;
        cout << "Joueur courant: " << leJeu.joueurCourant->nom << endl;
        cout << "Nombre de jeton du joueur courant: " << leJeu.joueurCourant->nbJeton << endl;

        // Mise à jour des données du plateau
        ajouteJetonPlateau(&leJeu.joueur1, leJeu.plateau);
        ajouteJetonPlateau(&leJeu.joueur2, leJeu.plateau);

        if(analyseCoupsJouables(leJeu.plateau, leJeu.joueurCourant, leJeu.joueurEnAttente, &leJeu.coupsJouables)){
            ajouteCoupsJouablesPlateau(leJeu.plateau, &leJeu.coupsJouables);
            
            if(leJeu.mode == ORDINATEUR && leJeu.joueurCourant == &leJeu.joueur2){
                CoupJouable * coupAJouer = leJeu.coupsJouables;
                CoupJouable * tmp = leJeu.coupsJouables;

                while(tmp != NULL){
                    if(tmp->nbCaptures > coupAJouer->nbCaptures){
                        coupAJouer = tmp;
                    }
                    tmp = tmp->suivant;
                }

                joueLeCoup(leJeu.plateau, coupAJouer->emplacement->coordonnees, &leJeu.joueur2, &leJeu.joueur1);

                // Affichage du plateau
                ajouteJetonPlateau(&leJeu.joueur1, leJeu.plateau);
                ajouteJetonPlateau(&leJeu.joueur2, leJeu.plateau);
                affichePlateau(leJeu.plateau);

                // FIN DU TOUR
                cout << "Michelle vient de vous capturer " << coupAJouer->nbCaptures << " jetons." << endl;
                cout << "Passer à la suite ? (o/n)" << endl;
                do{
                    cin >> passer;
                }while(passer != 'o');
            }else{
                // Affichage du plateau
                affichePlateau(leJeu.plateau);

                // DÉROULÉ DU TOUR
                cout << "Quelle case souhaitez-vous prendre " << leJeu.joueurCourant->nom << " ?" << endl;
                do{
                    cin >> caseSaisie;
                }while(!saisieCorrecte(leJeu.plateau, caseSaisie, coorSaisie) || !coupJouable(&leJeu.coupsJouables, coorSaisie, leJeu.joueurCourant, leJeu.joueurEnAttente));
                joueLeCoup(leJeu.plateau, coorSaisie, leJeu.joueurCourant, leJeu.joueurEnAttente);
            }

            // FIN DU TOUR
            toursPasses = 0;
            retireCoupsJouablesPlateau(leJeu.plateau, &leJeu.coupsJouables);
        }else{

            // Affichage du plateau
            affichePlateau(leJeu.plateau);

                do{
                    if(leJeu.mode == ORDINATEUR && leJeu.joueurCourant == &leJeu.joueur2){
                        cout << "Malheureusement pour elle, Michelle n'a aucun coup jouable..." << endl;
                        cout << "Passer au tour suivant ? (o/n)" << endl;
                    }else{
                        cout << "Malheureusement vous n'avez aucun coup jouable..." << endl;
                        cout << "Passer au tour suivant ? (o/n)" << endl;
                    }
                    cin >> passer;
                }while(passer != 'o');
            
            toursPasses++;
        }
        // Passage au tour suivant
        changeJoueurCourant(&leJeu);
        if(leJeu.joueur1.nbJeton + leJeu.joueur2.nbJeton == 64 || toursPasses == 2){
            partieTerminee = true;
        }
    }while(!partieTerminee);

    system("clear");

    cout << "PARTIE TERMINÉE !" << endl;
    ajouteJetonPlateau(&leJeu.joueur1, leJeu.plateau);
    ajouteJetonPlateau(&leJeu.joueur2, leJeu.plateau);
    affichePlateau(leJeu.plateau);

    if(leJeu.joueur1.nbJeton  > leJeu.joueur2.nbJeton){
        cout << "Le grand gagnant est " << leJeu.joueur1.nom << " avec " << leJeu.joueur1.nbJeton << " jetons contre " << leJeu.joueur2.nbJeton << " ! Félicitations à lui !" << endl;
    }else{
        if(leJeu.joueur1.nbJeton  < leJeu.joueur2.nbJeton){
            cout << "Le grand gagnant est " << leJeu.joueur2.nom << " avec " << leJeu.joueur2.nbJeton << " jetons contre " << leJeu.joueur1.nbJeton << " ! Félicitations à lui !" << endl;
        }else{
            cout << "C'est une égalité ! Félicitaion à vous deux ! " << endl;
        }
    }

    return 0;
}

bool saisieMenuCorrecte(int saisieUt){
    if(saisieUt != AUTRE_JOUEUR && saisieUt != ORDINATEUR){
        cout << "Erreur: Veuillez saisir un numéro correspondant à l'une des propositions ci-dessus :" << endl;
        return false;
    }else{
        return true;
    }
}

bool saisieCorrecte(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], char saisieUt[2], int coorCase[2]){
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
        if(plateau[coorCase[1]][coorCase[0]]->couleur != 'v' && plateau[coorCase[1]][coorCase[0]]->couleur != 'j'){
            cout << "Erreur: la case saisie est déjà occupée." << endl;
            cout << "Veuillez saisir une nouvelle case :" << endl;
            return false;
        }else{
            return true;
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