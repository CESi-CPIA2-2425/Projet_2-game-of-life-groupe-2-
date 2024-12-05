#ifndef DISPLAYGRAPHIQUE_H
#define DISPLAYGRAPHIQUE_H

#include <SFML/Graphics.hpp>
#include "Grille.h"

// Classe responsable de l'affichage graphique de la grille
class DisplayGraphique {
private:
    sf::RenderWindow window;       // Fenêtre SFML pour afficher la grille
    int tailleCellule;             // Taille d'une cellule en pixels

public:
    // Constructeur : initialise la fenêtre avec la largeur, la hauteur, et la taille des cellules
    DisplayGraphique(int largeur, int hauteur, int tailleCellule);

    // Affiche l'état actuel de la grille
    void afficher(const Grille& grille);

    // Gère les événements de la fenêtre (par exemple, fermer la fenêtre)
    bool gererEvenements();
};

#endif // DISPLAYGRAPHIQUE_H

