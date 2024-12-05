#ifndef CELLULE_H
#define CELLULE_H

// Classe représentant une cellule individuelle dans la grille
class Cellule {
private:
    bool estVivante;     // État actuel de la cellule (vivante ou morte)
    bool prochainEtat;   // État que prendra la cellule à la prochaine itération

public:
    // Constructeur par défaut : initialise la cellule comme morte
    Cellule() : estVivante(false), prochainEtat(false) {}

    // Retourne si la cellule est actuellement vivante
    bool estVivanteActuellement() const { return estVivante; }

    // Définit l'état actuel de la cellule (vivante ou morte)
    void definirEtat(bool etat) { estVivante = etat; }

    // Calcule le prochain état de la cellule en fonction des règles du Jeu de la Vie
    void calculerProchainEtat(int voisinsVivants);

    // Met à jour l'état actuel en passant au prochain état
    void mettreAJourEtat() { estVivante = prochainEtat; }
};

#endif // CELLULE_H

