#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

// Function to solve a cubic equation using Cardano's method
void solveCubic(double a, double b, double c, double d) {
    // Convert the cubic equation into the form x^3 + px + q = 0
    double p = (3*a*c - b*b) / (3*a*a);
    double q = (2*b*b*b - 9*a*b*c + 27*a*a*d) / (27*a*a*a);

    // Calculate the discriminant
    complex<double> delta0 = complex<double>(b*b - 3*a*c, 0);
    complex<double> delta1 = complex<double>(2*b*b*b - 9*a*b*c + 27*a*a*d, 0);
    complex<double> discriminant = delta1*delta1 - 4.0*delta0*delta0*delta0;

    // Use Cardano's formula to find the root
    complex<double> C = pow((delta1 + sqrt(discriminant)) / 2.0, 1.0 / 3.0);  // Use pow for cube root
    complex<double> root1 = -1.0 / (3.0 * a) * (b + C + delta0 / C);

    // Output the root
    cout << "Root of the equation: " << root1 << endl;
}

int main() {
    double a, b, c, d;
    cout << "Enter the coefficients a, b, c, d for the cubic equation ax^3 + bx^2 + cx + d = 0: ";
    cin >> a >> b >> c >> d;

    solveCubic(a, b, c, d);

    return 0;
}
