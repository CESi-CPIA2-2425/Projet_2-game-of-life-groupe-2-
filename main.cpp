#include <iostream>
#include <string>
#include "Grille.h"
#include "DisplayGraphique.h"
#include <limits>

// Nettoie le buffer d'entrée
void nettoyerBuffer() {
    while (std::cin.get() != '\n'); // Vide tout le contenu restant dans le buffer
}
