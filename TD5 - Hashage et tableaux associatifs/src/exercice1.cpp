#include <iostream>
#include <string>
#include <cstddef> // Inclusion pour utiliser size_t

// Calcule un hachage simple pour une chaîne, renvoyant un entier entre 0 et max
size_t hash_string(const std::string& str, size_t max) {
    size_t hash = 0;
    
    // Additionne les codes ASCII des caractères
    for (char c : str) {
        hash += static_cast<size_t>(c);
    }
    
    // Applique un modulo pour limiter la valeur entre 0 et max
    return hash % (max + 1);
}

// Calcule un hachage sensible à l'ordre des caractères
size_t hash_string_ordered(const std::string& str, size_t max) {
    size_t hash = 0;
    
    // Pondère chaque caractère selon sa position pour refléter l'ordre
    for (size_t i = 0; i < str.length(); ++i) {
        // Utilise une multiplication par 31 (nombre premier courant en hachage)
        // pour différencier les positions dans le calcul final
        hash = hash * 31 + static_cast<size_t>(str[i]);
    }
    
    // Restreint la valeur entre 0 et max via un modulo
    return hash % (max + 1);
}

// Implémente un hachage polynomial de type "rolling hash"
size_t polynomial_rolling_hash(std::string const& s, size_t p, size_t m) {
    size_t hash_value = 0;
    size_t p_pow = 1; // Initialise à p^0 = 1
    
    // Évalue le hachage polynomial : s[0]*p^(n-1) + s[1]*p^(n-2) + ... + s[n-1]*p^0
    for (char c : s) {
        hash_value = (hash_value + static_cast<size_t>(c) * p_pow) % m;
        p_pow = (p_pow * p) % m; // Calcule la puissance suivante de p, avec modulo pour limiter les dépassements
    }
    
    return hash_value;
}

int main() {
    std::string input;
    size_t max_value;
    
    std::cout << "Entrez une chaîne de caractères : ";
    std::getline(std::cin, input);
    
    std::cout << "Entrez la valeur maximale pour le hachage : ";
    std::cin >> max_value;
    
    size_t hash_result = hash_string(input, max_value);
    
    // Applique la fonction de hachage sensible à l'ordre
    size_t ordered_hash_result = hash_string_ordered(input, max_value);
    
    std::cout << "Hachage simple de \"" << input << "\" : " << hash_result << std::endl;
    std::cout << "Hachage ordonné de \"" << input << "\" : " << ordered_hash_result << std::endl;
    
    // Illustration avec des anagrammes
    std::string str1 = "abc";
    std::string str2 = "cba";
    
    std::cout << "\nExemple avec anagrammes :\n";
    std::cout << "Hachage simple de \"" << str1 << "\" : " << hash_string(str1, max_value) << std::endl;
    std::cout << "Hachage simple de \"" << str2 << "\" : " << hash_string(str2, max_value) << std::endl;
    std::cout << "Hachage ordonné de \"" << str1 << "\" : " << hash_string_ordered(str1, max_value) << std::endl;
    std::cout << "Hachage ordonné de \"" << str2 << "\" : " << hash_string_ordered(str2, max_value) << std::endl;
    
    // Test du hachage polynomial
    size_t p = 31; // Base pour le calcul
    size_t m = max_value + 1; // Valeur de modulo
    
    std::cout << "\nTest du hachage polynomial :\n";
    std::cout << "Hachage polynomial de \"" << str1 << "\" : " 
              << polynomial_rolling_hash(str1, p, m) << std::endl;
    std::cout << "Hachage polynomial de \"" << str2 << "\" : " 
              << polynomial_rolling_hash(str2, p, m) << std::endl;
    
    return 0;
}