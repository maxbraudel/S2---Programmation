#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

int main() {
    // Créer un vecteur pour stocker des entiers aléatoires
    std::vector<int> numbers;
    const int SIZE = 20;
    
    // Initialisation du générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 100);
    
    // Remplissage du vecteur avec des nombres aléatoires
    std::cout << "Remplissage du vecteur avec des nombres aléatoires..." << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        numbers.push_back(dist(gen));
    }
    
    // Affichage du vecteur en utilisant les itérateurs
    std::cout << "\nContenu du vecteur :" << std::endl;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Recherche d'un nombre
    int searchNumber;
    std::cout << "\nEntrez un nombre à rechercher : ";
    std::cin >> searchNumber;
    
    auto findResult = std::find(numbers.begin(), numbers.end(), searchNumber);
    if (findResult != numbers.end()) {
        std::cout << searchNumber << " a été trouvé dans le vecteur à la positions " 
                  << std::distance(numbers.begin(), findResult) << std::endl;
    } else {
        std::cout << searchNumber << " n'a pas été trouvé dans le vecteur" << std::endl;
    }
    
    // Comptage des occurrences
    int countNumber;
    std::cout << "\nEntrez un nombre pour compter ses occurrences : ";
    std::cin >> countNumber;
    
    int occurrences = std::count(numbers.begin(), numbers.end(), countNumber);
    std::cout << countNumber << " apparaît " << occurrences << " fois dans le vecteur" << std::endl;
    
    // Tri du vecteur
    std::cout << "\nTriage du vecteur..." << std::endl;
    std::sort(numbers.begin(), numbers.end());
    
    std::cout << "Vecteur trié :" << std::endl;
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Calcul de la somme
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "\nSomme de tous les éléments : " << sum << std::endl;
    
    return 0;
}
