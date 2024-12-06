#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <complex>

/**
 * @brief A class for solving linear systems represented by a circulant matrix.
 *        It provides methods to perform calculations and find solutions.
 * @note By default, the matrix is configured to handle a linear system of size \(2^{14} = 16384\).
 *       The code can be modified to support matrices of size \(2^k\) for any \(k\).
 */

class Matrix {

public:

    /**
     * @note The default type used for computations is a complex number with double-precision real and imaginary parts.
     */
    using ComplexType = std::complex<double>;

private:
    /**
     * @var coefficients — a vector containing the coefficients \(A_i\), which represent the first row of the circulant matrix.
     * @var constants — a vector containing the constant terms for the system of linear equations.
     */
    std::vector<ComplexType> coefficients;
    std::vector<ComplexType> constants;

public:

    /**
     * @brief Initializes the circulant matrix using two vectors containing coefficients and constants.
     * @param coefficients — a vector representing the first row of the matrix, containing coefficients \(A_i\).
     * @param constants — a vector containing the constant terms of the linear system.
     */
    Matrix(const std::vector<ComplexType>& coefficients, const std::vector<ComplexType>& constants);

    /**
     * @brief Alternative initialization using a file with matrix coefficients and constants formatted as follows:
     * @example //my_file.txt:
     * [any text followed by a colon]: A1 A2 ... A16384
     * [any text followed by a colon]: b1 b2 ... b16384
     * @see GenerateCirculantMatrix.cpp
     * @param fileName — the name of the file containing the coefficients.
     */
    Matrix(const std::string& fileName); //NOLINT

    /**
     * @brief Computes the solution vector for the given system of equations.
     * @note This method internally uses the \texttt{fastFourierTransform()} and \texttt{inverseFFT()} functions.
     * @return A vector containing the solutions to the system of equations.
     */
    std::vector<ComplexType> solve();

    /**
     * @brief Outputs the computed solutions to a specified file.
     * @param fileName — the name of the file where the solutions will be saved.
     */
    void solveAndOutput(const std::string& fileName);

    /**
     * @brief A debug method for outputting the constants vector.
     */
    void debugOutput() { // DEBUG METHOD
        for (ComplexType constant : constants) {
            std::cout << constant << std::endl;
        }
        std::cout << constants.size() << std::endl;
    }

    /**
     * @brief Converts the first row of a circulant matrix (\(coefficients\)) into its equivalent first column.
     *        This conversion is useful for calculating the eigenvalues of the matrix.
     * @param firstRow — a vector representing the first row, to be transformed into column format.
     * @return A vector representing the first column of the circulant matrix.
     */
    static std::vector<ComplexType> rowToColumn(const std::vector<ComplexType>& firstRow);

private:

    /**
     * @brief Performs the Fast Fourier Transform using the Cooley-Tukey algorithm.
     * @param vec — the vector to be transformed from the time domain to the frequency domain.
     */
    void FastFourierTransform(std::vector<ComplexType>& vec);

    /**
     * @brief Performs the Inverse Fast Fourier Transform using the Cooley-Tukey algorithm.
     * @param vec — the vector to be transformed from the frequency domain back to the time domain.
     */
    void inverseF(std::vector<ComplexType>& vec);

};
