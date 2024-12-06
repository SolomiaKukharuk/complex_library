/*
Description: Header file containing the definition of the Complex class
*/

#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <fstream>
#include <complex> // Standard library for complex numbers

class Complex {
private:
    double real; // Real part of the complex number
    double imag; // Imaginary part of the complex number

public:
    // Constructors
    Complex();
    Complex(double real, double imag);

    // Overloaded operators
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;

    // Methods
    double modulus() const; // Calculates the modulus of the complex number

    // Input/Output
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    friend std::istream& operator>>(std::istream& is, Complex& c);

    // Save to and read from file
    void saveToFile(std::ofstream& file) const;
    static Complex readFromFile(std::ifstream& file);
};

#endif
