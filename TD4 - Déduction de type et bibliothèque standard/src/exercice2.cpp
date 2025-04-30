#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Fonction lambda pour vérifier si un caractère est un espace
auto const is_space = [](char letter){ return letter == ' '; };

// Fonction qui retourne la longueur du premier mot dans une chaîne de caractères
size_t first_word_length(std::string const& str) {
    // Trouve le premier caractère non espace
    auto start = std::find_if_not(str.begin(), str.end(), is_space);
    
    // Si la chaîne est vide ou contient uniquement des espaces
    if (start == str.end()) {
        return 0;
    }
    
    // Trouve la première occurrence d'un espace
    auto end = std::find_if(start, str.end(), is_space);
    
    // Retourne la longueur du premier mot
    return std::distance(start, end);
}

// Fonction qui retourne un vecteur contenant tous les mots d'une chaîne de caractères
std::vector<std::string> split_string(std::string const& str) {
    std::vector<std::string> words;
    
    // Position de départ pour la recherche
    auto start = str.begin();
    
    while (start != str.end()) {
        // Trouve le premier caractère non espace
        start = std::find_if_not(start, str.end(), is_space);
        
        // Si nous sommes à la fin, la boucle s'arrête
        if (start == str.end()) {
            break;
        }
        
        // Trouver la fin du mot actuel
        auto end = std::find_if(start, str.end(), is_space);
        
        // Ajouter le mot au vecteur
        words.push_back(std::string(start, end));
        
        // Déplacer la position de départ
        start = end;
    }
    
    return words;
}

int main() {
    // Phrases tests
    std::string sentence1 = "Bonjour le monde";
    std::string sentence2 = "   Ceci est   un test avec plusieurs   espaces   ";
    
    // Tester la fonction first_word_length
    std::cout << "Première phrase: \"" << sentence1 << "\"" << std::endl;
    std::cout << "Longueur du premier mot : " << first_word_length(sentence1) << std::endl;
    
    std::cout << "\nDeuxième phrase: \"" << sentence2 << "\"" << std::endl;
    std::cout << "Longueur du premier mot: " << first_word_length(sentence2) << std::endl;
    
    // Tester la fonction split_string
    std::cout << "\nMots de la première phrase :" << std::endl;
    std::vector<std::string> words1 = split_string(sentence1);
    for (const auto& word : words1) {
        std::cout << "\"" << word << "\"" << std::endl;
    }
    
    std::cout << "\nMots de la deuxième phrase :" << std::endl;
    std::vector<std::string> words2 = split_string(sentence2);
    for (const auto& word : words2) {
        std::cout << "\"" << word << "\"" << std::endl;
    }
    
    // Demander à l'utilisateur de rentrer une phrase
    std::string user_sentence;
    std::cout << "\nEntrez une phrase à découper : ";
    std::getline(std::cin, user_sentence);
    
    std::cout << "Longueur du premier mot : " << first_word_length(user_sentence) << std::endl;
    
    std::cout << "Mots de votre phrase :" << std::endl;
    std::vector<std::string> user_words = split_string(user_sentence);
    for (const auto& word : user_words) {
        std::cout << "\"" << word << "\"" << std::endl;
    }
    
    return 0;
}
