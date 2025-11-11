#ifndef POWER_BASIS_CURVE_1D_H
#define POWER_BASIS_CURVE_1D_H

#include <vector>
#include <iostream>
#include <initializer_list>
#include <cmath>
#include <stdexcept>

/*
 PowerBasisCurve1D
 - coefficients stored from low power to high power:
   coeffs_[i] corresponds to a_i * t^i
 - evaluate(t) uses Horner algorithm
 - derivative() returns a PowerBasisCurve1D object for f'(t)
*/
class PowerBasisCurve1D {
public:
    PowerBasisCurve1D() = default;

    explicit PowerBasisCurve1D(const std::vector<double>& coeffs)
        : coeffs_(coeffs) {}

    PowerBasisCurve1D(std::initializer_list<double> coeffs)
        : coeffs_(coeffs) {}

    // degree = highest exponent (coeffs_.size()-1), returns -1 for empty
    int degree() const { return static_cast<int>(coeffs_.size()) - 1; }

    const std::vector<double>& coefficients() const { return coeffs_; }

    // Horner algorithm for polynomial evaluation
    double evaluate(double t) const {
        if (coeffs_.empty()) return 0.0;
        // Horner from highest to lowest
        double result = 0.0;
        for (int i = degree(); i >= 0; --i) {
            result = result * t + coeffs_[i];
        }
        return result;
    }

    // build derivative polynomial coefficients and return new curve
    PowerBasisCurve1D derivative() const {
        int n = static_cast<int>(coeffs_.size());
        if (n <= 1) {
            return PowerBasisCurve1D(std::vector<double>{0.0});
        }
        std::vector<double> dcoeffs(n - 1);
        for (int i = 1; i < n; ++i) dcoeffs[i-1] = i * coeffs_[i];
        return PowerBasisCurve1D(dcoeffs);
    }

    PowerBasisCurve1D secondDerivative() const {
        return derivative().derivative();
    }

    // Evaluate derivative at t (efficiently): form derivative polynomial and Horner-eval it
    double evaluateDerivative(double t) const {
        return derivative().evaluate(t);
    }

    double evaluateSecondDerivative(double t) const {
        return secondDerivative().evaluate(t);
    }

    void print(std::ostream& os = std::cout) const {
        if (coeffs_.empty()) {
            os << "0\n";
            return;
        }
        os << "f(t) = ";
        for (int i = degree(); i >= 0; --i) {
            os << coeffs_[i];
            if (i > 0) os << " t^" << i << " + ";
        }
        os << '\n';
    }

private:
    std::vector<double> coeffs_;
};

#endif // POWER_BASIS_CURVE_1D_H
