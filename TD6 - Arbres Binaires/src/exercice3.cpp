// Chemin du fichier: /Users/maxbraudel/Études/IMAC/Progra & Algo/S2 - Programmation/TD6 - Arbres Binaires/src/exercice3.cpp
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

// Définition d'un noeud d'arbre binaire utilisant les pointeurs intelligents (unique_ptr)
struct SmartNode;

// Prototypes des fonctions - déclarations anticipées pour les dépendances circulaires
std::unique_ptr<SmartNode> create_smart_node(int value);
std::unique_ptr<SmartNode>& most_left(std::unique_ptr<SmartNode>& node);
bool remove(std::unique_ptr<SmartNode>& node, int value);
bool contains(const std::unique_ptr<SmartNode>& node, int value);

// Structure qui représente un noeud dans l'arbre binaire avec gestion automatique de la mémoire
struct SmartNode {
    int value;
    std::unique_ptr<SmartNode> left{nullptr};
    std::unique_ptr<SmartNode> right{nullptr};
    
    // Détermine si ce noeud est terminal (n'a pas d'enfants)
    bool is_leaf() const {
        // Les unique_ptr se convertissent implicitement en booléens (true si non-null, false sinon)
        return !left && !right;
    }
    
    // Ajoute récursivement une nouvelle valeur dans l'arbre en respectant la propriété d'ABR
    void insert(int value) {
        if (value < this->value) {
            // Pour les valeurs inférieures à la valeur du noeud, on insère à gauche
            if (!left) {
                left = create_smart_node(value);
            } else {
                left->insert(value);
            }
        } else {
            // Pour les valeurs supérieures ou égales, on insère à droite
            if (!right) {
                right = create_smart_node(value);
            } else {
                right->insert(value);
            }
        }
    }
    
    // Affiche l'arbre en parcours infixe (gauche-racine-droite) pour obtenir les valeurs triées
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
    
    // Récupère la valeur minimale stockée dans l'arbre (noeud le plus à gauche)
    int min() const {
        if (!left) {
            return value;
        }
        return left->min();
    }
    
    // Récupère la valeur maximale stockée dans l'arbre (noeud le plus à droite)
    int max() const {
        if (!right) {
            return value;
        }
        return right->max();
    }
    
    // Effectue un parcours préfixe (racine-gauche-droite) et renvoie les pointeurs vers les noeuds
    std::vector<const SmartNode*> prefix() const noexcept {
        std::vector<const SmartNode*> result;
        
        // Commencer par visiter la racine
        result.push_back(this);
        
        // Puis visiter récursivement le sous-arbre gauche
        if (left) {
            std::vector<const SmartNode*> left_nodes = left->prefix();
            result.insert(result.end(), left_nodes.begin(), left_nodes.end());
        }
        
        // Enfin visiter récursivement le sous-arbre droit
        if (right) {
            std::vector<const SmartNode*> right_nodes = right->prefix();
            result.insert(result.end(), right_nodes.begin(), right_nodes.end());
        }
        
        return result; 
    }
};

// Crée un nouveau noeud géré par unique_ptr avec la valeur fournie
std::unique_ptr<SmartNode> create_smart_node(int value) {
    return std::make_unique<SmartNode>(SmartNode{value});
}

// Trouve et renvoie une référence vers le noeud le plus à gauche (valeur minimale)
// Utilisé principalement pour la suppression d'un noeud avec deux enfants
std::unique_ptr<SmartNode>& most_left(std::unique_ptr<SmartNode>& node) {
    if (!node) {
        return node;
    }
    
    if (!node->left) {
        return node;
    }
    
    return most_left(node->left);
}

// Supprime un noeud contenant la valeur spécifiée en préservant les propriétés de l'ABR
// Gère trois cas: 1) noeud feuille, 2) noeud avec un enfant, 3) noeud avec deux enfants
bool remove(std::unique_ptr<SmartNode>& node, int value) {
    if (!node) {
        return false;
    }
    
    if (value < node->value) {
        return remove(node->left, value);
    }
    
    if (value > node->value) {
        return remove(node->right, value);
    }
    
    // Si on arrive ici, c'est que la valeur du noeud courant est celle à supprimer
    
    // Cas 1: noeud terminal (sans enfants)
    if (node->is_leaf()) {
        node.reset();  // Libère la mémoire et met le pointeur à nullptr
        return true;
    }
    
    // Cas 2: Noeud avec un seul enfant
    if (!node->left) {
        // Le noeud n'a qu'un enfant droit
        node = std::move(node->right);  // Transfert de propriété
        return true;
    }
    
    if (!node->right) {
        // Le noeud n'a qu'un enfant gauche
        node = std::move(node->left);  // Transfert de propriété
        return true;
    }
    
    // Cas 3: Noeud avec deux enfants
    // On cherche le successeur inorder (plus petite valeur dans le sous-arbre droit)
    std::unique_ptr<SmartNode>& successor = most_left(node->right);
    
    // Copier la valeur du successeur dans le noeud courant
    node->value = successor->value;
    
    // Supprimer le successeur (qui a au plus un enfant droit)
    if (!successor->right) {
        successor.reset();
    } else {
        successor = std::move(successor->right);
    }
    
    return true;
}

// Classe qui encapsule la gestion d'un arbre binaire de recherche avec pointeurs intelligents
class BinaryTree {
private:
    std::unique_ptr<SmartNode> root{nullptr};  // Racine de l'arbre, initialement vide
    
public:
    // Constructeur par défaut
    BinaryTree() = default;
    
    // Constructeur avec valeur initiale
    explicit BinaryTree(int root_value) {
        root = create_smart_node(root_value);
    }
    
    // Insérer une valeur dans l'arbre
    void insert(int value) {
        if (!root) {
            root = create_smart_node(value);
        } else {
            root->insert(value);
        }
    }
    
    // Supprimer une valeur de l'arbre
    bool remove(int value) {
        return ::remove(root, value);
    }
    
    // Vider l'arbre
    void clear() {
        root.reset();
    }
    
    // Vérifie si l'arbre contient une valeur donnée
    bool contains(int value) const {
        return ::contains(root, value);
    }
    
    // Calculer la hauteur de l'arbre
    size_t height() const {
        if (!root) {
            return 0;
        }
        return root->height();
    }
    
    // Afficher l'arbre en ordre infixe
    void display_infix() const {
        if (root) {
            root->display_infix();
        }
        std::cout << std::endl;
    }
    
    // Valeur minimale
    int min() const {
        if (!root) {
            throw std::runtime_error("Arbre vide");
        }
        return root->min();
    }
    
    // Valeur maximale
    int max() const {
        if (!root) {
            throw std::runtime_error("Arbre vide");
        }
        return root->max();
    }
    
    // Calcule et renvoie la somme de toutes les valeurs dans l'arbre en utilisant le parcours préfixe
    int sum() const {
        if (!root) {
            return 0;
        }
        
        std::vector<const SmartNode*> nodes = root->prefix();
        int total = 0;
        for (const auto* node : nodes) {
            total += node->value;
        }
        return total;
    }
};

// Recherche récursivement une valeur dans l'arbre binaire de recherche
bool contains(const std::unique_ptr<SmartNode>& node, int value) {
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
    
    std::cout << "Suppression de la valeur 3: " << (tree.remove(3) ? "réussi" : "échec") << std::endl;
    
    std::cout << "Affichage après suppression: ";
    tree.display_infix();
    
    return 0;
}