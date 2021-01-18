#include <iostream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;


// MODÈLE
void initJeu(Jeu * unJeu){
	int coor1[2]={3,3}, coor2[2]={4,4}, coor3[2]={3,4}, coor4[2]={4,3};

	// Initialisation du premier joueur et de ses deux premiers jetons
	cout << endl;
	cout << "ENREGISTREMENT DU PREMIER JOUEUR :" << endl;
	initJoueur(&unJeu->joueur1, 'b');
	ajouteJetonJoueur(&unJeu->joueur1, coor1);
	ajouteJetonJoueur(&unJeu->joueur1, coor2);

	// Initialisation du second joueur et de ses deux premiers jetons
	cout << endl;
	cout << "ENREGISTREMENT DU SECOND JOUEUR :" << endl;
    initJoueur(&unJeu->joueur2, 'n');
	ajouteJetonJoueur(&unJeu->joueur2, coor3);
	ajouteJetonJoueur(&unJeu->joueur2, coor4);

	// Initialisation du joueur courant
	unJeu->joueurCourant = &unJeu->joueur1;
	unJeu->joueurEnAttente = &unJeu->joueur2;

	// Initialisation de la liste coups jouables à NULL pour le début
	unJeu->coupsJouables = NULL;

	// Initialisation du plateau de jeu
	initPlateau(unJeu->plateau);
}

// CONTROLEURS
void changeJoueurCourant(Jeu * unJeu){
	if(strcmp(unJeu->joueurCourant->nom, (*unJeu).joueur1.nom) == 0 ){
		unJeu->joueurCourant = &unJeu->joueur2;
		unJeu->joueurEnAttente = &unJeu->joueur1;
	}else{
		unJeu->joueurCourant = &unJeu->joueur1;
		unJeu->joueurEnAttente = &unJeu->joueur2;
	}
}

bool analyseCoupsJouables(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], Joueur * joueurCourant, Joueur * adversaire, ListeCoupsJouables * coupsJouables){
    Jeton * tmp = joueurCourant->listeJetons;

    while(tmp != NULL){
        bool leCoupEstJouable = false;
        Jeton * leCoupJouable = NULL;
        ListeJetons * jetonsCapturestmp = new ListeJetons;
        *jetonsCapturestmp = NULL;

        for(int direction=0; direction<8;direction++){
            if(caseExiste(tmp->coordonnees[0]+VECTEURS[direction][0], tmp->coordonnees[1]+VECTEURS[direction][1]) && plateau[tmp->coordonnees[1]+VECTEURS[direction][1]][tmp->coordonnees[0]+VECTEURS[direction][0]]->couleur == adversaire->couleur){
                int count = 0;

                if(directionJouable(plateau, tmp->coordonnees, direction, jetonsCapturestmp, &count, adversaire->couleur, 'v')){
                    leCoupEstJouable = true;
                    leCoupJouable = plateau[tmp->coordonnees[1]+VECTEURS[direction][1]*(count+1)][tmp->coordonnees[0]+VECTEURS[direction][0]*(count+1)];
                    enregistreCoupJouable(coupsJouables, leCoupJouable, jetonsCapturestmp, count);
                    videListeJetons(jetonsCapturestmp);
                }
            }
        }
        if(*jetonsCapturestmp != NULL){
            videListeJetons(jetonsCapturestmp);
            free(jetonsCapturestmp);
        }

        tmp = tmp->suivant;
    }

    if(*coupsJouables != NULL){
        return true;
    }else{
        return false;
    }
    
}

bool directionJouable(Jeton * plateau[MAXLARGEUR][MAXLARGEUR], int caseDepart[2], int uneDirection, ListeJetons * jetonsCaptures, int * count, char couleurAdversaire, char objectif){
    Jeton * caseSuivante;
    int coorCaseSuivante[2];
    
    if(caseExiste(caseDepart[0] + VECTEURS[uneDirection][0], caseDepart[1] + VECTEURS[uneDirection][1])){
        caseSuivante = plateau[caseDepart[1] + VECTEURS[uneDirection][1]][caseDepart[0] + VECTEURS[uneDirection][0]];
        coorCaseSuivante[0] = caseDepart[0] + VECTEURS[uneDirection][0];
        coorCaseSuivante[1] = caseDepart[1] + VECTEURS[uneDirection][1];

        if(caseSuivante->couleur == couleurAdversaire){
            ajouteJetonCapture(jetonsCaptures, caseSuivante->coordonnees);
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

void enregistreCoupJouable(ListeCoupsJouables * liste, Marqueur * emplacement, ListeJetons * jetonsCaptures, int nbCaptures){
	int rang = estEnregistre(liste, emplacement->coordonnees);

	if(rang >= 0){
		CoupJouable * coupJouabletmp = *liste;

		for(int i=0; i<rang-1; i++){
            coupJouabletmp = coupJouabletmp->suivant;
        }

		coupJouabletmp->nbCaptures = coupJouabletmp->nbCaptures + nbCaptures;
		
		ajouteJetonsCaptures(&coupJouabletmp->jetonsCaptures, jetonsCaptures);

	}else{
		CoupJouable * nouveauCoup = new CoupJouable;
		nouveauCoup->emplacement = emplacement;
		
		ajouteJetonsCaptures(&(nouveauCoup->jetonsCaptures), jetonsCaptures);

		nouveauCoup->nbCaptures = nbCaptures;
			
		if(liste != NULL){
			nouveauCoup->suivant = *liste;
		}else{
			nouveauCoup->suivant = NULL;
		}
		*liste = nouveauCoup;
	}
}

int estEnregistre(ListeCoupsJouables * coupsJouables, int coorEmplacement[2]){
	int rang = 0;
	bool present = false;
	CoupJouable * tmp = *coupsJouables;

	while(tmp != NULL && !present){
		if((tmp)->emplacement->coordonnees[0] == coorEmplacement[0] && (tmp)->emplacement->coordonnees[1] == coorEmplacement[1]){
			present = true;
		}
		rang++;
		tmp = tmp->suivant;
	}
	if(present){
		return rang;
	}else{
		return -1;
	}
}

bool coupJouable(ListeCoupsJouables * coupsJouables, int caseSouhaitee[2], Joueur * joueurCourant, Joueur * adversaire){
    int rang = estEnregistre(coupsJouables, caseSouhaitee);
    bool coupValide = false;
    
    if(rang >= 0){
        CoupJouable * tmp1 = *coupsJouables; 

        coupValide = true;

        for(int i=0; i<rang-1; i++){
            tmp1 = tmp1->suivant;
        }

        Jeton * tmp2 = tmp1->jetonsCaptures;
        while(tmp2 != NULL){
                ajouteJetonJoueur(joueurCourant, tmp2->coordonnees);
                supprimeJetonJoueur(adversaire, tmp2->coordonnees);
            tmp2 = tmp2->suivant;
        }
        
    }else{
        cout << "Erreur: vous devez au moins capturer un jeton adverse." << endl;
        cout << "Veuillez saisir une nouvelle case :" << endl;
    }

    return coupValide;
}

void videListeCoupsJouables(ListeCoupsJouables * uneListe){
	CoupJouable * tmp = *uneListe;

	while(tmp != NULL){
		*uneListe = (*uneListe)->suivant;
		videListeJetons(&tmp->jetonsCaptures);
		free(tmp);
		tmp = *uneListe;
	}
}