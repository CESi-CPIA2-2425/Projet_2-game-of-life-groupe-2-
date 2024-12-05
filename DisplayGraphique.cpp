#include "DisplayGraphique.h"

// Constructeur : crée une fenêtre SFML avec les dimensions spécifiées
DisplayGraphique::DisplayGraphique(int largeur, int hauteur, int tailleCellule)
    : tailleCellule(tailleCellule),
      window(sf::VideoMode(largeur * tailleCellule, hauteur * tailleCellule), "Jeu de la Vie") {}

// Affiche la grille dans la fenêtre graphique
void DisplayGraphique::afficher(const Grille& grille) {
    // Nettoie la fenêtre avec un fond noir
    window.clear(sf::Color::Black);

    // Récupère les cellules de la grille
    const auto& cellules = grille.obtenirCellules();
    for (int y = 0; y < cellules.size(); ++y) {
        for (int x = 0; x < cellules[y].size(); ++x) {
            // Crée un rectangle pour représenter chaque cellule
            sf::RectangleShape rectangle(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));
            rectangle.setPosition(x * tailleCellule, y * tailleCellule); // Position de la cellule

            // Définit la couleur selon l'état de la cellule
            if (cellules[y][x].estVivanteActuellement()) {
                rectangle.setFillColor(sf::Color::White); // Cellule vivante (blanche)
            } else {
                rectangle.setFillColor(sf::Color(100, 100, 100)); // Cellule morte (gris clair)
            }

            // Dessine la cellule
            window.draw(rectangle);
        }
    }

    // Met à jour l'affichage de la fenêtre
    window.display();
}

// Gère les événements utilisateur pour la fenêtre graphique
bool DisplayGraphique::gererEvenements() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close(); // Ferme la fenêtre si l'utilisateur clique sur "fermer"
            return false;
        }
    }
    return true;
}

