#include "utils.hpp"
#include <cmath>

// Calcul du plus grand commun diviseur
int gcd(int a, int b) {
    // Utilise std::abs pour éviter les nombres négatifs
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        int modulo {a % b};
        a = b;
        b = modulo;
    }

    return a;
}

// Simplifie une fraction en la réduisant
Fraction simplify(Fraction const& f) {
    const int divisor {gcd(f.numerator, f.denominator) };

    return {
        f.numerator / divisor,
        f.denominator / divisor
    };
}

// Simplifie la fraction directement sur la référence
void simplify_ref(Fraction& f) {
    const int divisor { gcd(f.numerator, f.denominator) };
    f.numerator /= divisor;
    f.denominator /= divisor;
}
