#include <iostream>
#include <vector>
#include <algorithm>

// Vérifier si le vecteur est ordonné dans l'ordre croissant
bool is_sorted(std::vector<int> const& vec) { 
    return std::is_sorted(vec.begin(), vec.end()); 
}

// Fonction de partition pour le tri rapide
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

// Fonction de tri rapide récursive
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

// Surcharge pour simplifier l'appel initial
void quick_sort(std::vector<int> & vec) {
    if (!vec.empty()) {
        quick_sort(vec, 0, vec.size() - 1);
    }
}

// Fonction pour fusionner deux sous-tableaux triés (pour le tri fusion)
void merge_sort_merge(std::vector<int> & vec, size_t const left, size_t const middle, size_t const right) {
    // Tailles des deux sous-tableaux
    size_t const left_size = middle - left + 1;
    size_t const right_size = right - middle;
    
    // Création des tableaux temporaires
    std::vector<int> left_array(vec.begin() + left, vec.begin() + middle + 1);
    std::vector<int> right_array(vec.begin() + middle + 1, vec.begin() + right + 1);
    
    // Indices pour parcourir les tableaux
    size_t left_index = 0;
    size_t right_index = 0;
    size_t merge_index = left;
    
    // Fusion des deux tableaux
    while (left_index < left_size && right_index < right_size) {
        if (left_array[left_index] <= right_array[right_index]) {
            vec[merge_index] = left_array[left_index];
            left_index++;
        } else {
            vec[merge_index] = right_array[right_index];
            right_index++;
        }
        merge_index++;
    }
    
    // Copie des éléments restants du tableau gauche
    while (left_index < left_size) {
        vec[merge_index] = left_array[left_index];
        left_index++;
        merge_index++;
    }
    
    // Copie des éléments restants du tableau droit
    while (right_index < right_size) {
        vec[merge_index] = right_array[right_index];
        right_index++;
        merge_index++;
    }
}

// Fonction de tri fusion récursive
void merge_sort(std::vector<int> & vec, size_t const left, size_t const right) {
    // Condition d'arrêt de la récursion
    if (left < right) {
        // Calcul du milieu
        size_t middle = left + (right - left) / 2;
        
        // Tri récursif des deux sous-tableaux
        merge_sort(vec, left, middle);
        merge_sort(vec, middle + 1, right);
        
        // Fusion des deux sous-tableaux triés
        merge_sort_merge(vec, left, middle, right);
    }
}

// Surcharge pour simplifier l'appel initial
void merge_sort(std::vector<int> & vec) {
    if (!vec.empty()) {
        merge_sort(vec, 0, vec.size() - 1);
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
    
    // Tri de l'array avec quick sort
    quick_sort(array);
    std::cout << "Après le tri rapide : ";
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