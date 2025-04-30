#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <stack>
#include <cctype>

// Convertir un string en plusieurs tokens avec des espaces comme opérateurs
std::vector<std::string> split_string(std::string const& s)
{
    std::istringstream in(s); 
    return std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>()); 
}

// Vérifie si un token est un nombre à virgule
bool is_floating(std::string const& s)
{
    bool has_decimal_point = false;
    
    // Vérifie si la chaîne est vide
    if (s.empty()) {
        return false;
    }
    
    // Parcours chaque caractère de la chaîne
    for (size_t i = 0; i < s.length(); ++i) {
        // Pour les nombres négatifs
        if (i == 0 && s[i] == '-') {
            continue;
        }
        
        // Vérifier si le carractère est un chiffre
        if (std::isdigit(s[i])) {
            continue;
        }
        
        // Vérifie si le caractère est un point
        if (s[i] == '.') {
            // Si on a déjà un point, c'est pas un nombre
            if (has_decimal_point) {
                return false;
            }
            has_decimal_point = true;
            continue;
        }
        
        // Le caractère n'est ni un chiffre, ni un point
        return false;
    }
    
    return true;
}

// Évalue l'expression NPI
float npi_evaluate(std::vector<std::string> const& tokens)
{
    std::stack<float> stack;
    
    for (const auto& token : tokens) {
        // Vérifie d'abord si c'est un opérateur connu
        if (token == "+" || token == "-" || token == "*" || token == "/") {

            // Vérifie s'il y a assez d'opérandes
            if (stack.size() < 2) {
                std::cerr << "Erreur : Expression invalide (pas assez d'opérandes pour l'opérateur '" << token << "')" << std::endl;
                continue;
            }
            
            float rightOperand = stack.top();
            stack.pop();
            float leftOperand = stack.top();
            stack.pop();
            
            // Effectue l'opération
            float result = 0.0f;
            bool operationSuccess = true;
            
            if (token == "+") {
                result = leftOperand + rightOperand;
            } else if (token == "-") {
                result = leftOperand - rightOperand;
            } else if (token == "*") {
                result = leftOperand * rightOperand;
            } else if (token == "/") {
                if (rightOperand == 0.0f) {
                    std::cerr << "Erreur : Division par 0 impossible" << std::endl;
                    operationSuccess = false;
                } else {
                    result = leftOperand / rightOperand;
                }
            }
            
            // Empile le résultat seulement si l'opération a réussi
            if (operationSuccess) {
                stack.push(result);
            } else {
                // En cas d'erreur, on remet les opérandes sur la pile
                stack.push(leftOperand);
                stack.push(rightOperand);
            }
        }
        // Sinon, essaie de l'interpréter comme un nombre
        else if (is_floating(token)) {
            try {
                stack.push(std::stof(token));
            } catch (const std::exception& e) {
                std::cerr << "Erreur lors de la conversion de '" << token << "' en nombre: " << e.what() << std::endl;
                continue; // Passe au token suivant
            }
        }
        // Si ce n'est ni un opérateur connu ni un nombre
        else {
            std::cerr << "Erreur : Token inconnu '" << token << "'" << std::endl;
            continue;
        }
    }
    
    // Vérifie si il y a exactement une valeur restante sur la pile
    if (stack.size() != 1) {
        std::cerr << "Erreur : Expression invalide (trop de valeurs sur la pile)" << std::endl;
        return 0.0f;
    }
    
    return stack.top();
}

int main()
{
    std::string expression;
    
    std::cout << "Entrer une expression NPI (exmeple : '3 4 +' pour 3 + 4): ";
    std::getline(std::cin, expression);
    
    // Convertir l'expression en tokens
    std::vector<std::string> tokens = split_string(expression);
    
    // Évaluer l'expression
    float result = npi_evaluate(tokens);
    
    // Afficher le résultat
    std::cout << "Résultat : " << result << std::endl;
    
    return 0;
}