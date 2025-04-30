#include <iostream>
#include <vector>
#include <algorithm>

// Fonction de recherche dichotomique
int search(std::vector<int> const& vec, int const value) {

    // Indices pour définir la partie du tableau à traiter
    int left = 0;
    int right = vec.size() - 1;
    
    // Tant qu'il reste des éléments à traiter
    while (left <= right) {
        
        // Calcul de l'indice du milieu
        int middle = left + (right - left) / 2;
        
        // Si la valeur est trouvée
        if (vec[middle] == value) {
            return middle;
        }
        
        // Si la valeur est plus grande que la valeur du milieu
        if (vec[middle] < value) {
            // On cherche dans la partie droite
            left = middle + 1;
        } else {
            // Sinon, on cherche dans la partie gauche
            right = middle - 1;
        }
    }
    
    // Si la valeur n'est pas trouvée
    return -1;
}

// afficher le résultat de la recherche
void display_search_result(std::vector<int> const& vec, int const value) {
    std::cout << "Tableau : [";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
    
    std::cout << "Valeur recherchée : " << value << std::endl;
    
    int index = search(vec, value);
    if (index != -1) {
        std::cout << "La valeur " << value << " a été trouvée à l'indice " << index << std::endl;
    } else {
        std::cout << "La valeur " << value << " n'a pas été trouvée dans le tableau" << std::endl;
    }
    
    std::cout << std::endl;
}

// vérifier si un tableau est trié
bool is_sorted(std::vector<int> const& vec) {
    return std::is_sorted(vec.begin(), vec.end());
}

int main() {
    // Tableaux de test
    std::vector<int> array1 = {1, 2, 2, 3, 4, 8, 12};
    std::vector<int> array2 = {1, 2, 3, 3, 6, 12, 14, 15};
    std::vector<int> array3 = {2, 2, 3, 4, 5, 8, 12, 15, 16};
    std::vector<int> array4 = {5, 6, 7, 8, 9, 10, 11, 12, 13};
    std::vector<int> array5 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // Vérification que les tableaux sont triés
    if (!is_sorted(array1) || !is_sorted(array2) || !is_sorted(array3) || !is_sorted(array4) || !is_sorted(array5)) {
        std::cout << "Attention : Un ou plusieurs tableaux ne sont pas triés !" << std::endl;
    }
    
    // Test de la fonction search
    std::cout << "=== Tests de la recherche dichotomique ===" << std::endl << std::endl;
    
    display_search_result(array1, 8);
    display_search_result(array2, 15);
    display_search_result(array3, 16);
    display_search_result(array4, 6);
    display_search_result(array5, 10);
    
    return 0;
}