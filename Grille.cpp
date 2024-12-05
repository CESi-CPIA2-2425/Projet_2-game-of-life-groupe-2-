#include "Grille.h"
#include <fstream>

// Constructeur : initialise une grille vide avec les dimensions données
Grille::Grille(int largeur, int hauteur) : largeur(largeur), hauteur(hauteur) {
    cellules.resize(hauteur, std::vector<Cellule>(largeur)); // Crée une grille 2D de cellules
}

// Charge l'état initial de la grille depuis un fichier
void Grille::chargerDepuisFichier(const std::string& cheminFichier) {
    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open()) throw std::runtime_error("Impossible d'ouvrir le fichier");

    fichier >> hauteur >> largeur; // Lit les dimensions de la grille
    cellules.resize(hauteur, std::vector<Cellule>(largeur)); // Redimensionne la grille

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            int etat;
            fichier >> etat; // Lit 1 (vivante) ou 0 (morte)
            cellules[y][x].definirEtat(etat == 1);
        }
    }
}

// Sauvegarde l'état actuel de la grille dans un fichier
void Grille::sauvegarderDansFichier(const std::string& cheminFichier) {
    std::ofstream fichier(cheminFichier);
    fichier << hauteur << " " << largeur << "\n"; // Écrit les dimensions de la grille
    for (const auto& ligne : cellules) {
        for (const auto& cellule : ligne) {
            fichier << (cellule.estVivanteActuellement() ? 1 : 0) << " "; // Écrit 1 ou 0
        }
        fichier << "\n";
    }
}

// Affiche l'état actuel de la grille dans la console
void Grille::afficherConsole() {
    for (const auto& ligne : cellules) {
        for (const auto& cellule : ligne) {
            std::cout << (cellule.estVivanteActuellement() ? "1 " : "0 ");
        }
        std::cout << "\n";
    }
}

// Met à jour l'état de toutes les cellules dans la grille
void Grille::mettreAJour() {
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            cellules[y][x].calculerProchainEtat(compterVoisinsVivants(x, y));
        }
    }
    for (auto& ligne : cellules) {
        for (auto& cellule : ligne) {
            cellule.mettreAJourEtat();
        }
    }
}

// Compte le nombre de voisins vivants autour d'une cellule donnée
int Grille::compterVoisinsVivants(int x, int y) const {
    int compte = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue; // Ignore la cellule elle-même
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < largeur && ny >= 0 && ny < hauteur) {
                if (cellules[ny][nx].estVivanteActuellement()) ++compte;
            }
        }
    }
    return compte;
}

// Compare si deux grilles sont identiques
bool Grille::estIdentique(const Grille& autre) const {
    if (hauteur != autre.hauteur || largeur != autre.largeur) return false;

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (cellules[y][x].estVivanteActuellement() != autre.cellules[y][x].estVivanteActuellement()) {
                return false;
            }
        }
    }
    return true;
}

