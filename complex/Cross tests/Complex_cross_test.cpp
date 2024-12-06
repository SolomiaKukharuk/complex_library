/*
Description: Comparing the results of C (custom and standard libraries) and C++ implementations
*/

#include <iostream>
#include <fstream>
#include <chrono>
#include <complex>       // C++ standard complex library
extern "C" {
    #include "C:\Users\usr\Downloads\complex\C  realisation\Complex.h"  // Include C header file with extern "C" linkage
}
#include "C:\Users\usr\Downloads\complex\C++ realisation\Complex.h" // Include C++ header file

void compareComplexImplementations() {
    // Test complex numbers
    Complex cppComplex1(3.0, 4.0);
    Complex cppComplex2(1.0, 2.0);

    std::complex<double> cppStdComplex1(3.0, 4.0);
    std::complex<double> cppStdComplex2(1.0, 2.0);

    Complex cComplex1 = {3.0, 4.0};
    Complex cComplex2 = {1.0, 2.0};

    // C++ custom implementation
    std::cout << "C++ Custom Implementation Results:\n";
    std::cout << "Addition: " << (cppComplex1 + cppComplex2) << "\n";
    std::cout << "Subtraction: " << (cppComplex1 - cppComplex2) << "\n";
    std::cout << "Multiplication: " << (cppComplex1 * cppComplex2) << "\n";
    std::cout << "Division: " << (cppComplex1 / cppComplex2) << "\n";

    // C++ standard library implementation
    std::cout << "\nC++ Standard Library Implementation Results:\n";
    std::cout << "Addition: " << (cppStdComplex1 + cppStdComplex2) << "\n";
    std::cout << "Subtraction: " << (cppStdComplex1 - cppStdComplex2) << "\n";
    std::cout << "Multiplication: " << (cppStdComplex1 * cppStdComplex2) << "\n";
    std::cout << "Division: " << (cppStdComplex1 / cppStdComplex2) << "\n";

    // C custom implementation
    std::cout << "\nC Custom Implementation Results:\n";
    printComplex(add(cComplex1, cComplex2));
    printComplex(subtract(cComplex1, cComplex2));
    printComplex(multiply(cComplex1, cComplex2));
    printComplex(divide(cComplex1, cComplex2));
}

int main() {
    compareComplexImplementations();
      std::ifstream inputFile("cross_test_input.txt");
    std::ofstream outputFile("cross_test_output.txt");

    if (!inputFile || !outputFile) {
        std::cerr << "Error: Could not open input or output file.\n";
        return 1;
    }

    double real1, imag1, real2, imag2;
    int pairIndex = 0;

    while (inputFile >> real1 >> imag1 >> real2 >> imag2) {
        ++pairIndex;

        // Complex numbers for C++ Custom
        Complex c1(real1, imag1);
        Complex c2(real2, imag2);

        // Complex numbers for C++ Std
        std::complex<double> s1(real1, imag1);
        std::complex<double> s2(real2, imag2);

        // Complex numbers for C Manual
        ComplexManual cManual1 = {real1, imag1};
        ComplexManual cManual2 = {real2, imag2};

        // Measure and compare execution times
        outputFile << "Pair " << pairIndex << ":\n";

        // Addition
        auto start = std::chrono::high_resolution_clock::now();
        auto customAdd = c1 + c2;
        auto end = std::chrono::high_resolution_clock::now();
        auto customTime = std::chrono::duration<double, std::micro>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        auto stdAdd = s1 + s2;
        end = std::chrono::high_resolution_clock::now();
        auto stdTime = std::chrono::duration<double, std::micro>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        auto manualAdd = add(cManual1, cManual2);
        end = std::chrono::high_resolution_clock::now();
        auto manualTime = std::chrono::duration<double, std::micro>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        auto stdCAdd = addStd(cManual1, cManual2);
        end = std::chrono::high_resolution_clock::now();
        auto stdCTime = std::chrono::duration<double, std::micro>(end - start).count();

        // Write addition results
        outputFile << "Addition Results:\n";
        outputFile << "C++ Custom: " << customAdd << " (Time: " << customTime << " µs)\n";
        outputFile << "C++ Std: " << stdAdd << " (Time: " << stdTime << " µs)\n";
        outputFile << "C Manual: (" << manualAdd.real << ", " << manualAdd.imag << ") (Time: " << manualTime << " µs)\n";
        outputFile << "C Std: (" << stdCAdd.real << ", " << stdCAdd.imag << ") (Time: " << stdCTime << " µs)\n";

        // Repeat similar steps for subtraction, multiplication, and division
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
}
