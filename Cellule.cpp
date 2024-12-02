#include "Cellule.h"

// Calcule le prochain état de la cellule en fonction des règles du Jeu de la Vie
void Cellule::calculerProchainEtat(int voisinsVivants) {
    if (estVivante) {
        // Une cellule vivante reste vivante si elle a 2 ou 3 voisins vivants
        prochainEtat = (voisinsVivants == 2 || voisinsVivants == 3);
    } else {
        // Une cellule morte devient vivante si elle a exactement 3 voisins vivants
        prochainEtat = (voisinsVivants == 3);
    }
}
