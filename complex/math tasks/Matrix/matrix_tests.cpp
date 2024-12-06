#include <gtest/gtest.h>
#include "Matrix.hpp"
#include <vector>
#include <complex>

using ComplexType = std::complex<double>;

// Test suite for the rowToColumn function
TEST(MatrixTests, RowToColumnTest) {
    // Define the input row of the circulant matrix
    std::vector<ComplexType> firstRow = {ComplexType(1, 0), ComplexType(2, 0), ComplexType(3, 0)};
    // Expected output when converted to the first column
    std::vector<ComplexType> expectedColumn = {ComplexType(1, 0), ComplexType(3, 0), ComplexType(2, 0)};

    // Execute the function
    auto resultColumn = Matrix::rowToColumn(firstRow);

    // Validate the result
    ASSERT_EQ(resultColumn.size(), expectedColumn.size());
    for (size_t i = 0; i < resultColumn.size(); ++i) {
        EXPECT_EQ(resultColumn[i], expectedColumn[i]) << "Mismatch at index " << i;
    }
}

// Test for constructor that reads from a file
TEST(MatrixTests, ConstructorFromFileTest) {
    // Create a temporary test file with sample data
    const std::string testFileName = "test_matrix.txt";
    std::ofstream outFile(testFileName);
    outFile << "Coefficients: 1 2 3 4\n";
    outFile << "Constants: 4 3 2 1\n";
    outFile.close();

    // Initialize the matrix using the file constructor
 Matrix matrix(testFileName);

    // Retrieve coefficients and constants (add getters for this purpose if needed)
    auto coefficients = matrix.getCoefficients(); // Implement getCoefficients()
    auto constants = matrix.getConstants();       // Implement getConstants()

    // Verify the size and values
    ASSERT_EQ(coefficients.size(), 4);
    ASSERT_EQ(constants.size(), 4);

    EXPECT_EQ(coefficients[0], ComplexType(1, 0));
    EXPECT_EQ(coefficients[1], ComplexType(2, 0));
    EXPECT_EQ(coefficients[2], ComplexType(3, 0));
    EXPECT_EQ(coefficients[3], ComplexType(4, 0));

    EXPECT_EQ(constants[0], ComplexType(4, 0));
    EXPECT_EQ(constants[1], ComplexType(3, 0));
    EXPECT_EQ(constants[2], ComplexType(2, 0));
    EXPECT_EQ(constants[3], ComplexType(1, 0));
}

// Test for solving a system of equations
TEST(MatrixTests, SolveTest) {
    // Define coefficients and constants
    std::vector<ComplexType> coefficients = {ComplexType(1, 0), ComplexType(2, 0), ComplexType(1, 0)};
    std::vector<ComplexType> constants = {ComplexType(4, 0), ComplexType(5, 0), ComplexType(6, 0)};

    // Create the matrix
    Matrix matrix(coefficients, constants);

    // Solve the system
    auto solutions = matrix.solve();

    // Verify the solution size
    ASSERT_EQ(solutions.size(), 3);

    // Expected solution (example, adjust based on actual calculation logic)
    std::vector<ComplexType> expectedSolutions = {ComplexType(2, 0), ComplexType(1, 0), ComplexType(3, 0)};

    for (size_t i = 0; i < solutions.size(); ++i) {
        EXPECT_NEAR(solutions[i].real(), expectedSolutions[i].real(), 1e-10);
        EXPECT_NEAR(solutions[i].imag(), expectedSolutions[i].imag(), 1e-10);
    }
}

// Test for FFT and inverse FFT
TEST(MatrixTests, FFTAndInverseFFTTest) {
    // Input vector for FFT
    std::vector<ComplexType> input = {ComplexType(1, 0), ComplexType(2, 0), ComplexType(3, 0), ComplexType(4, 0)};
    std::vector<ComplexType> originalInput = input;

    // Perform FFT
    Matrix matrix({}, {});
    matrix.FastFourierTransform(input);

    // Perform inverse FFT
    matrix.inverseF(input);

    // Validate that the inverse FFT restores the original input
    for (size_t i = 0; i < input.size(); ++i) {
        EXPECT_NEAR(input[i].real(), originalInput[i].real(), 1e-10);
        EXPECT_NEAR(input[i].imag(), originalInput[i].imag(), 1e-10);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
