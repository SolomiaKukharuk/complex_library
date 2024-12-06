/*
Description: Function definitions for operations with complex numbers
*/

#include "Complex.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Operations for custom Complex structure
Complex add(Complex a, Complex b) {
    Complex result = {a.real + b.real, a.imag + b.imag};
    return result;
}

Complex subtract(Complex a, Complex b) {
    Complex result = {a.real - b.real, a.imag - b.imag};
    return result;
}

Complex multiply(Complex a, Complex b) {
    Complex result = {a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real};
    return result;
}

Complex divide(Complex a, Complex b) {
    double denominator = b.real * b.real + b.imag * b.imag;
    Complex result = {
        (a.real * b.real + a.imag * b.imag) / denominator,
        (a.imag * b.real - a.real * b.imag) / denominator
    };
    return result;
}

double modulus(Complex a) {
    return sqrt(a.real * a.real + a.imag * a.imag);
}

void printComplex(Complex a) {
    printf("Complex number: %.2f + %.2fi\n", a.real, a.imag);
}

Complex readComplex() {
    Complex a;
    printf("Enter real part: ");
    scanf("%lf", &a.real);
    printf("Enter imaginary part: ");
    scanf("%lf", &a.imag);
    return a;
}

void saveToFile(FILE *file, Complex a) {
    fprintf(file, "%.2f %.2f\n", a.real, a.imag);
}

Complex readFromFile(FILE *file) {
    Complex a;
    fscanf(file, "%lf %lf", &a.real, &a.imag);
    return a;
}

// Operations using <complex.h>
double complex addStd(double complex a, double complex b) {
    return a + b;
}

double complex subtractStd(double complex a, double complex b) {
    return a - b;
}

double complex multiplyStd(double complex a, double complex b) {
    return a * b;
}

double complex divideStd(double complex a, double complex b) {
    return a / b;
}
