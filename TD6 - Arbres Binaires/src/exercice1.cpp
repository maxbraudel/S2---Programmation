// Chemin du fichier: /Users/maxbraudel/Études/IMAC/Progra & Algo/S2 - Programmation/TD6 - Arbres Binaires/src/exercice1.cpp
#include <iostream>
#include <vector>
#include <algorithm>

// Implémentation d'un arbre binaire de recherche avec pointeurs C++
struct Noeud {
    int valeur;
    Noeud* gauche;
    Noeud* droite;
    
    Noeud(int val) : valeur(val), gauche(nullptr), droite(nullptr) {}
    
    // Détermine si un noeud est terminal (sans enfants)
    bool est_feuille() const {
        return (gauche == nullptr && droite == nullptr);
    }
};

// Alloue dynamiquement un nouveau noeud avec la valeur donnée
Noeud* creer_noeud(int valeur) {
    return new Noeud(valeur);
}

// Ajoute récursivement un nouveau noeud dans l'arbre binaire de recherche
void inserer(Noeud* racine, int valeur) {
    if (valeur < racine->valeur) {
        if (racine->gauche == nullptr) {
            racine->gauche = creer_noeud(valeur);
        } else {
            inserer(racine->gauche, valeur);
        }
    } else {
        if (racine->droite == nullptr) {
            racine->droite = creer_noeud(valeur);
        } else {
            inserer(racine->droite, valeur);
        }
    }
}

// Parcourt l'arbre en ordre infixe (gauche-racine-droite) et affiche les valeurs
void afficher_infixe(Noeud* noeud) {
    if (noeud == nullptr) return;
    
    afficher_infixe(noeud->gauche);
    std::cout << noeud->valeur << " ";
    afficher_infixe(noeud->droite);
}

// Calcule récursivement la hauteur de l'arbre (nombre de niveaux)
int hauteur(Noeud* noeud) {
    if (noeud == nullptr) return 0;
    if (noeud->est_feuille()) return 1;
    
    return 1 + std::max(
        noeud->gauche ? hauteur(noeud->gauche) : 0,
        noeud->droite ? hauteur(noeud->droite) : 0
    );
}

// Trouve récursivement la plus petite valeur dans l'arbre (noeud le plus à gauche)
int valeur_min(Noeud* noeud) {
    if (noeud->gauche == nullptr) {
        return noeud->valeur;
    }
    return valeur_min(noeud->gauche);
}

// Trouve récursivement la plus grande valeur dans l'arbre (noeud le plus à droite)
int valeur_max(Noeud* noeud) {
    if (noeud->droite == nullptr) {
        return noeud->valeur;
    }
    return valeur_max(noeud->droite);
}

// Renvoie un pointeur vers le pointeur du noeud le plus à gauche (utilisé pour la suppression)
Noeud** le_plus_a_gauche(Noeud** ptr_noeud) {
    if (*ptr_noeud == nullptr) {
        return ptr_noeud;
    }
    
    if ((*ptr_noeud)->gauche == nullptr) {
        return ptr_noeud;
    }
    
    return le_plus_a_gauche(&((*ptr_noeud)->gauche));
}

// Supprime un noeud avec la valeur donnée de l'arbre. Gère les trois cas de suppression :
// 1. Noeud feuille, 2. Noeud avec un enfant, 3. Noeud avec deux enfants
bool supprimer(Noeud** ptr_noeud, int valeur) {
    Noeud* noeud = *ptr_noeud;
    
    if (noeud == nullptr) {
        return false;
    }
    
    if (valeur < noeud->valeur) {
        return supprimer(&(noeud->gauche), valeur);
    }
    
    if (valeur > noeud->valeur) {
        return supprimer(&(noeud->droite), valeur);
    }
    
    // Cas 1: Noeud terminal sans enfants
    if (noeud->est_feuille()) {
        delete noeud;
        *ptr_noeud = nullptr;
        return true;
    }
    
    // Cas 2: Un seul enfant
    if (noeud->gauche == nullptr) {
        Noeud* temp = noeud;
        *ptr_noeud = noeud->droite;
        delete temp;
        return true;
    }
    
    if (noeud->droite == nullptr) {
        Noeud* temp = noeud;
        *ptr_noeud = noeud->gauche;
        delete temp;
        return true;
    }
    
    // Cas 3: Deux enfants
    Noeud** successeur = le_plus_a_gauche(&(noeud->droite));
    
    noeud->valeur = (*successeur)->valeur;
    
    if ((*successeur)->droite == nullptr) {
        delete *successeur;
        *successeur = nullptr;
    } else {
        Noeud* temp = *successeur;
        *successeur = (*successeur)->droite;
        delete temp;
    }
    
    return true;
}

// Libère récursivement toute la mémoire allouée pour l'arbre
void supprimer_arbre(Noeud* noeud) {
    if (noeud == nullptr) return;
    
    supprimer_arbre(noeud->gauche);
    supprimer_arbre(noeud->droite);
    
    delete noeud;
}

int main() {
    Noeud* racine = creer_noeud(5);

    inserer(racine, 3);
    inserer(racine, 7);
    inserer(racine, 2);
    inserer(racine, 4);
    inserer(racine, 6);
    inserer(racine, 8);
    inserer(racine, 1);
    inserer(racine, 9);
    inserer(racine, 0);
    
    std::cout << "Affichage infixe: ";
    afficher_infixe(racine);
    std::cout << std::endl;
    
    // Afficher les valeurs minimale et maximale
    std::cout << "Valeur minimale: " << valeur_min(racine) << std::endl;
    std::cout << "Valeur maximale: " << valeur_max(racine) << std::endl;
    
    // Calculer la somme des valeurs en utilisant prefix
    std::vector<int> noeuds_prefixe;

    std::function<void(Noeud*, std::vector<int>&)> prefix_valeurs = [&](Noeud* noeud, std::vector<int>& resultat) {
        if (noeud == nullptr) return;
        
        resultat.push_back(noeud->valeur);
        prefix_valeurs(noeud->gauche, resultat);
        prefix_valeurs(noeud->droite, resultat);
    };
    
    prefix_valeurs(racine, noeuds_prefixe);
    
    int somme = 0;
    for (int valeur : noeuds_prefixe) {
        somme += valeur;
    }
    
    std::cout << "Somme des valeurs (en utilisant prefix): " << somme << std::endl;
    
    std::cout << "Hauteur de l'arbre: " << hauteur(racine) << std::endl;
    
    supprimer_arbre(racine);
    
    return 0;
}

