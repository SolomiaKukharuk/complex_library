/*
Description: Implementation of the Complex class and its methods
*/

#include "Complex.h"
#include <cmath>

// Constructors
Complex::Complex() : real(0), imag(0) {} // Default constructor
Complex::Complex(double real, double imag) : real(real), imag(imag) {} // Parameterized constructor

// Overloaded operators
Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.imag * other.imag;
    return Complex(
        (real * other.real + imag * other.imag) / denominator,
        (imag * other.real - real * other.imag) / denominator
    );
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

// Methods
double Complex::modulus() const {
    return sqrt(real * real + imag * imag);
}

// Input/Output
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real << " + " << c.imag << "i";
    return os;
}

std::istream& operator>>(std::istream& is, Complex& c) {
    std::cout << "Enter real part: ";
    is >> c.real;
    std::cout << "Enter imaginary part: ";
    is >> c.imag;
    return is;
}

// Save to and read from file
void Complex::saveToFile(std::ofstream& file) const {
    file << real << " " << imag << std::endl;
}

Complex Complex::readFromFile(std::ifstream& file) {
    double real, imag;
    file >> real >> imag;
    return Complex(real, imag);
}
