#include <iostream>
#include <fstream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;

int main(){
    Jeu leJeu;
    int toursPasses = 0, actionSaisie = 0;
    int coorSaisie[2];
    char saisieUt[2];
    bool partieTerminee, partieQuittee, premierPassage, quitter = false;


    system("clear");
    cout << CYAN << "BIENVENUE DANS NOTRE JEU DE REVERSI !" << ANNULE_COULEUR << endl;
    cout << endl;
    cout << endl;
    do{
        cout << MAGENTA << "MENU PRINCIPAL" << ANNULE_COULEUR << endl;
        cout << endl;
        cout << "1 - Lancer une partie contre un autre joueur." << endl;
        cout << "2 - Lancer une partie conte Michelle (Ordinateur)." << endl;
        cout << "3 - Charger la dernière partie en cours." << endl;
        cout << "4 - Quitter." << endl;
        cout << endl;
        cout << "Veuillez saisir le numéro de l'action que vous souhaitez réaliser :" << endl;
        do{
            cin >> actionSaisie;
        }while(!saisieMenuCorrecte(actionSaisie));

        system("clear");

        switch (actionSaisie)
        {
        case CHARGEMENT:
            initPlateau(leJeu.plateau);
            chargementPartie(&leJeu);
            break;

        case QUITTER:
            quitter = true;
            break;

        default:
            leJeu.mode = actionSaisie;
            initJeu(&leJeu);
            break;
        }

        if(!quitter){
            // INITIALISATION DES VARIABLES GLOBALES D'UNE PARTIE
            partieQuittee = false;
            partieTerminee = false;

            do{
                // INITIALISATION DES VARIABLES GLOBALES D'UN TOUR DE JEU
                premierPassage = true;

                // DÉBUT DU TOUR
                // Affichage des informations sur le joueur courant
                system("clear");
                cout << endl;
                cout << CYAN << "NOUVEAU TOUR DE JEU:" << ANNULE_COULEUR << endl;
                cout << "Joueur courant: " << leJeu.joueurCourant->nom << endl;
                cout << "Nombre de jeton(s) du joueur courant: " << leJeu.joueurCourant->nbJeton << endl;

                // Mise à jour des données du plateau
                ajouteJetonPlateau(&leJeu.joueur1, leJeu.plateau);
                ajouteJetonPlateau(&leJeu.joueur2, leJeu.plateau);

                if(leJeu.mode == ORDINATEUR && leJeu.joueurCourant == &leJeu.joueur2){
                    // Si l'on joue face à l'ordinateur, on affiche une première fois  le plateau pour que le joueur voit le résultat de son tour précédent
                    cout << endl;
                    cout << "Voici le plateau suite à votre précédent tour :" << endl;
                    affichePlateau(leJeu.plateau);
                }else{
                    // SI c'est à un utilisateur de jouer, on le guide quelque peut:
                    if(leJeu.joueurCourant == &leJeu.joueur1){
                        cout << "Vous êtes les X et vous devez capturer les O." << endl;
                    }else{
                        cout << "Vous êtes les O et vous devez capturer les X." << endl;
                    }
                    cout << "(les cases * correspondent aux cases valides que vous pouvez entrer.)" << endl;
                }

                // DÉROULÉ DU TOUR
                //On vérifie si le joueur courant peut jouer
                if(analyseCoupsJouables(leJeu.plateau, leJeu.joueurCourant, leJeu.joueurEnAttente, &leJeu.coupsJouables)){
                    // Si le joueur courant peut jouer: 
                    
                    // On ajoute les coups jouables au plateau
                    ajouteCoupsJouablesPlateau(leJeu.plateau, &leJeu.coupsJouables);
                    
                    if(leJeu.mode == ORDINATEUR && leJeu.joueurCourant == &leJeu.joueur2){
                        // Si l'on est dans le cas d'une partie face à l'ordinateur et que c'est son tour de jouer:

                        // On fait jouer l'ordinateur et on récupère le nombre de jetons qu'il a capturé
                        int nbCaptures = ordinateurJoue(&leJeu);

                        // Affichage du plateau
                        ajouteJetonPlateau(&leJeu.joueur1, leJeu.plateau);
                        ajouteJetonPlateau(&leJeu.joueur2, leJeu.plateau);
                        cout << "Voici le plateau suite au tour de Michelle :" << endl;
                        affichePlateau(leJeu.plateau);

                        // FIN DU TOUR
                        do{
                            if(premierPassage){
                                cout << "Elle vous a capturé " << nbCaptures << " jetons." << endl;
                                premierPassage = false;
                            }else{
                                cout << "Votre énervement ne changera rien... Il faut tourner la page maintenant." << endl;
                            }
                            cout << "Quitter la partie = 'q'" << endl;
                            cout << "Passer à la suite = 'o'" << endl;
                            cin >> saisieUt;
                            if(tolower(saisieUt[0]) == 'q'){
                                partieQuittee = quitterPartie(&leJeu);
                            }
                        }while(!partieQuittee && tolower(saisieUt[0]) != 'o');

                    }else{
                        // Affichage du plateau
                        affichePlateau(leJeu.plateau);

                        cout << "Quitter la partie = 'q'" << endl;
                        cout << "Quelle case souhaitez-vous prendre " << leJeu.joueurCourant->nom << " ?" << endl;
                        do{
                            cin >> saisieUt;
                            if(tolower(saisieUt[0]) == 'q'){
                                partieQuittee = quitterPartie(&leJeu);
                            }
                        }while(!partieQuittee && (!saisieCorrecte(leJeu.plateau, saisieUt, coorSaisie) || !coupJouable(&leJeu.coupsJouables, coorSaisie)));

                        //Si le joueur n'a pas décidé de quitter la partie, on joue le coup
                        if(!partieQuittee){
                            joueLeCoup(leJeu.plateau, coorSaisie, leJeu.joueurCourant, leJeu.joueurEnAttente);
                        }
                    }

                    // FIN DU TOUR
                    toursPasses = 0;
                    retireCoupsJouablesPlateau(leJeu.plateau, &leJeu.coupsJouables);
                }else{
                    // Si le joueur courant ne peut pas jouer:

                    // Affichage du plateau
                    affichePlateau(leJeu.plateau);

                        do{
                            if(leJeu.mode == ORDINATEUR && leJeu.joueurCourant == &leJeu.joueur2){
                                // Dans le cas d'une partie face à l'ordinateur
                                if(premierPassage){
                                    cout << "Malheureusement pour elle, Michelle n'a aucun coup jouable." << endl;
                                    premierPassage = false;
                                }else{
                                    cout << "Savourez cette petite victiore... mais pas trop longtemps non plus !" << endl;
                                }
                                cout << "Quitter la partie = 'q'" << endl;
                                cout << "Passer à la suite = 'o'" << endl;
                            }else{
                                // Dans le cas d'un joueur classique
                                if(premierPassage){
                                    cout << "Malheureusement, vous n'avez aucun coup jouable..." << endl;
                                    premierPassage = false;
                                }else{
                                    cout << "Votre énervement ne changera rien... Il faut tourner la page maintenant." << endl;
                                }
                                cout << "Quitter la partie = 'q'" << endl;
                                cout << "Passer à la suite = 'o'" << endl;
                                }
                            cin >> saisieUt;
                            if(tolower(saisieUt[0]) == 'q'){
                                partieQuittee = quitterPartie(&leJeu);
                            }
                        }while(!partieQuittee && tolower(saisieUt[0]) != 'o');
                    
                    toursPasses++;
                }
                // Passage au tour suivant
                changeJoueurCourant(&leJeu);

                // Si le plateau est remplit, ou si aucun des joueurs ne peut jouer, on met fin à la partie
                if(leJeu.joueur1.nbJeton + leJeu.joueur2.nbJeton == 64 || toursPasses == 2){
                    partieTerminee = true;
                }

            }while(!partieTerminee && !partieQuittee);

            if(!partieQuittee){
                system("clear");

                cout << CYAN << "PARTIE TERMINÉE !" << ANNULE_COULEUR << endl;

                // On affiche le plateau final
                ajouteJetonPlateau(&leJeu.joueur1, leJeu.plateau);
                ajouteJetonPlateau(&leJeu.joueur2, leJeu.plateau);
                affichePlateau(leJeu.plateau);

                // On affiche le gagnant et son nombre de jetons final
                if(leJeu.joueur1.nbJeton  > leJeu.joueur2.nbJeton){
                    cout << "Le grand gagnant est " << leJeu.joueur1.nom << " avec " << leJeu.joueur1.nbJeton << " jetons contre " << leJeu.joueur2.nbJeton << " pour " << leJeu.joueur2.nom << " ! Félicitations à lui !" << endl;
                }else{
                    if(leJeu.joueur1.nbJeton  < leJeu.joueur2.nbJeton){
                        cout << "Le grand gagnant est " << leJeu.joueur2.nom << " avec " << leJeu.joueur2.nbJeton << " jetons contre " << leJeu.joueur1.nbJeton << " pour " << leJeu.joueur1.nom << " ! Félicitations à lui !" << endl;
                    }else{
                        cout << "C'est une égalité ! Félicitations à vous deux ! " << endl;
                    }
                }
                do{
                    cout << "retour au menu principal ? (o/n)" << endl;
                    cin >> saisieUt;
                }while(tolower(saisieUt[0]) != 'o');
            }

            system("clear");
        
        }else{
            // Si le joueur décide de quitter le programme
            cout << "À bientôt !" << endl;
        }
    }while(!quitter);

    return 0;
}

bool saisieMenuCorrecte(int saisieUt){
    // On vérifie que la saisie correspond bien à un des cas possibles
    if(saisieUt != HUMAIN && saisieUt != ORDINATEUR && saisieUt != CHARGEMENT && saisieUt != QUITTER){
        cout << "Erreur: Veuillez saisir un numéro correspondant à l'une des propositions ci-dessus :" << endl;
        return false;
    }else{
        // L'utilisateur choisi de chargé une partie, on vérifie qu'une sauvegarde existe bien
        if(saisieUt == CHARGEMENT){
            ifstream fichier("./sauvegarde.txt");
            if(fichier){
                return true;
            }else{
                cout << "Erreur: aucune partie en cours n'a été trouvée." << endl;
                cout << "Veuillez saisir une autre action à réaliser :" << endl;
                return false;
            }
        }else{
            return true;
        }
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
    // On converit les coordonnées de char à int en prenant en compte le décalage en -1 des tableaux
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

bool quitterPartie(Jeu * leJeu){
    char saisieUt = 'a';

    system("clear");
    do{
        cout << "Souhaitez-vous réellement quitter la partie ? (o/n)" << endl;
        cin >> saisieUt;
    }while(tolower(saisieUt) != 'o' && tolower(saisieUt) != 'n');

    if(saisieUt == 'o'){
        // Si l'utilisateur quitte la partie, on sauvegarde la partie en cours:

        // Dans le cas où la partie est quitté alors que le joueur courant est l'ordinateur, on change de joueur afin que l'ordinateur ne rejoue pas une seconde fois au chargement de la partie
        if(leJeu->mode == ORDINATEUR && leJeu->joueurCourant->nom == leJeu->joueur2.nom){
            changeJoueurCourant(leJeu);
        }
        // On sauvegarde la partie en cours
        sauvegardePartie(*leJeu);
        return true;
    }else{
        return false;
    }
}