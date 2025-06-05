#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <queue>
#include <stack>
#include <set>

namespace Graph {
    struct WeightedGraphEdge {
        int to {};
        float weight {1.0f};

        // L'utilisation de 'default' permet de générer automatiquement les opérateurs de comparaison membre à membre
        // Cette fonctionnalité est disponible uniquement en C++20. Si vous utilisez une version antérieure, 
        // les implémentations manuelles sont fournies plus bas
        bool operator==(WeightedGraphEdge const& other) const = default;
        bool operator!=(WeightedGraphEdge const& other) const = default;
    };

    struct WeightedGraph {
        // Les tableaux associatifs (unordered_map) offrent une complexité O(1) pour l'ajout et la recherche
        // Avantages:
        // - Stockage des sommets dans un ordre quelconque
        // - Pas de contrainte d'identifiants consécutifs
        // - Flexibilité dans le type d'identifiants (string, char, int, etc.)
        std::unordered_map<int, std::vector<WeightedGraphEdge>> adjacency_list {};

        void add_vertex(int const id);

        void add_directed_edge(int const from, int const to, float const weight = 1.0f);
        void add_undirected_edge(int const from, int const to, float const weight = 1.0f);
        
        // Même fonctionnement que pour WeightedGraphEdge
        bool operator==(WeightedGraph const& other) const = default;
        bool operator!=(WeightedGraph const& other) const = default;

        void print_DFS(int const start) const;
        void print_BFS(int const start) const;
    };

    // Ajoute un sommet au graphe s'il n'existe pas déjà
    void WeightedGraph::add_vertex(int const id) {
        // Vérifie l'existence du sommet
        if (adjacency_list.find(id) == adjacency_list.end()) {
            // Création d'un nouveau sommet avec une liste d'arêtes vide
            adjacency_list[id] = std::vector<WeightedGraphEdge>{};
        }
    }

    // Ajoute une arête orientée du sommet 'from' vers le sommet 'to'
    void WeightedGraph::add_directed_edge(int const from, int const to, float const weight) {
        // Création des sommets si nécessaire
        add_vertex(from);
        add_vertex(to);
        
        // Ajout de l'arête orientée
        adjacency_list[from].push_back({to, weight});
    }

    // Ajoute une arête non orientée entre les sommets 'from' et 'to'
    void WeightedGraph::add_undirected_edge(int const from, int const to, float const weight) {
        // Création de deux arêtes orientées pour simuler une arête non orientée
        add_directed_edge(from, to, weight);
        add_directed_edge(to, from, weight);
    }

    // Construit un graphe à partir d'une matrice d'adjacence
    WeightedGraph build_from_adjacency_matrix(std::vector<std::vector<float>> const& adjacency_matrix) {
        WeightedGraph graph;
        
        // Analyse de chaque ligne de la matrice
        for (size_t i = 0; i < adjacency_matrix.size(); ++i) {
            // Création du sommet correspondant
            graph.add_vertex(static_cast<int>(i));
            
            // Analyse de chaque colonne pour identifier les connexions
            for (size_t j = 0; j < adjacency_matrix[i].size(); ++j) {
                // Une valeur non nulle indique une arête
                if (adjacency_matrix[i][j] != 0.0f) {
                    graph.add_directed_edge(static_cast<int>(i), static_cast<int>(j), adjacency_matrix[i][j]);
                }
            }
        }
        
        return graph;
    }

} // namespace

// Programme principal pour tester les fonctionnalités du graphe
int main() {
    // Définition d'une matrice d'adjacence
    // Représente un graphe de 4 sommets avec leurs connexions
    std::vector<std::vector<float>> adjacency_matrix = {
        {0.0f, 2.0f, 1.0f, 0.0f},
        {2.0f, 0.0f, 3.0f, 0.0f},
        {1.0f, 3.0f, 0.0f, 1.5f},
        {0.0f, 0.0f, 1.5f, 0.0f}
    };
    
    // Construction du graphe à partir de la matrice d'adjacence
    Graph::WeightedGraph graph1 = Graph::build_from_adjacency_matrix(adjacency_matrix);
    
    // Construction manuelle d'un graphe équivalent
    Graph::WeightedGraph graph2;
    
    // Création des sommets
    for (int i = 0; i < 4; ++i) {
        graph2.add_vertex(i);
    }
    
    // Ajout des connexions non orientées
    graph2.add_undirected_edge(0, 1, 2.0f);
    graph2.add_undirected_edge(0, 2, 1.0f);
    graph2.add_undirected_edge(1, 2, 3.0f);
    graph2.add_undirected_edge(2, 3, 1.5f);
    
    // Vérification de l'équivalence des deux graphes
    if (graph1 == graph2) {
        std::cout << "Les deux graphes sont identiques!" << std::endl;
    } else {
        std::cout << "Les deux graphes sont différents!" << std::endl;
    }
    
    return 0;
}