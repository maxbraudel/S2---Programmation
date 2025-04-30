#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <stack>
#include <cctype>

// Définition des énumérations et de la structure
enum class Operator { ADD, SUB, MUL, DIV };
enum class TokenType { OPERATOR, OPERAND };
struct Token {
    TokenType type;
    float value;
    Operator op;
};

// Convertir un string en plusieurs tokens avec des espaces comme séparateurs
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
        
        // Vérifier si le caractère est un chiffre
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

// Fonction pour créer un Token à partir d'un nombre flottant
Token make_token(float value)
{
    return Token{TokenType::OPERAND, value, Operator::ADD}; // Operator n'est pas utilisé ici
}

// Fonction pour créer un Token à partir d'un opérateur
Token make_token(Operator op)
{
    return Token{TokenType::OPERATOR, 0.0f, op}; // value n'est pas utilisée ici
}

// Fonction pour convertir un vecteur de chaînes en vecteur de Tokens
std::vector<Token> tokenize(std::vector<std::string> const& words)
{
    std::vector<Token> tokens;
    
    for (const auto& word : words) {
        // Vérifie d'abord si c'est un opérateur connu
        if (word == "+") {
            tokens.push_back(make_token(Operator::ADD));
        } else if (word == "-") {
            tokens.push_back(make_token(Operator::SUB));
        } else if (word == "*") {
            tokens.push_back(make_token(Operator::MUL));
        } else if (word == "/") {
            tokens.push_back(make_token(Operator::DIV));
        } 
        // Sinon, essaie de l'interpréter comme un nombre
        else if (is_floating(word)) {
            try {
                tokens.push_back(make_token(std::stof(word)));
            } catch (const std::exception& e) {
                std::cerr << "Erreur lors de la conversion de '" << word << "' en nombre: " << e.what() << std::endl;
                // On continue avec le token suivant
            }
        } 
        // Si ce n'est ni un opérateur connu ni un nombre
        else {
            std::cerr << "Erreur : Token inconnu '" << word << "'" << std::endl;
            // On ne l'ajoute pas aux tokens pour éviter les erreurs
        }
    }
    
    return tokens;
}

// Évalue l'expression NPI avec des Tokens
float npi_evaluate(std::vector<Token> const& tokens)
{
    std::stack<float> stack;
    
    for (const auto& token : tokens) {
        if (token.type == TokenType::OPERAND) {
            // Si c'est un opérande, on l'empile
            stack.push(token.value);
        } else {

            // Vérifie s'il y a assez d'opérandes
            if (stack.size() < 2) {
                std::cerr << "Erreur : Expression invalide (pas assez d'opérandes pour l'opérateur)" << std::endl;
                continue;
            }
            
            float rightOperand = stack.top();
            stack.pop();
            float leftOperand = stack.top();
            stack.pop();
            
            // Effectue l'opération selon l'opérateur
            float result = 0.0f;
            bool operationSuccess = true;
            
            switch (token.op) {
                case Operator::ADD:
                    result = leftOperand + rightOperand;
                    break;
                case Operator::SUB:
                    result = leftOperand - rightOperand;
                    break;
                case Operator::MUL:
                    result = leftOperand * rightOperand;
                    break;
                case Operator::DIV:
                    if (rightOperand == 0.0f) {
                        std::cerr << "Erreur : Division par 0 impossible" << std::endl;
                        operationSuccess = false;
                    } else {
                        result = leftOperand / rightOperand;
                    }
                    break;
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
    }
    
    // Vérifie s'il y a exactement une valeur restante sur la pile
    if (stack.size() != 1) {
        std::cerr << "Erreur : Expression invalide (trop de valeurs sur la pile)" << std::endl;
        return 0.0f;
    }
    
    return stack.top();
}

int main()
{
    std::string expression;
    
    std::cout << "Entrer une expression NPI (exemple : '3 4 +' pour 3 + 4): ";
    std::getline(std::cin, expression);
    
    // Convertir l'expression en chaînes
    std::vector<std::string> words = split_string(expression);
    
    // Convertir les chaînes en tokens
    std::vector<Token> tokens = tokenize(words);
    
    // Évaluer l'expression
    float result = npi_evaluate(tokens);
    
    // Afficher le résultat
    std::cout << "Résultat : " << result << std::endl;
    
    return 0;
}