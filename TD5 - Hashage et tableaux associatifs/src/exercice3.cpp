#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdlib> 
#include <ctime> 
#include <iomanip> 
#include <cstddef> 
#include <algorithm> 

enum class CardKind {
    Heart,
    Diamond,
    Club,
    Spade,
};

enum class CardValue {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
};

struct Card {
    CardKind kind;
    CardValue value;

    // Définit l'égalité entre deux cartes
    bool operator==(const Card& other) const {
        return kind == other.kind && value == other.value;
    }

    // Calcule un hachage simple pour une carte
    std::size_t hash() const {
        // Convertit les énumérations en entiers avant de les additionner
        return static_cast<std::size_t>(static_cast<int>(kind)) + static_cast<std::size_t>(static_cast<int>(value));
    }

    // Génère un hachage unique pour éviter les collisions
    std::size_t perfect_hash() const {
        // Utilise 13 (nombre de valeurs possibles) comme multiplicateur pour garantir l'unicité
        return static_cast<std::size_t>(static_cast<int>(kind)) * 13 + static_cast<std::size_t>(static_cast<int>(value));
    }
};

// Fournit un hasher personnalisé pour utiliser Card dans un unordered_map
namespace std {
    template <>
    struct hash<Card> {
        std::size_t operator()(const Card& card) const {
            return card.perfect_hash();
        }
    };
}

// Retourne une représentation textuelle d'une carte
std::string card_name(Card const& card) {
    std::string name {};

    unsigned int card_value {(static_cast<unsigned int>(card.value)+2) % 14};

    if (card_value < 10) {
        name += '0' + std::to_string(card_value);
    } else if (card_value == 10) {
        name += "10";
    } else if (card_value == 11) {
        name += 'J';
    } else if (card_value == 12) {
        name += 'Q';
    } else if (card_value == 13) {
        name += 'K';
    }

    name += " of ";

    if (card.kind == CardKind::Heart) {
        name += "Heart";
    } else if (card.kind == CardKind::Diamond) {
        name += "Diamond";
    } else if (card.kind == CardKind::Club) {
        name += "Club";
    } else if (card.kind == CardKind::Spade) {
        name += "Spade";
    }
    return name;
}

// Crée un ensemble de cartes générées aléatoirement
std::vector<Card> get_cards(size_t const size) {
    std::vector<Card> cards {};
    cards.reserve(size);
    for (size_t i {0}; i < size; ++i) {
        cards.push_back({static_cast<CardKind>(rand() % 4), static_cast<CardValue>(rand() % 13)});
    }
    return cards;
}

int main() {
    // Vérifie l'opérateur d'égalité
    Card card1 = {CardKind::Heart, CardValue::Ace};
    Card card2 = {CardKind::Heart, CardValue::Ace};
    Card card3 = {CardKind::Spade, CardValue::Ace};

    std::cout << "card1 == card2: " << (card1 == card2 ? "true" : "false") << std::endl;
    std::cout << "card1 == card3: " << (card1 == card3 ? "true" : "false") << std::endl;

    // Teste la fonction de hachage simple
    std::cout << "Hash de card1: " << card1.hash() << std::endl;
    std::cout << "Hash de card3: " << card3.hash() << std::endl;

    // Teste la fonction de hachage optimisée
    std::cout << "Perfect hash de card1: " << card1.perfect_hash() << std::endl;
    std::cout << "Perfect hash de card3: " << card3.perfect_hash() << std::endl;

    // Illustre l'utilisation de Card dans une table de hachage
    std::unordered_map<Card, std::string> cardMap;
    cardMap[card1] = "As de Coeur";
    cardMap[card3] = "As de Pique";

    std::cout << "cardMap[card1]: " << cardMap[card1] << std::endl;
    std::cout << "cardMap[card3]: " << cardMap[card3] << std::endl;

    // Évalue si la fonction de hachage est sans collision
    std::cout << "\nVérification de la fonction de hachage parfaite:" << std::endl;
    std::vector<std::size_t> hashes;
    
    // Produit les hachages pour toutes les combinaisons possibles de cartes
    for (int k = 0; k < 4; ++k) {
        for (int v = 0; v < 13; ++v) {
            Card card = {static_cast<CardKind>(k), static_cast<CardValue>(v)};
            hashes.push_back(card.perfect_hash());
        }
    }
    
    // Recherche d'éventuelles collisions dans les hachages
    bool perfect = true;
    for (size_t i = 0; i < hashes.size(); ++i) {
        for (size_t j = i + 1; j < hashes.size(); ++j) {
            if (hashes[i] == hashes[j]) {
                perfect = false;
                std::cout << "Collision détectée entre les hachages " << hashes[i] << " et " << hashes[j] << std::endl;
            }
        }
    }
    
    if (perfect) {
        std::cout << "La fonction de hachage est sans collision: aucune collision détectée!" << std::endl;
    } else {
        std::cout << "La fonction de hachage présente des collisions." << std::endl;
    }

    // Configure le générateur de nombres aléatoires
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Génère 100 cartes aléatoires
    const size_t num_cards = 100;
    std::vector<Card> cards = get_cards(num_cards);
    
    // Compte les occurrences de chaque carte à l'aide d'une table de hachage
    std::unordered_map<Card, int> card_counts;
    
    // Enregistre les occurrences des cartes
    for (const auto& card : cards) {
        card_counts[card]++;
    }
    
    // Présente les résultats des comptages
    std::cout << "\nRésultats pour " << num_cards << " cartes générées aléatoirement:" << std::endl;
    std::cout << std::left << std::setw(20) << "Carte" 
              << std::right << std::setw(10) << "Occurrences" << std::endl;
    std::cout << std::string(30, '-') << std::endl;
    
    // Trie les résultats par type et valeur pour un affichage clair
    std::vector<std::pair<Card, int>> sorted_counts(card_counts.begin(), card_counts.end());
    std::sort(sorted_counts.begin(), sorted_counts.end(), 
              [](const auto& a, const auto& b) {
                  if (a.first.kind != b.first.kind) {
                      return static_cast<int>(a.first.kind) < static_cast<int>(b.first.kind);
                  }
                  return static_cast<int>(a.first.value) < static_cast<int>(b.first.value);
              });
    
    for (const auto& [card, count] : sorted_counts) {
        std::cout << std::left << std::setw(20) << card_name(card) 
                  << std::right << std::setw(10) << count << std::endl;
    }
    
    // Fournit des statistiques supplémentaires
    std::cout << "\nStatistiques:" << std::endl;
    std::cout << "Nombre total de cartes générées: " << num_cards << std::endl;
    std::cout << "Nombre de cartes uniques: " << card_counts.size() << std::endl;
    
    // Identifie la carte la plus fréquente
    auto max_card = std::max_element(card_counts.begin(), card_counts.end(),
                                    [](const auto& a, const auto& b) { return a.second < b.second; });
    
    if (max_card != card_counts.end()) {
        std::cout << "Carte la plus fréquente: " << card_name(max_card->first) 
                  << " (" << max_card->second << " fois)" << std::endl;
    }
    
    return 0;
}