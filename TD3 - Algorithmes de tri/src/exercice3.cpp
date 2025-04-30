#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "ScopedTimer.hpp"

// Fonction pour vérifier si un vecteur est trié
bool is_sorted(std::vector<int> const& vec) { 
    return std::is_sorted(vec.begin(), vec.end()); 
}

// Fonction pour générer un vecteur aléatoire
std::vector<int> generate_random_vector(size_t const size, int const max = 100) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max;} );
    return vec;
}

// Implémentation du tri par sélection (de l'exercice 1)
void selection_sort(std::vector<int> & vec) {
    int n = vec.size();
    
    // On parcourt le vecteur
    for (int i = 0; i < n - 1; i++) {

        // On trouve l'élément le plus petit
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (vec[j] < vec[min_idx]) {
                min_idx = j;
            }
        }
        
        // On échange l'élément le plus petit avec le premier élément
        if (min_idx != i) {
            std::swap(vec[i], vec[min_idx]);
        }
    }
}

// Fonction de partition pour le tri rapide (de l'exercice 2)
size_t quick_sort_partition(std::vector<int> & vec, size_t left, size_t right, size_t const pivot) {
    // On place le pivot à la fin
    int pivot_value = vec[pivot];
    std::swap(vec[pivot], vec[right]);
    
    // Indice du premier élément plus grand que le pivot
    size_t store_index = left;
    
    // On parcourt le tableau et on place les éléments plus petits que le pivot à gauche
    for (size_t i = left; i < right; i++) {
        if (vec[i] < pivot_value) {
            std::swap(vec[i], vec[store_index]);
            store_index++;
        }
    }
    
    // On place le pivot à sa place définitive
    std::swap(vec[store_index], vec[right]);
    
    // On renvoie l'indice du pivot
    return store_index;
}

// Fonction de tri rapide récursive (de l'exercice 2)
void quick_sort(std::vector<int> & vec, size_t const left, size_t const right) {

    // Condition d'arrêt de la récursion
    if (left < right) {
        // On choisit le pivot (ici, le dernier élément)
        size_t pivot = right;
        
        // On partitionne le tableau
        size_t pivot_index = quick_sort_partition(vec, left, right, pivot);
        
        // On trie récursivement les deux sous-tableaux
        if (pivot_index > 0) {
            quick_sort(vec, left, pivot_index - 1);
        }
        quick_sort(vec, pivot_index + 1, right);
    }
}

// pour simplifier l'appel initial (de l'exercice 2)
void quick_sort(std::vector<int> & vec) {
    if (!vec.empty()) {
        quick_sort(vec, 0, vec.size() - 1);
    }
}

// Fonction pour tester un algorithme de tri avec différentes tailles de vecteurs
void test_sort_algorithm(const std::string& name, void (*sort_function)(std::vector<int>&), const std::vector<size_t>& sizes) {
    std::cout << "\n=== Test de l'algorithme : " << name << " ===" << std::endl;
    
    for (size_t size : sizes) {

        // Génération d'un vecteur aléatoire
        std::vector<int> vec = generate_random_vector(size);
        
        // Copie du vecteur pour vérification
        std::vector<int> vec_copy = vec;
        
        // Mesure du temps d'exécution
        {
            ScopedTimer timer(name + " (taille " + std::to_string(size) + ")");
            sort_function(vec);
        }
        
        // Vérification que le vecteur est trié
        if (!is_sorted(vec)) {
            std::cout << "ERREUR : Le vecteur n'est pas trié !" << std::endl;
        }
    }
}

// Fonction wrapper pour std::sort
void std_sort(std::vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
}

int main() {
    
    // Initialisation du générateur de nombres aléatoires
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Tailles de vecteurs à tester
    std::vector<size_t> sizes = {100, 1000, 10000, 50000};
    
    // Test des différents algorithmes de tri
    test_sort_algorithm("Selection Sort", selection_sort, sizes);
    test_sort_algorithm("Quick Sort", quick_sort, sizes);
    test_sort_algorithm("std::sort", std_sort, sizes);
    
    // Comparaison sur un très grand vecteur (uniquement pour Quick Sort et std::sort)
    std::cout << "\n=== Comparaison sur un très grand vecteur (100000 éléments) ===" << std::endl;
    
    size_t large_size = 100000;
    std::vector<int> large_vec = generate_random_vector(large_size);
    std::vector<int> large_vec_copy = large_vec;
    
    {
        ScopedTimer timer("Quick Sort (taille " + std::to_string(large_size) + ")");
        quick_sort(large_vec);
    }
    
    {
        ScopedTimer timer("std::sort (taille " + std::to_string(large_size) + ")");
        std::sort(large_vec_copy.begin(), large_vec_copy.end());
    }
    
    std::cout << "\n=== Analyse des résultats ===" << std::endl;
    std::cout << "1. Le tri par sélection a une complexité de O(n²). Il est clairement inefficace pour de grands tableaux." << std::endl;
    std::cout << "2. Le tri rapide a une complexité moyenne de O(n log n), ce qui le rend beaucoup plus efficace." << std::endl;
    std::cout << "4. Pour les petits tableaux, la différence de performance entre le tri rapide et std::sort est moins notable." << std::endl;
    std::cout << "5. Pour les grands tableaux, std::sort est plus rapide car il est certainement bien mieux optimisé 😞" << std::endl;
    
    return 0;
}