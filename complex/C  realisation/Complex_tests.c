/*
Description: File to test the functionality of the implemented functions
*/

#include "Complex.h"
#include <stdlib.h>

void manualTest();                // Test using manual input
void fileTest(const char *filename); // Test using data from a file

int main() {
    int choice;
    printf("Select test mode:\n1. Manual input(1)\n2. File input(2)\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        manualTest();
    } else if (choice == 2) {
        fileTest("Complex_test.dat");
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}

void manualTest() {
    // Testing functions with user input
    Complex a = readComplex();
    Complex b = readComplex();

    printf("Addition: ");
    printComplex(add(a, b));

    printf("Subtraction: ");
    printComplex(subtract(a, b));

    printf("Multiplication: ");
    printComplex(multiply(a, b));

    printf("Division: ");
    printComplex(divide(a, b));
}

void fileTest(const char *filename) {
    // Testing functions with input from a file
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    Complex a = readFromFile(file);
    Complex b = readFromFile(file);
    fclose(file);

    file = fopen("Complex_output.dat", "w");
    if (!file) {
        printf("Error: Cannot open output file!\n");
        return;
    }

    saveToFile(file, add(a, b));
    saveToFile(file, subtract(a, b));
    saveToFile(file, multiply(a, b));
    saveToFile(file, divide(a, b));

    fclose(file);
    printf("Results saved to Complex_output.dat\n");
}
