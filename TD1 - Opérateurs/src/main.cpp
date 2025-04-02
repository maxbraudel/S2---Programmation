#include <iostream>
#include "fraction.hpp"

int main()
{
    // EXERCICE 1 & EXERCICE 2 : Opérations & Affichage

    Fraction f1 { 3, 4 };
    Fraction f2 { 1, 2 };

    std::cout << std::endl << "EXERCICE 1 & EXERCICE 2 : Opérations & Affichage\n" << std::endl;
    std::cout << "f1 = " << f1 << " f2 = " << f2 << std::endl;
    Fraction f3 = f1 + f2;
    std::cout << "f1 + f2 = " << f3;
    std::cout << std::endl << "f1 - f2 = " << (f1 - f2);
    std::cout << std::endl << "f1 * f2 = " << (f1 * f2);
    std::cout << std::endl << "f1 / f2 = " << (f1 / f2);
    std::cout << std::endl << "Fraction{1, 6} + Fraction{2, 6} = " << (Fraction{1, 6} + Fraction{2, 6});

    // EXERCICE 3 : Égalités

    Fraction f4 { 1, 2 };
    Fraction f5 { 2, 4 };
    
    std::cout << std::endl << "\n\nEXERCICE 3 : Égalités\n";
    std::cout << std::endl << f4 << " == " << f5 << " ? " << (f4 == f5 ? "true" : "false");  // Should be true
    std::cout << std::endl << f4 << " != " << f5 << " ? " << (f4 != f5 ? "true" : "false");  // Should be false

    Fraction f6 { 3, 5 };
    std::cout << std::endl << f4 << " == " << f6 << " ? " << (f4 == f6 ? "true" : "false");  // Should be false
    std::cout << std::endl << f4 << " != " << f6 << " ? " << (f4 != f6 ? "true" : "false");  // Should be true
    
    // EXERCICE 4 : Comparaisons

    std::cout << std::endl << "\n\nEXERCICE 4 : Comparaisons\n";
    std::cout << std::endl << f4 << " < " << f6 << " ? " << (f4 < f6 ? "true" : "false");  // 1/2 < 3/5 should be true
    std::cout << std::endl << f4 << " <= " << f6 << " ? " << (f4 <= f6 ? "true" : "false");  // 1/2 <= 3/5 should be true
    std::cout << std::endl << f4 << " > " << f6 << " ? " << (f4 > f6 ? "true" : "false");  // 1/2 > 3/5 should be false
    std::cout << std::endl << f4 << " >= " << f6 << " ? " << (f4 >= f6 ? "true" : "false");  // 1/2 >= 3/5 should be false
    
    // Tests avec fractions égales
    std::cout << std::endl << f4 << " < " << f5 << " ? " << (f4 < f5 ? "true" : "false");  // 1/2 < 2/4 should be false
    std::cout << std::endl << f4 << " <= " << f5 << " ? " << (f4 <= f5 ? "true" : "false");  // 1/2 <= 2/4 should be true
    std::cout << std::endl << f4 << " > " << f5 << " ? " << (f4 > f5 ? "true" : "false");  // 1/2 > 2/4 should be false
    std::cout << std::endl << f4 << " >= " << f5 << " ? " << (f4 >= f5 ? "true" : "false");  // 1/2 >= 2/4 should be true
    
    // Tests avec signe négatif
    Fraction f7 { -1, 3 };
    Fraction f8 { 1, -3 };
    Fraction f9 { 2, 3 };

    std::cout << std::endl << f7 << " == " << f8 << " ? " << (f7 == f8 ? "true" : "false");  // -1/3 == 1/-3 should be true
    std::cout << std::endl << f7 << " < " << f9 << " ? " << (f7 < f9 ? "true" : "false");  // -1/3 < 2/3 should be true
    std::cout << std::endl << f9 << " < " << f7 << " ? " << (f9 < f7 ? "true" : "false");  // 2/3 < -1/3 should be false

    // EXERCICE 5 : Opérateurs d'affectation
    std::cout << std::endl << "\n\nEXERCICE 5 : Opérateurs d'affectation\n";
    
    Fraction f10 { 1, 4 };
    std::cout << std::endl << "f10 au départ = " << f10;
    
    f10 += Fraction{1, 4};
    std::cout << std::endl << "Après f10 += 1/4: " << f10;
    
    f10 -= Fraction{1, 8};
    std::cout << std::endl << "Après f10 -= 1/8: " << f10;
    
    f10 *= Fraction{2, 3};
    std::cout << std::endl << "Après f10 *= 2/3: " << f10;
    
    f10 /= Fraction{1, 2};
    std::cout << std::endl << "Après f10 /= 1/2: " << f10;

    // EXERCICE 6 : Conversions

    std::cout << std::endl << "\n\nEXERCICE 6 : Conversions\n";
    
    Fraction f11 { 1, 4 };
    std::cout << std::endl << f11 << " comme float (en utilisant to_float): " << f11.to_float();
    
    // Utilisation de l'opérateur de conversion
    float f11_float = static_cast<float>(f11);
    std::cout << std::endl << f11 << " comme float (en utilisant l'opérateur de conversion): " << f11_float;
    
    std::cout << std::endl << f11 << " multiplié par 2.0: " << (static_cast<float>(f11) * 2.0f);
    
    // Tests avec différentes fractions
    Fraction f12 { 2, 5 };
    std::cout << std::endl << f12 << " comme float: " << static_cast<float>(f12);
    
    Fraction f13 { -3, 4 };
    std::cout << std::endl << f13 << " comme float: " << static_cast<float>(f13);

    return 0;
}
