#pragma once
#include <iostream>

struct Fraction {
    int numerator { 0 };
    int denominator { 1 };
    
    // Opérateurs d'affectation
    Fraction& operator+=(Fraction const& f);
    Fraction& operator-=(Fraction const& f);
    Fraction& operator*=(Fraction const& f);
    Fraction& operator/=(Fraction const& f);
    
    // Méthodes de conversion
    float to_float() const;
    operator float() const;
};

// Opérateur pour afficher une fraction
std::ostream& operator<<(std::ostream& os, Fraction const& f);

// Opérateurs pour les opérations arithmétiques
Fraction operator+(Fraction const& f1, Fraction const& f2);
Fraction operator-(Fraction const& f1, Fraction const& f2);
Fraction operator*(Fraction const& f1, Fraction const& f2);
Fraction operator/(Fraction const& f1, Fraction const& f2);

// Opérateurs de comparaison
bool operator==(Fraction const& f1, Fraction const& f2);
bool operator!=(Fraction const& f1, Fraction const& f2);
bool operator<(Fraction const& f1, Fraction const& f2);
bool operator<=(Fraction const& f1, Fraction const& f2);
bool operator>(Fraction const& f1, Fraction const& f2);
bool operator>=(Fraction const& f1, Fraction const& f2);
