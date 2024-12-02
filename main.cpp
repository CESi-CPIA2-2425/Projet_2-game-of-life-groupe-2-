#include <iostream>
#include <string>
#include "Grille.h"
#include "DisplayGraphique.h"
#include <limits>

// Nettoie le buffer d'entrée
void nettoyerBuffer() {
    while (std::cin.get() != '\n'); // Vide tout le contenu restant dans le buffer
}

void modeConsole(const std::string& cheminFichier) {
    Grille grille(0, 0);
    grille.chargerDepuisFichier(cheminFichier);

    std::cout << "Etat initial :\n";
    grille.afficherConsole();

    int iterations = 0;
    std::cout << "\nEntrez le nombre d'iterations a executer : ";
    std::cin >> iterations;

    Grille grillePrecedente = grille; // Copie de la grille pour suivre l'état précédent

    for (int i = 0; i < iterations; ++i) {
        grille.mettreAJour();
        if (grille.estIdentique(grillePrecedente)) { // Vérifie si l'état est stable
            std::cout << "\nGrille stable atteinte apres " << i + 1 << " iterations.\n";
            break;
        }
        grillePrecedente = grille; // Met à jour la grille précédente
        std::cout << "\nIteration " << i + 1 << " :\n";
        grille.afficherConsole();
    }

    grille.sauvegarderDansFichier("resultat_console.txt");
    std::cout << "\nEtat final sauvegarde dans 'resultat_console.txt'.\n";
}

void modeGraphique(const std::string& cheminFichier) {
    Grille grille(0, 0);
    grille.chargerDepuisFichier(cheminFichier);

    int largeur = grille.obtenirCellules()[0].size();
    int hauteur = grille.obtenirCellules().size();
    DisplayGraphique affichage(largeur, hauteur, 20);

    // Demander à l'utilisateur le nombre d'itérations
    int iterations = 0;
    std::cout << "Entrez le nombre d'iterations a executer en mode graphique : ";
    while (!(std::cin >> iterations) || iterations <= 0) {
        std::cin.clear(); // Réinitialise le flux en cas d'entrée invalide
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Vide le buffer
        std::cerr << "Entree invalide. Veuillez entrer un nombre entier positif : ";
    }

    Grille grillePrecedente = grille; // Copie de la grille pour suivre l'état précédent

    // Simulation graphique pour le nombre d'itérations spécifié
    for (int i = 0; i < iterations; ++i) {
        if (!affichage.gererEvenements()) break; // Quitte si la fenêtre est fermée
        grille.mettreAJour();
        if (grille.estIdentique(grillePrecedente)) { // Vérifie si l'état est stable
            std::cout << "\nGrille stable atteinte apres " << i + 1 << " iterations.\n";
            break;
        }
        grillePrecedente = grille; // Met à jour la grille précédente
        affichage.afficher(grille); // Affiche la grille après chaque mise à jour
        sf::sleep(sf::milliseconds(500)); // Pause pour rendre chaque itération visible
    }

    grille.sauvegarderDansFichier("resultat_graphique.txt");
    std::cout << "\nEtat final sauvegarde dans 'resultat_graphique.txt'.\n";
}

int main() {
    std::string cheminFichier;
    std::cout << "Entrez le chemin du fichier contenant la grille initiale : ";
    std::cin >> cheminFichier;
    std::cout << "Chemin du fichier lu : " << cheminFichier << "\n";

    nettoyerBuffer(); // Vide le buffer pour éviter tout conflit

    int mode;
    std::cout << "Choisissez le mode : 1 (console), 2 (graphique) : ";
    while (!(std::cin >> mode) || (mode != 1 && mode != 2)) {
        std::cin.clear();
        nettoyerBuffer(); // Nettoie le buffer
        std::cerr << "Entree invalide. Veuillez entrer 1 (console) ou 2 (graphique) : ";
    }

    if (mode == 1) {
        modeConsole(cheminFichier);
    } else if (mode == 2) {
        modeGraphique(cheminFichier);
    }

    return 0;
}

