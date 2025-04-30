#include <iostream>
#include <vector>
#include <algorithm>

// Vérifier si le vecteur est ordonné dans l'ordre croissant
bool is_sorted(std::vector<int> const& vec) { 
    return std::is_sorted(vec.begin(), vec.end()); 
}

// Implémentation de l'algorithme de trip par sélection 
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

// Test
int main() {
    // Array de test
    std::vector<int> array {6, 2, 8, 1, 5, 3, 9};
    
    // Affichage de l'array original
    std::cout << "Array original : ";
    for (int num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Tri de l'array
    selection_sort(array);
    std::cout << "Après le tri de sélection : ";
    for (int num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    if (is_sorted(array)) {
        std::cout << "L'array est trié." << std::endl;
    } else {
        std::cout << "L'array n'est pas trié." << std::endl;
    }
    
    return 0;
}