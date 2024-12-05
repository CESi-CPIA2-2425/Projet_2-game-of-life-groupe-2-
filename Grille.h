#ifndef GRILLE_H
#define GRILLE_H

#include <vector>
#include <iostream>
#include "Cellule.h"

// Classe représentant la grille du Jeu de la Vie
class Grille {
private:
    std::vector<std::vector<Cellule>> cellules; // Grille 2D de cellules
    int largeur, hauteur;                      // Dimensions de la grille

public:
    // Constructeur qui initialise une grille vide avec les dimensions données
    Grille(int largeur, int hauteur);

    // Charge l'état initial de la grille depuis un fichier
    void chargerDepuisFichier(const std::string& cheminFichier);

    // Sauvegarde l'état actuel de la grille dans un fichier
    void sauvegarderDansFichier(const std::string& cheminFichier);

    // Affiche la grille dans la console
    void afficherConsole();

    // Met à jour l'état de toutes les cellules dans la grille
    void mettreAJour();

    // Compte le nombre de voisins vivants d'une cellule donnée
    int compterVoisinsVivants(int x, int y) const;

    // Compare si deux grilles sont identiques
    bool estIdentique(const Grille& autre) const;

    // Accesseurs pour la grille
    const std::vector<std::vector<Cellule>>& obtenirCellules() const { return cellules; }
    std::vector<std::vector<Cellule>>& obtenirCellules() { return cellules; }
};

#endif // GRILLE_H

