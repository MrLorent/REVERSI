#include <iostream>
#include <fstream>
#include <cstring>
#include "modele.h"
#include "vue.h"
#include "controleur.h"

using namespace std;

/**
 * Sauvegarde les informations principales d'une partie dans un fichier texte
*/
void sauvegardePartie(Jeu leJeu){

    string const nomFichier("./sauvegarde.txt");
    ofstream fichier(nomFichier.c_str());

    if(fichier)    
    {
        fichier << leJeu.mode << endl; //récup mode de jeu
        //récup nom joueur 1, couleur et coordonnees de ses jetons
        fichier << leJeu.joueur1.nom << endl;
        fichier << leJeu.joueur1.couleur << endl;

        Jeton* curseur=leJeu.joueur1.listeJetons;
        while (curseur!=NULL){
			fichier << curseur->coordonnees[0] << endl;
			fichier << curseur->coordonnees[1] << endl;
			curseur=curseur->suivant;
        }
        fichier << "-1" << endl;
        fichier << "-1" << endl;


        //récup nom joueur 2, couleur et coordonnees de ses jetons
        fichier << leJeu.joueur2.nom << endl;
        fichier << leJeu.joueur2.couleur << endl;

        curseur=leJeu.joueur2.listeJetons;
        
		while (curseur!=NULL){
			fichier << curseur->coordonnees[0] << endl;
			fichier << curseur->coordonnees[1] << endl ;
			curseur=curseur->suivant;
        }
        fichier << "-1" << endl;
        fichier << "-1" << endl;

        //récup nom joueur courant
        fichier << leJeu.joueurCourant->nom;
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}


/**
 * Initialise une partie à partir des informations contenues dans le fichier texte "sauvegarde.txt"
*/
void chargementPartie(Jeu *leJeu){
      ifstream fichier("./sauvegarde.txt");
      if(fichier) {
        //L'ouverture s'est bien passée, on peut donc lire

        //On lit le mode de jeu (int) depuis le fichier
        int mode;
        fichier >> mode;
        leJeu->mode = mode;
        // cout << "\nmode recup : " << leJeu->mode << endl ;

        //On lit le nom du joueur 1 (tableau de char) depuis le fichier
        string nom;
        fichier >> nom; 
        char tabChar1[nom.size() + 1]; //on convertit le string récup en tab de char
        strcpy(tabChar1, nom.c_str());
        for (int j = 0 ; j != 20 ; j ++){ //on remplit le nom
            leJeu->joueur1.nom[j] = tabChar1[j];
        }
        // cout << "1e prenom recup : " << leJeu->joueur1.nom << endl ;

        //On lit la couleur du joueur 1 (char) depuis le fichier
        string couleur;
        fichier >> couleur; 
        char c1[couleur.size() + 1];
        strcpy(c1, couleur.c_str());
        leJeu->joueur1.couleur = c1[0];
        // cout << "1e couleur recup : " << leJeu->joueur1.couleur << endl ;

        //On lit les coordonnees du joueur 1 (int) depuis le fichier
        //Jeton *curseur=leJeu->joueur1.listeJetons;
        leJeu->joueur1.nbJeton = 0;
        leJeu->joueur1.listeJetons = NULL;
        int tab_interm[2];
        int coord1, coord2; 
        fichier >> coord1;
        fichier >> coord2;
        do{
            tab_interm[0] = coord1;
            tab_interm[1] = coord2;
            // cout << "1e coordonnees recup " << tab_interm[0] << " " << tab_interm[1] << endl ;
            ajouteJetonJoueur(&(leJeu->joueur1),tab_interm);
            fichier >> coord1;
            fichier >> coord2;
        }
        while (coord1!=(-1) && coord2!=(-1));

        //On lit le nom du joueur 2 (string) depuis le fichier
        string nom2;
        fichier >> nom2; 
        char tabChar2[nom2.size() + 1]; 
        strcpy(tabChar2, nom2.c_str()); //on convertit le string récup en tab de char
        for (int j = 0 ; j != 20 ; j ++){ //on remplit le nom
            leJeu->joueur2.nom[j] = tabChar2[j];
        }
        // cout << "2e prenom recup : " << leJeu->joueur2.nom << endl ;

        //On lit la couleur du joueur 2 (char) depuis le fichier
        string couleur2;
        fichier >> couleur2; 
        char c2[couleur2.size() + 1];
        strcpy(c2, couleur2.c_str());
        leJeu->joueur2.couleur = c2[0];
        // cout << "2e couleur recup : " << leJeu->joueur2.couleur << endl ;

        //On lit les coordonnees du joueur 2 (int) depuis le fichier
        leJeu->joueur2.nbJeton = 0;
        leJeu->joueur2.listeJetons = NULL;
        fichier >> coord1;
        fichier >> coord2;
        do{
            tab_interm[0] = coord1;
            tab_interm[1] = coord2;
            // cout << "2e coordonnees recup " << tab_interm[0] << " " << tab_interm[1] << endl ;
            ajouteJetonJoueur(&(leJeu->joueur2),tab_interm);
            fichier >> coord1;
            fichier >> coord2;
        } 
        while (coord1!=(-1) && coord2!=(-1));

        //On lit le joueur courant (tab de char) depuis le fichier
        string courant;
        fichier >> courant;
        char joueurCourant[courant.size() + 1]; //on convertit le string récup en tab de char
        strcpy(joueurCourant, courant.c_str());
        if(strcmp (joueurCourant,(leJeu->joueur1.nom)) == 0){
            leJeu->joueurCourant = &leJeu->joueur1; // on le compare avec les 2 noms
            leJeu->joueurEnAttente = &leJeu->joueur2;
        }else{
            leJeu->joueurCourant = &leJeu->joueur2;
            leJeu->joueurEnAttente = &leJeu->joueur1;
        }
        // cout << "le joueur courant est " << (leJeu->joueurCourant->nom) << endl ;

        // cout << "La derniere partie a ete chargee. Vous pouvez maintenant la reprendre." << endl;
        remove("sauvegarde.txt");
    }else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
}