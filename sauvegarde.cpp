#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{

    string const nomFichier("C:/Users/fline/Desktop/Sauvegarde.txt");
    ofstream monFlux(nomFichier.c_str());

    if(monFlux)    
    {
        monFlux << "Derniere partie sauvegardee" << endl;
        monFlux << Jeu.mode << endl; //récup mode de jeu
        //récup nom joueur 1, couleur et coordonnees de ses jetons
        monFlux << Jeu.joueur1.nom << endl;
        monFlux << Jeu.joueur1.couleur << endl;
        Jeton* curseur=Jeu.joueur1->ListeJetons;
        while (curseur!=NULL){
        monFlux << curseur->jeton.coordonnées[1] << curseur->jeton.coordonnées[2] << "\n" ;
        curseur=curseur->suivant;
        }
        //récup nom joueur 2, couleur et coordonnees de ses jetons
        monFlux << Jeu.joueur2.nom << endl;
        monFlux << Jeu.joueur2.couleur << endl;
        curseur=Jeu.joueur2->ListeJetons;
        while (curseur!=NULL){
        monFlux << curseur->jeton.coordonnées[1] << curseur->jeton.coordonnées[2] << "\n" ;
        curseur=curseur->suivant;
        }
        
        if(Jeu.mode==...) monFlux << Jeu.joueur2 << endl;
        monFlux << Jeu.plateau << endl;
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
    return 0;
}

 ifstream fichier("C:/Users/fline/Desktop/Sauvegarde.txt");

   if(fichier)
   {
      //L'ouverture s'est bien passée, on peut donc lire
      string ligne; //Une variable pour stocker les lignes lues
      while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
      {
         chargementMode = ligne << endl;
         //Et on l'affiche dans la console
         //Ou alors on fait quelque chose avec cette ligne
         //À vous de voir
      }
   }
   else
   {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
   }

   return 0;
}