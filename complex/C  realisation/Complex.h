/*
Description: Header file containing the definition of the Complex structure and function prototypes
*/

#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>
#include <complex.h>
#include <tgmath.h>

typedef struct {
    double real; // Real part of the complex number
    double imag; // Imaginary part of the complex number
} Complex;

// Function prototypes
Complex add(Complex a, Complex b);          // Adds two complex numbers
Complex subtract(Complex a, Complex b);     // Subtracts two complex numbers
Complex multiply(Complex a, Complex b);     // Multiplies two complex numbers
Complex divide(Complex a, Complex b);       // Divides two complex numbers
double modulus(Complex a);                  // Calculates the modulus of a complex number
void printComplex(Complex a);               // Prints a complex number
Complex readComplex();                      // Reads a complex number from user input
void saveToFile(FILE *file, Complex a);     // Saves a complex number to a file
Complex readFromFile(FILE *file);           // Reads a complex number from a file

// Functions using <complex.h>
double complex addStd(double complex a, double complex b);
double complex subtractStd(double complex a, double complex b);
double complex multiplyStd(double complex a, double complex b);
double complex divideStd(double complex a, double complex b);

#endif
