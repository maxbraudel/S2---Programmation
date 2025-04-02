#include "fraction.hpp"
#include "utils.hpp"

#include <iostream>

// Affiche la fraction sous forme "numérateur/dénominateur"
std::ostream& operator<<(std::ostream& os, Fraction const& f) {
    os << f.numerator << "/" << f.denominator;
    return os;
}

// Ajoute une fraction à l'objet courant
Fraction& Fraction::operator+=(Fraction const& f) {
    numerator = numerator * f.denominator + f.numerator * denominator;
    denominator = denominator * f.denominator;
    
    // Simplifie la fraction après addition
    *this = simplify(*this);
    
    return *this;
}

// Soustrait une fraction de l'objet courant
Fraction& Fraction::operator-=(Fraction const& f) {
    numerator = numerator * f.denominator - f.numerator * denominator;
    denominator = denominator * f.denominator;
    
    // Simplifie la fraction après soustraction
    *this = simplify(*this);
    
    return *this;
}

// Multiplie l'objet courant par une fraction
Fraction& Fraction::operator*=(Fraction const& f) {
    numerator = numerator * f.numerator;
    denominator = denominator * f.denominator;
    
    // Simplifie la fraction après multiplication
    *this = simplify(*this);
    
    return *this;
}

// Divise l'objet courant par une fraction
Fraction& Fraction::operator/=(Fraction const& f) {
    numerator = numerator * f.denominator;
    denominator = denominator * f.numerator;
    
    // Simplifie la fraction après division
    *this = simplify(*this);
    
    return *this;
}

// Additionne deux fractions
Fraction operator+(Fraction const& f1, Fraction const& f2) {
    Fraction result = f1;
    result += f2;
    return result;
}

// Soustrait une fraction de l'autre
Fraction operator-(Fraction const& f1, Fraction const& f2) {
    Fraction result = f1;
    result -= f2;
    return result;
}

// Multiplie deux fractions
Fraction operator*(Fraction const& f1, Fraction const& f2) {
    Fraction result = f1;
    result *= f2;
    return result;
}

// Divise une fraction par l'autre
Fraction operator/(Fraction const& f1, Fraction const& f2) {
    Fraction result = f1;
    result /= f2;
    return result;
}

// Convertit la fraction en flottant
float Fraction::to_float() const {
    // Vérifie si le dénominateur est 0
    if (denominator == 0) {
        return 0.0f;
    }
    
    // Effectue la division et retourne un flottant
    return static_cast<float>(numerator) / static_cast<float>(denominator);
}

// Convertit la fraction en flottant via un opérateur
Fraction::operator float() const {
    return to_float();  // Utilise la méthode to_float pour la conversion
}

// Vérifie si deux fractions sont égales
bool operator==(Fraction const& f1, Fraction const& f2) {
    return f1.numerator * f2.denominator == f1.denominator * f2.numerator;
}

// Vérifie si deux fractions sont différentes
bool operator!=(Fraction const& f1, Fraction const& f2) {
    return !(f1 == f2);
}

// Vérifie si une fraction est inférieure à une autre
bool operator<(Fraction const& f1, Fraction const& f2) {
    int sign1 = (f1.denominator > 0) ? 1 : -1;
    int sign2 = (f2.denominator > 0) ? 1 : -1;
    
    // Compare les fractions en tenant compte des signes
    if (sign1 == sign2) {
        return f1.numerator * f2.denominator < f1.denominator * f2.numerator;
    } else {
        return f1.numerator * f2.denominator > f1.denominator * f2.numerator;
    }
}

// Vérifie si une fraction est inférieure ou égale à une autre
bool operator<=(Fraction const& f1, Fraction const& f2) {
    return (f1 < f2) || (f1 == f2);
}

// Vérifie si une fraction est supérieure à une autre
bool operator>(Fraction const& f1, Fraction const& f2) {
    return !(f1 <= f2);
}

// Vérifie si une fraction est supérieure ou égale à une autre
bool operator>=(Fraction const& f1, Fraction const& f2) {
    return !(f1 < f2);
}
