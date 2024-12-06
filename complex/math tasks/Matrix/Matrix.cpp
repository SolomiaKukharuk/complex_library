#include "Matrix.hpp"
#include <sstream>
#include <chrono>
#include <cmath>
#include <stdexcept>
#include <algorithm>

std::vector<Matrix::ComplexType> Matrix::rowToColumn(const std::vector<ComplexType>& firstRow) {
    if (firstRow.empty()) {
        throw std::invalid_argument("The input row vector is empty.");
    }

    std::vector<ComplexType> firstColumn = firstRow;
    std::reverse(firstColumn.begin() + 1, firstColumn.end());

    return firstColumn;
}

Matrix::Matrix(const std::vector<ComplexType>& coefficients, const std::vector<ComplexType>& constants)
    : coefficients(coefficients), constants(constants) {
    if (coefficients.empty()) {
        throw std::invalid_argument("The coefficients vector is empty.");
    }
    if (constants.empty()) {
        throw std::invalid_argument("The constants vector is empty.");
    }
    if (coefficients.size() != constants.size()) {
        throw std::invalid_argument("The sizes of coefficients and constants vectors must be equal.");
    }
}

Matrix::Matrix(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        throw std::runtime_error("Could not open the file: " + fileName);
    }

    std::vector<ComplexType> mainRow;
    std::vector<ComplexType> freeTerms;

    mainRow.reserve(8);
    freeTerms.reserve(8);

    std::string line;
    if (std::getline(inputFile, line)) {
        size_t delimiterPosition = line.find(':');
        if (delimiterPosition == std::string::npos) {
            throw std::runtime_error("Invalid file format: missing ':' in the coefficients line.");
        }

        std::istringstream streamValues(line.substr(delimiterPosition + 1));
        double value;
        while (streamValues >> value) {
            mainRow.emplace_back(value);
        }
    }

    if (std::getline(inputFile, line)) {
        size_t delimiterPosition = line.find(':');
        if (delimiterPosition == std::string::npos) {
            throw std::runtime_error("Invalid file format: missing ':' in the constants line.");
        }

        std::istringstream streamValues(line.substr(delimiterPosition + 1));
        double value;
        while (streamValues >> value) {
            freeTerms.emplace_back(value);
        }
    }

    if (mainRow.size() != freeTerms.size()) {
        throw std::runtime_error("Mismatch between the number of coefficients and constants in the file.");
    }

    this->coefficients = mainRow;
    this->constants = freeTerms;
    inputFile.close();
}

std::vector<Matrix::ComplexType> Matrix::solve() {
    if (coefficients.empty() || constants.empty()) {
        throw std::logic_error("Coefficients or constants vectors are empty. Cannot solve the system.");
    }

    unsigned long size = coefficients.size();
    std::vector<ComplexType> fftCoefficients = rowToColumn(coefficients);
    fastFourierTransform(fftCoefficients);

    std::vector<ComplexType> fftConstants = constants;
    fastFourierTransform(fftConstants);

    std::vector<ComplexType> fftSolutions(size);
    for (size_t index = 0; index < size; ++index) {
        if (std::abs(fftCoefficients[index]) < 1e-10) {
            throw std::runtime_error("Division by zero encountered during FFT solution computation.");
        }
        fftSolutions[index] = fftConstants[index] / fftCoefficients[index];
    }

    inverseFFT(fftSolutions);

    return fftSolutions;
}

void Matrix::solveAndOutput(const std::string& fileName) {
    if (coefficients.empty() || constants.empty()) {
        throw std::logic_error("Coefficients or constants vectors are empty. Cannot output the solution.");
    }

    std::ofstream outputFile(fileName);
    if (!outputFile) {
        throw std::runtime_error("Could not open the output file: " + fileName);
    }

    auto startTime = std::chrono::high_resolution_clock::now();
    auto solutions = solve();
    auto endTime = std::chrono::high_resolution_clock::now();

    outputFile << "Solutions for the system of linear equations: (";
    for (const ComplexType& solution : solutions) {
        outputFile << solution.real() << ", ";
    }
    outputFile << ")\n\n";

    std::chrono::duration<double> executionTime = endTime - startTime;
    outputFile << "Time consumed solving the system with std::complex: " << executionTime.count() << " seconds\n";

    outputFile << "\nVerification of the solution for the first row:\n";

    double realSum = 0;
    for (size_t index = 0; index < solutions.size(); ++index) {
        double realTerm = coefficients[index].real() * solutions[index].real() -
                          coefficients[index].imag() * solutions[index].imag();
        realSum += realTerm;
    }

    if (std::abs(realSum - constants[0].real()) < 1e-10) {
        outputFile << "Verification PASSED\n";
    } else {
        outputFile << "Verification FAILED\n";
    }

    outputFile << "Expected result: " << constants[0].real() << "\n";
    outputFile << "Actual result: " << realSum << "\n";

    outputFile.close();
}

void Matrix::FastFourierTransform(std::vector<ComplexType>& vector) {
    unsigned long size = vector.size();
    if ((size & (size - 1)) != 0) {
        throw std::invalid_argument("Vector size must be a power of 2 for FFT.");
    }
    if (size <= 1) return;

    std::vector<ComplexType> evenElements(size / 2);
    std::vector<ComplexType> oddElements(size / 2);
    for (size_t index = 0; index < size / 2; ++index) {
        evenElements[index] = vector[index * 2];
        oddElements[index] = vector[index * 2 + 1];
    }

    FastFourierTransform(evenElements);
    FastFourierTransform(oddElements);

    for (size_t index = 0; index < size / 2; ++index) {
        double angle = -2 * M_PI * index / size;
        ComplexType temp = std::polar(1.0, angle) * oddElements[index];
        vector[index] = evenElements[index] + temp;
        vector[index + size / 2] = evenElements[index] - temp;
    }
}

void Matrix::inverseF(std::vector<ComplexType>& vector) {
    unsigned long size = vector.size();
    for (auto& value : vector) {
        value = std::conj(value);
    }

    FastFourierTransform(vector);

    for (auto& value : vector) {
        value = std::conj(value) / static_cast<double>(size);
    }
}
