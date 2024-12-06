#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

// Function to solve a quartic equation using Ferrari's method
void solveQuartic(double a, double b, double c, double d, double e) {
    // First, reduce the quartic equation to a cubic one
    complex<double> p = (3.0*a*c - b*b) / (3.0*a*a);
    complex<double> q = (2.0*b*b*b - 9.0*a*b*c + 27.0*a*a*d) / (27.0*a*a*a);

    complex<double> delta0 = complex<double>(b*b - 3.0*a*c, 0);
    complex<double> delta1 = complex<double>(2.0*b*b*b - 9.0*a*b*c + 27.0*a*a*d, 0);
    complex<double> discriminant = delta1*delta1 - 4.0*delta0*delta0*delta0;

    // Use Cardano's method for the reduced cubic equation
    complex<double> C = pow((delta1 + sqrt(discriminant)) / 2.0, 1.0 / 3.0);  // Use pow for cube root
    complex<double> root1 = -1.0 / (3.0 * a) * (b + C + delta0 / C);

    cout << "Root for the reduced cubic equation: " << root1 << endl;
}

int main() {
    double a, b, c, d, e;
    cout << "Enter the coefficients a, b, c, d, e for the quartic equation ax^4 + bx^3 + cx^2 + dx + e = 0: ";
    cin >> a >> b >> c >> d >> e;

    solveQuartic(a, b, c, d, e);

    return 0;
}
