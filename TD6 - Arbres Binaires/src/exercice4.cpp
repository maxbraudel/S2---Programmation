// Chemin du fichier: /Users/maxbraudel/Études/IMAC/Progra & Algo/S2 - Programmation/TD6 - Arbres Binaires/src/exercice4.cpp
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

namespace BinaryTreeImpl {

// Structure de noeud avec implémentation interne encapsulée dans un namespace
struct Node {
    int value;
    std::unique_ptr<Node> left{nullptr};
    std::unique_ptr<Node> right{nullptr};
    
    // Détermine si un noeud est terminal (sans enfants)
    bool is_leaf() const {
        return !left && !right;
    }
    
    // Ajoute récursivement une valeur à l'arbre en respectant les propriétés d'un ABR
    void insert(int value) {
        if (value < this->value) {
            if (!left) {
                left = std::make_unique<Node>(Node{value});
            } else {
                left->insert(value);
            }
        } else {
            if (!right) {
                right = std::make_unique<Node>(Node{value});
            } else {
                right->insert(value);
            }
        }
    }
    
    // Parcourt l'arbre en ordre infixe (gauche-racine-droite) pour afficher les valeurs triées
    void display_infix() const {
        if (left) {
            left->display_infix();
        }
        
        std::cout << value << " ";
        
        if (right) {
            right->display_infix();
        }
    }
    
    // Calcule récursivement la hauteur de l'arbre (nombre maximal de niveaux)
    size_t height() const {
        if (is_leaf()) {
            return 1;
        }
        
        size_t left_height = 0;
        size_t right_height = 0;
        
        if (left) {
            left_height = left->height();
        }
        
        if (right) {
            right_height = right->height();
        }
        
        return 1 + std::max(left_height, right_height);
    }
    
    // Récupère la plus petite valeur stockée dans l'arbre (noeud le plus à gauche)
    int min() const {
        if (!left) {
            return value;
        }
        return left->min();
    }
    
    // Récupère la plus grande valeur stockée dans l'arbre (noeud le plus à droite)
    int max() const {
        if (!right) {
            return value;
        }
        return right->max();
    }
    
    // Effectue un parcours préfixe (racine-gauche-droite) et renvoie les valeurs dans cet ordre
    std::vector<int> prefix() const {
        std::vector<int> result;
        
        // Visiter d'abord la racine
        result.push_back(value);
        
        // Puis visiter récursivement le sous-arbre gauche
        if (left) {
            std::vector<int> left_values = left->prefix();
            result.insert(result.end(), left_values.begin(), left_values.end());
        }
        
        // Enfin visiter récursivement le sous-arbre droit
        if (right) {
            std::vector<int> right_values = right->prefix();
            result.insert(result.end(), right_values.begin(), right_values.end());
        }
        
        return result;
    }
    
    // Effectue un parcours postfixe (gauche-droite-racine) et renvoie les valeurs dans cet ordre
    std::vector<int> postfix() const {
        std::vector<int> result;
        
        // Visiter d'abord récursivement le sous-arbre gauche
        if (left) {
            std::vector<int> left_values = left->postfix();
            result.insert(result.end(), left_values.begin(), left_values.end());
        }
        
        // Puis visiter récursivement le sous-arbre droit
        if (right) {
            std::vector<int> right_values = right->postfix();
            result.insert(result.end(), right_values.begin(), right_values.end());
        }
        
        // Visiter la racine en dernier
        result.push_back(value);
        
        return result;
    }
};

// Renvoie une référence vers le noeud le plus à gauche (utilisé pour la suppression)
std::unique_ptr<Node>& most_left(std::unique_ptr<Node>& node) {
    if (!node) {
        return node;
    }
    
    if (!node->left) {
        return node;
    }
    
    return most_left(node->left);
}

// Supprime un noeud contenant la valeur spécifiée en maintenant les propriétés de l'ABR
// Gère les trois cas de suppression: noeud terminal, noeud avec un enfant, noeud avec deux enfants
bool remove(std::unique_ptr<Node>& node, int value) {
    if (!node) {
        return false;
    }
    
    if (value < node->value) {
        return remove(node->left, value);
    }
    
    if (value > node->value) {
        return remove(node->right, value);
    }
    
    // Cas 1: Noeud terminal sans enfants
    if (node->is_leaf()) {
        node.reset();
        return true;
    }
    
    // Cas 2: Noeud avec un seul enfant
    if (!node->left) {
        node = std::move(node->right);
        return true;
    }
    
    if (!node->right) {
        node = std::move(node->left);
        return true;
    }
    
    // Cas 3: Noeud avec deux enfants
    std::unique_ptr<Node>& successor = most_left(node->right);
    
    node->value = successor->value;
    
    if (!successor->right) {
        successor.reset();
    } else {
        successor = std::move(successor->right);
    }
    
    return true;
}

// Recherche récursivement une valeur dans l'arbre binaire
bool contains(const std::unique_ptr<Node>& node, int value) {
    if (!node) {
        return false;
    }
    
    if (node->value == value) {
        return true;
    }
    
    if (value < node->value) {
        return contains(node->left, value);
    } else {
        return contains(node->right, value);
    }
}

// Calcule récursivement la somme de toutes les valeurs dans l'arbre
int sum_values(const std::unique_ptr<Node>& node) {
    if (!node) {
        return 0;
    }
    
    return node->value + sum_values(node->left) + sum_values(node->right);
}

} // fin du namespace BinaryTreeImpl

// Interface publique de l'arbre binaire de recherche
// Utilise le pattern PIMPL (Pointer to IMPLementation) pour cacher les détails d'implémentation
class BinaryTree {
private:
    // Stockage de l'implémentation interne, invisible aux utilisateurs de la classe
    std::unique_ptr<BinaryTreeImpl::Node> root{nullptr};
    
public:
    // Constructeur par défaut
    BinaryTree() = default;
    
    // Constructeur avec valeur initiale
    explicit BinaryTree(int value) {
        root = std::make_unique<BinaryTreeImpl::Node>(BinaryTreeImpl::Node{value});
    }
    
    // Ajoute une nouvelle valeur à l'arbre
    void insert(int value) {
        if (!root) {
            root = std::make_unique<BinaryTreeImpl::Node>(BinaryTreeImpl::Node{value});
        } else {
            root->insert(value);
        }
    }
    
    // Supprime un noeud contenant la valeur spécifiée
    bool remove(int value) {
        return BinaryTreeImpl::remove(root, value);
    }
    
    // Libère toute la mémoire et réinitialise l'arbre
    void clear() {
        root.reset();
    }
    
    // Vérifie si l'arbre contient une valeur donnée
    bool contains(int value) const {
        return BinaryTreeImpl::contains(root, value);
    }
    
    // Calcule la hauteur de l'arbre (nombre de niveaux)
    size_t height() const {
        if (!root) {
            return 0;
        }
        return root->height();
    }
    
    // Affiche toutes les valeurs de l'arbre en ordre croissant (parcours infixe)
    void display_infix() const {
        if (root) {
            root->display_infix();
        }
        std::cout << std::endl;
    }
    
    // Récupère la plus petite valeur stockée dans l'arbre
    int min() const {
        if (!root) {
            throw std::runtime_error("Arbre vide");
        }
        return root->min();
    }
    
    // Récupère la plus grande valeur stockée dans l'arbre
    int max() const {
        if (!root) {
            throw std::runtime_error("Arbre vide");
        }
        return root->max();
    }
    
    // Renvoie les valeurs dans l'ordre préfixe (racine-gauche-droite)
    std::vector<int> prefix() const {
        if (!root) {
            return {};
        }
        return root->prefix();
    }
    
    // Renvoie les valeurs dans l'ordre postfixe (gauche-droite-racine)
    std::vector<int> postfix() const {
        if (!root) {
            return {};
        }
        return root->postfix();
    }
    
    // Calcule la somme de toutes les valeurs dans l'arbre
    int sum() const {
        return BinaryTreeImpl::sum_values(root);
    }
};

int main() {
    BinaryTree tree;
    
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.insert(1);
    tree.insert(9);
    tree.insert(0);
    
    std::cout << "Affichage infixe: ";
    tree.display_infix();
    
    std::cout << "Valeur minimale: " << tree.min() << std::endl;
    std::cout << "Valeur maximale: " << tree.max() << std::endl;

    std::cout << "Somme des valeurs: " << tree.sum() << std::endl;

    std::cout << "Hauteur de l'arbre: " << tree.height() << std::endl;
    
    std::vector<int> prefix_values = tree.prefix();
    std::cout << "Parcours préfixe: ";
    for (int val : prefix_values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::vector<int> postfix_values = tree.postfix();
    std::cout << "Parcours postfixe: ";
    for (int val : postfix_values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::cout << "L'arbre contient 6: " << (tree.contains(6) ? "oui" : "non") << std::endl;
    std::cout << "L'arbre contient 42: " << (tree.contains(42) ? "oui" : "non") << std::endl;
    

    std::cout << "Suppression de la valeur 3: " << (tree.remove(3) ? "réussi" : "échec") << std::endl;
    
    // Afficher l'arbre après suppression
    std::cout << "Affichage après suppression: ";
    tree.display_infix();
    
    return 0;
}