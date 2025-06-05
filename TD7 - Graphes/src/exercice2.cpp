#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <functional> // Nécessaire pour utiliser std::function dans les callbacks

namespace Graph {
    struct WeightedGraphEdge {
        int to {};
        float weight {1.0f};

        // L'opérateur 'default' génère automatiquement les opérateurs de comparaison membre à membre
        // Disponible uniquement en C++20. Pour les versions antérieures, voir implémentations manuelles ci-dessous
        bool operator==(WeightedGraphEdge const& other) const = default;
        bool operator!=(WeightedGraphEdge const& other) const = default;
    };

    struct WeightedGraph {
        // La structure unordered_map offre:
        // - Complexité O(1) pour les opérations d'ajout et de recherche
        // - Stockage flexible des sommets sans contraintes d'ordre
        // - Support pour des identifiants non-consécutifs
        // - Possibilité d'utiliser divers types d'identifiants (string, char, int, etc.)
        std::unordered_map<int, std::vector<WeightedGraphEdge>> adjacency_list {};

        void add_vertex(int const id);

        void add_directed_edge(int const from, int const to, float const weight = 1.0f);
        void add_undirected_edge(int const from, int const to, float const weight = 1.0f);
        
        // Génération automatique des opérateurs de comparaison (C++20)
        bool operator==(WeightedGraph const& other) const = default;
        bool operator!=(WeightedGraph const& other) const = default;

        void print_DFS(int const start) const;
        void print_BFS(int const start) const;
        
        // Parcours DFS avec fonction de rappel personnalisable
        void DFS(int const start, std::function<void(int const)> const& callback) const;
    };

    // Ajoute un nouveau sommet au graphe s'il n'existe pas déjà
    void WeightedGraph::add_vertex(int const id) {
        // Vérification de l'existence du sommet
        if (adjacency_list.find(id) == adjacency_list.end()) {
            // Initialisation avec une liste d'arêtes vide
            adjacency_list[id] = std::vector<WeightedGraphEdge>{};
        }
    }

    // Crée une connexion unidirectionnelle entre deux sommets
    void WeightedGraph::add_directed_edge(int const from, int const to, float const weight) {
        // Création des sommets si nécessaire
        add_vertex(from);
        add_vertex(to);
        
        // Établissement de la connexion orientée
        adjacency_list[from].push_back({to, weight});
    }

    // Crée une connexion bidirectionnelle entre deux sommets
    void WeightedGraph::add_undirected_edge(int const from, int const to, float const weight) {
        // Création de deux arêtes symétriques
        add_directed_edge(from, to, weight);
        add_directed_edge(to, from, weight);
    }

    // Génère un graphe à partir d'une représentation matricielle
    WeightedGraph build_from_adjacency_matrix(std::vector<std::vector<float>> const& adjacency_matrix) {
        WeightedGraph graph;
        
        // Analyse des lignes de la matrice (sommets source)
        for (size_t i = 0; i < adjacency_matrix.size(); ++i) {
            // Enregistrement du sommet dans le graphe
            graph.add_vertex(static_cast<int>(i));
            
            // Analyse des colonnes (sommets destination)
            for (size_t j = 0; j < adjacency_matrix[i].size(); ++j) {
                // Une valeur non-nulle indique une connexion
                if (adjacency_matrix[i][j] != 0.0f) {
                    graph.add_directed_edge(static_cast<int>(i), static_cast<int>(j), adjacency_matrix[i][j]);
                }
            }
        }
        
        return graph;
    }

    // Affiche les sommets selon un parcours en profondeur
    void WeightedGraph::print_DFS(int const start) const {
        // Validation du sommet initial
        if (adjacency_list.find(start) == adjacency_list.end()) {
            std::cout << "Le sommet de départ n'existe pas!" << std::endl;
            return;
        }
        
        // Registre des sommets déjà explorés
        std::set<int> visited;
        
        // Structure LIFO pour le parcours en profondeur
        std::stack<int> to_visit;
        
        // Initialisation avec le sommet de départ
        to_visit.push(start);
        
        std::cout << "Parcours en profondeur (DFS) à partir du sommet " << start << ": ";
        
        while (!to_visit.empty()) {
            // Extraction du prochain sommet à explorer
            int current = to_visit.top();
            to_visit.pop();
            
            // Traitement uniquement des sommets non visités
            if (visited.find(current) == visited.end()) {
                // Marquage du sommet courant
                visited.insert(current);
                
                // Affichage du sommet
                std::cout << current << " ";
                
                // Ajout des voisins non visités à la pile
                // Parcours inversé pour préserver l'ordre naturel lors de l'exploration
                if (adjacency_list.find(current) != adjacency_list.end()) {
                    const auto& edges = adjacency_list.at(current);
                    for (auto it = edges.rbegin(); it != edges.rend(); ++it) {
                        int neighbor = it->to;
                        if (visited.find(neighbor) == visited.end()) {
                            to_visit.push(neighbor);
                        }
                    }
                }
            }
        }
        
        std::cout << std::endl;
    }
    
    // Affiche les sommets selon un parcours en largeur
    void WeightedGraph::print_BFS(int const start) const {
        // Validation du sommet initial
        if (adjacency_list.find(start) == adjacency_list.end()) {
            std::cout << "Le sommet de départ n'existe pas!" << std::endl;
            return;
        }
        
        // Registre des sommets déjà explorés
        std::set<int> visited;
        
        // Structure FIFO pour le parcours en largeur
        std::queue<int> to_visit;
        
        // Initialisation avec le sommet de départ
        visited.insert(start);
        to_visit.push(start);
        
        std::cout << "Parcours en largeur (BFS) à partir du sommet " << start << ": ";
        
        while (!to_visit.empty()) {
            // Extraction du prochain sommet à explorer
            int current = to_visit.front();
            to_visit.pop();
            
            // Affichage du sommet
            std::cout << current << " ";
            
            // Ajout des voisins non visités à la file
            if (adjacency_list.find(current) != adjacency_list.end()) {
                for (const auto& edge : adjacency_list.at(current)) {
                    int neighbor = edge.to;
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        to_visit.push(neighbor);
                    }
                }
            }
        }
        
        std::cout << std::endl;
    }
    
    // Version générique du parcours DFS permettant un traitement personnalisé des sommets
    void WeightedGraph::DFS(int const start, std::function<void(int const)> const& callback) const {
        // Validation silencieuse du sommet initial
        if (adjacency_list.find(start) == adjacency_list.end()) {
            return; // Aucune action si le sommet n'existe pas
        }
        
        // Registre des sommets déjà explorés
        std::set<int> visited;
        
        // Structure LIFO pour le parcours en profondeur
        std::stack<int> to_visit;
        
        // Initialisation avec le sommet de départ
        to_visit.push(start);
        
        while (!to_visit.empty()) {
            // Extraction du prochain sommet à explorer
            int current = to_visit.top();
            to_visit.pop();
            
            // Traitement uniquement des sommets non visités
            if (visited.find(current) == visited.end()) {
                // Marquage du sommet courant
                visited.insert(current);
                
                // Application de la fonction de rappel sur le sommet
                callback(current);
                
                // Ajout des voisins non visités à la pile
                if (adjacency_list.find(current) != adjacency_list.end()) {
                    const auto& edges = adjacency_list.at(current);
                    for (auto it = edges.rbegin(); it != edges.rend(); ++it) {
                        int neighbor = it->to;
                        if (visited.find(neighbor) == visited.end()) {
                            to_visit.push(neighbor);
                        }
                    }
                }
            }
        }
    }

} // namespace

// Programme de démonstration et de test des fonctionnalités
int main() {
    // Définition d'un graphe de test sous forme matricielle
    // Représentation d'un graphe à 4 sommets avec différentes connexions pondérées
    std::vector<std::vector<float>> adjacency_matrix = {
        {0.0f, 2.0f, 1.0f, 0.0f},
        {2.0f, 0.0f, 3.0f, 0.0f},
        {1.0f, 3.0f, 0.0f, 1.5f},
        {0.0f, 0.0f, 1.5f, 0.0f}
    };
    
    // Construction d'un graphe via la matrice d'adjacence
    Graph::WeightedGraph graph1 = Graph::build_from_adjacency_matrix(adjacency_matrix);
    
    // Construction manuelle d'un graphe équivalent
    Graph::WeightedGraph graph2;
    
    // Création de la structure des sommets
    for (int i = 0; i < 4; ++i) {
        graph2.add_vertex(i);
    }
    
    // Établissement des connexions bidirectionnelles
    graph2.add_undirected_edge(0, 1, 2.0f);
    graph2.add_undirected_edge(0, 2, 1.0f);
    graph2.add_undirected_edge(1, 2, 3.0f);
    graph2.add_undirected_edge(2, 3, 1.5f);
    
    // Vérification de l'équivalence structurelle
    if (graph1 == graph2) {
        std::cout << "Les deux graphes sont identiques!" << std::endl;
    } else {
        std::cout << "Les deux graphes sont différents!" << std::endl;
    }
    
    std::cout << "\n--- Test des parcours de graphe ---" << std::endl;
    
    // Démonstration du parcours en profondeur depuis le sommet 0
    std::cout << "1. ";
    graph1.print_DFS(0);
    
    // Démonstration du parcours en largeur depuis le sommet 0
    std::cout << "2. ";
    graph1.print_BFS(0);
    
    // Parcours en profondeur avec un point de départ alternatif
    std::cout << "3. ";
    graph1.print_DFS(2);
    
    // Parcours en largeur avec un point de départ alternatif
    std::cout << "4. ";
    graph1.print_BFS(2);
    
    // Utilisation du DFS avec une fonction d'affichage personnalisée
    std::cout << "5. DFS avec callback à partir du sommet 0: ";
    graph1.DFS(0, [](int const vertex) {
        std::cout << vertex << " ";
    });
    std::cout << std::endl;
    
    // Démonstration avancée: utilisation du DFS pour effectuer un calcul
    std::cout << "6. Somme des IDs des sommets parcourus en DFS à partir du sommet 1: ";
    int sum = 0;
    graph1.DFS(1, [&sum](int const vertex) {
        sum += vertex;
    });
    std::cout << sum << std::endl;
    
    return 0;
}