#include <gtest/gtest.h>
#include <fstream>  
#include "Cellule.h"
#include "Grille.h"

// Test : État par défaut d'une Cellule
TEST(CelluleTest, EtatInitial) {
    Cellule cellule;
    EXPECT_FALSE(cellule.estVivanteActuellement());  // Une cellule doit être morte par défaut
}

// Test : Définir et mettre à jour l'état d'une Cellule
TEST(CelluleTest, SetAndUpdateState) {
    Cellule cellule;
    cellule.definirEtat(true);  // Définit la cellule comme vivante
    EXPECT_TRUE(cellule.estVivanteActuellement());  // Vérifie qu'elle est vivante

    cellule.calculerProchainEtat(1);  // Avec 1 voisin, elle devrait mourir
    cellule.mettreAJourEtat();
    EXPECT_FALSE(cellule.estVivanteActuellement());
}

// Test : Charger une Grille depuis un fichier
TEST(GrilleTest, ChargerDepuisFichier) {
    Grille grille(0, 0);

    // Crée un fichier de test à charger
    std::ofstream fichier("test_grille.txt");
    if (fichier.is_open()) {
        fichier << "3 3\n"
                << "0 1 0\n"
                << "1 1 1\n"
                << "0 1 0\n";
        fichier.close();
    } else {
        FAIL() << "Impossible de créer le fichier de test.";
    }

    // Teste le chargement du fichier
    ASSERT_NO_THROW(grille.chargerDepuisFichier("test_grille.txt"));
    EXPECT_EQ(grille.obtenirCellules().size(), 3);  // Hauteur
    EXPECT_EQ(grille.obtenirCellules()[0].size(), 3);  // Largeur
    EXPECT_TRUE(grille.obtenirCellules()[1][1].estVivanteActuellement());  // Cellule centrale
}

// Test : Mise à jour correcte de la Grille
TEST(GrilleTest, MiseAJour) {
    Grille grille(3, 3);

    // Récupère une référence modifiable des cellules
    auto& cellules = grille.obtenirCellules();

    // Configure manuellement un état initial pour la grille
    cellules[0][1].definirEtat(true);
    cellules[1][0].definirEtat(true);
    cellules[1][1].definirEtat(true);
    cellules[1][2].definirEtat(true);
    cellules[2][1].definirEtat(true);

    // Met à jour la grille
    grille.mettreAJour();

    // Vérifie l'état après mise à jour
    EXPECT_TRUE(cellules[0][1].estVivanteActuellement());
    EXPECT_TRUE(cellules[1][0].estVivanteActuellement());
    EXPECT_TRUE(cellules[1][2].estVivanteActuellement());
    EXPECT_TRUE(cellules[2][1].estVivanteActuellement());
    EXPECT_FALSE(cellules[1][1].estVivanteActuellement());
}
