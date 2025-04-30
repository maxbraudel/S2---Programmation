#include <iostream>
#include <string>
#include <algorithm>

// Fonction qui vérifie si une chaîne de caractères est un palindrome
bool is_palindrome(std::string const& str) {

    // std::equal pour comparer les caractères de la chaîne avec les caractères de la chaîne inversée
    return std::equal(std::begin(str), std::end(str), std::rbegin(str));
}

// vérifie si une chaîne de caractères est un palindrome

bool is_palindrome_sanitized(std::string const& str) {
    // Créer une nouvelle chaîne sans caractères non-alphanumériques
    std::string cleaned;
    
    for (char c : str) {
        if (std::isalnum(c)) {
            // Convertir en minuscule et ajouter à la chaîne sanitized
            cleaned.push_back(std::tolower(c));
        }
    }
    
    // Vérifier si la chaîne nettoyée est un palindrome
    return std::equal(std::begin(cleaned), std::end(cleaned), std::rbegin(cleaned));
}

int main() {
    // Exemples de palindromes
    std::string stringsToTest[] = {
        "radar",
        "kayak",
        "Radar",
        "Kayak"
    };
    
    // Tester la fonction is_palindrome
    std::cout << "=== Test de la fonction is_palindrome ===" << std::endl;
    
    std::cout << "\nTest des candidats :" << std::endl;
    for (const auto& word : stringsToTest) {
        std::cout << "\"" << word << "\" est " 
                  << (is_palindrome(word) ? "un palindrome" : "PAS un palindrome")
                  << std::endl;
    }
    
    // Tester la fonction is_palindrome_sanitized
    std::cout << "\n=== Test de la fonction is_palindrome_sanitized ===" << std::endl;
    
    std::cout << "\nTest souple des candidats :" << std::endl;
    for (const auto& word : stringsToTest) {
        std::cout << "\"" << word << "\" est " 
                  << (is_palindrome_sanitized(word) ? "un palindrome" : "PAS un palindrome")
                  << std::endl;
    }
    
    // Permettre à l'utilisateur de tester avec une chaine en input
    std::string user_input;
    std::cout << "\nEntrez une chaîne pour vérifier si c'est un palindrome : ";
    std::getline(std::cin, user_input);
    
    std::cout << "\"" << user_input << "\" est " 
              << (is_palindrome(user_input) ? "un palindrome" : "PAS un palindrome")
              << " (vérification stricte)" << std::endl;
              
    std::cout << "\"" << user_input << "\" est " 
              << (is_palindrome_sanitized(user_input) ? "un palindrome" : "PAS un palindrome")
              << " (vérification souple : on ignore la majuscule et les caractères non-alphanumériques)" << std::endl;
    
    return 0;
}
