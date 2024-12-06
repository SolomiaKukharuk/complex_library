/*
Description: File for testing the functionality of the Complex class
*/

#include "Complex.h"
#include <fstream>

void manualTest(); // Test using manual input
void fileTest(const std::string& filename); // Test using data from a file

int main() {
    int choice;
    std::cout << "Select test mode:\n1. Manual input(1)\n2. File input(2)\nChoice: ";
    std::cin >> choice;

    if (choice == 1) {
        manualTest();
    } else if (choice == 2) {
        fileTest("Complex__test.dat");
    } else {
        std::cout << "Invalid choice!" << std::endl;
    }

    return 0;
}

void manualTest() {
    // Testing the class with user input
    Complex a, b;
    std::cin >> a >> b;

    std::cout << "Addition: " << (a + b) << std::endl;
    std::cout << "Subtraction: " << (a - b) << std::endl;
    std::cout << "Multiplication: " << (a * b) << std::endl;
    std::cout << "Division: " << (a / b) << std::endl;
}

void fileTest(const std::string& filename) {
    // Testing the class with input from a file
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    Complex a = Complex::readFromFile(inputFile);
    Complex b = Complex::readFromFile(inputFile);
    inputFile.close();

    std::ofstream outputFile("Complex__output.dat");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Cannot open output file!" << std::endl;
        return;
    }

    (a + b).saveToFile(outputFile);
    (a - b).saveToFile(outputFile);
    (a * b).saveToFile(outputFile);
    (a / b).saveToFile(outputFile);

    outputFile.close();
    std::cout << "Results saved to Complex__output.dat" << std::endl;
}
