#include <functional>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>

enum class Insect {
    BumbleBee,
    Firefly,
    Moth,
    Mosquito,
    Termite,
    Cricket,
    Scarab,
    Hornet,
    Centipede,
    Mantis,
    HoneyBee
};

// Liste des valeurs possibles pour les insectes
std::vector<Insect> const insect_values {
    Insect::BumbleBee,
    Insect::Firefly,
    Insect::Moth,
    Insect::Mosquito,
    Insect::Termite,
    Insect::Cricket,
    Insect::Scarab,
    Insect::Hornet,
    Insect::Centipede,
    Insect::Mantis,
    Insect::HoneyBee
};

// Table de correspondance entre les insectes et leurs noms sous forme de chaînes
std::unordered_map<Insect, std::string> const insect_to_string = {
    {Insect::BumbleBee, "BumbleBee"},
    {Insect::Firefly, "Firefly"},
    {Insect::Moth, "Moth"},
    {Insect::Mosquito, "Mosquito"},
    {Insect::Termite, "Termite"},
    {Insect::Cricket, "Cricket"},
    {Insect::Scarab, "Scarab"},
    {Insect::Hornet, "Hornet"},
    {Insect::Centipede, "Centipede"},
    {Insect::Mantis, "Mantis"},
    {Insect::HoneyBee, "HoneyBee"}
};

// Comptages attendus pour chaque type d'insecte
std::vector<int> const expected_insect_counts {
    75,  // BumbleBee
    50,  // Firefly
    100, // Moth
    20,  // Mosquito
    400, // Termite
    150, // Cricket
    60,  // Scarab
    10,  // Hornet
    40,  // Centipede
    90,  // Mantis 
    5,   // HoneyBee
};

// Transforme un vecteur de comptages en un vecteur de probabilités
std::vector<float> probabilities_from_count(std::vector<int> const& counts) {
    std::vector<float> probabilities;
    probabilities.reserve(counts.size());
    
    // Calcule la somme totale des occurrences
    int sum = 0;
    for (int count : counts) {
        sum += count;
    }
    
    // Convertit les comptages en probabilités relatives
    if (sum > 0) { 
        for (int count : counts) {
            probabilities.push_back(static_cast<float>(count) / static_cast<float>(sum));
        }
    } else {
        float equal_probability = 1.0f / static_cast<float>(counts.size());
        for (size_t i = 0; i < counts.size(); ++i) {
            probabilities.push_back(equal_probability);
        }
    }
    
    return probabilities;
}

// Génère des observations d'insectes selon des probabilités données
std::vector<std::pair<Insect, int>> get_insect_observations(
    size_t const number_of_observations,
    std::vector<float> const& insect_probabilities,
    unsigned int const seed = std::random_device{}()
) {
    // Vérifie que la somme des probabilités vaut 1
    std::default_random_engine random_engine{seed};

    auto rand_insect_index { std::bind(std::discrete_distribution<size_t>{insect_probabilities.begin(), insect_probabilities.end()}, random_engine) };
    
    std::vector<std::pair<Insect, int>> observations {};
    observations.reserve(number_of_observations);

    for (size_t i {0}; i < number_of_observations; ++i) {
        size_t const random_insect_index { rand_insect_index() };
        Insect const random_insect { insect_values[random_insect_index] };
        
        // Vérifie si l'insecte actuel est identique au précédent
        if (!observations.empty() && observations.back().first == random_insect) {
            observations.back().second++;
            i -= 1;
        } else {
            observations.push_back({random_insect, 1});
        }
    }

    return observations;
}

#include <iostream>
#include <iomanip>

int main() {
    // Calcule les probabilités à partir des comptages attendus
    std::vector<float> probabilities = probabilities_from_count(expected_insect_counts);
    
    // Simule 10 000 observations d'insectes
    const size_t nb_observations = 10000;
    auto observations = get_insect_observations(nb_observations, probabilities);
    
    // Utilise une table de hachage pour recenser les occurrences de chaque insecte
    std::unordered_map<Insect, int> insect_counts;
    
    // Parcourt les observations pour cumuler les comptages
    for (const auto& observation : observations) {
        insect_counts[observation.first] += observation.second;
    }
    
    // Affiche les résultats des observations
    std::cout << "Résultats des observations de " << nb_observations << " insectes:" << std::endl;
    std::cout << std::left << std::setw(15) << "Insecte" << std::right << std::setw(10) << "Nombre" << std::endl;
    std::cout << std::string(25, '-') << std::endl;
    
    for (const auto& insect : insect_values) {
        std::cout << std::left << std::setw(15) << insect_to_string.at(insect)
                  << std::right << std::setw(10) << insect_counts[insect] << std::endl;
    }
    
    // Convertit les comptages observés en vecteur pour analyse
    std::vector<int> observed_counts;
    observed_counts.reserve(insect_values.size());
    
    for (const auto& insect : insect_values) {
        observed_counts.push_back(insect_counts[insect]);
    }
    
    // Calcule les probabilités réelles à partir des observations
    std::vector<float> observed_probabilities = probabilities_from_count(observed_counts);
    
    // Définit un seuil de tolérance pour la conformité (1%)
    const float threshold = 0.01f;
    bool is_conforming = true;
    
    // Affiche la comparaison entre probabilités initiales et observées
    std::cout << "\nComparaison des probabilités:" << std::endl;
    std::cout << std::left << std::setw(15) << "Insecte" 
              << std::right << std::setw(15) << "Prob. Initiale"
              << std::right << std::setw(15) << "Prob. Observée"
              << std::right << std::setw(15) << "Différence" 
              << std::right << std::setw(15) << "Conforme?" << std::endl;
    std::cout << std::string(75, '-') << std::endl;
    
    for (size_t i = 0; i < insect_values.size(); ++i) {
        float diff = std::abs(probabilities[i] - observed_probabilities[i]);
        bool is_insect_conforming = diff <= threshold;
        
        // Marque la non-conformité si un insecte dépasse le seuil
        if (!is_insect_conforming) {
            is_conforming = false;
        }
        
        std::cout << std::left << std::setw(15) << insect_to_string.at(insect_values[i])
                  << std::right << std::setw(15) << std::fixed << std::setprecision(6) << probabilities[i]
                  << std::right << std::setw(15) << std::fixed << std::setprecision(6) << observed_probabilities[i]
                  << std::right << std::setw(15) << std::fixed << std::setprecision(6) << diff
                  << std::right << std::setw(15) << (is_insect_conforming ? "Oui" : "Non") << std::endl;
    }
    
    // Affiche le verdict final de conformité
    std::cout << "\nRésultat global: ";
    if (is_conforming) {
        std::cout << "Les observations respectent les probabilités initiales (seuil de " << threshold << ")." << std::endl;
    } else {
        std::cout << "Les observations ne respectent pas les probabilités initiales (seuil de " << threshold << ")." << std::endl;
    }
    
    return 0;
}