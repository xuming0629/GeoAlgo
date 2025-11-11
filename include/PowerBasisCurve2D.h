#ifndef POWER_BASIS_CURVE_2D_H
#define POWER_BASIS_CURVE_2D_H

#include "PowerBasisCurve1D.h"
#include <utility>

/*
 PowerBasisCurve2D
 - Parametric curve (x(t), y(t))
 - Internally holds two PowerBasisCurve1D for x and y components.
 - evaluate(t) -> std::pair<double,double>
 - derivative(t) gives first derivative (dx/dt, dy/dt)
 - secondDerivative(t) gives second derivative (d2x/dt2, d2y/dt2)
*/
class PowerBasisCurve2D {
public:
    PowerBasisCurve2D() = default;

    // Construct from two coefficient vectors: x_coeffs, y_coeffs
    PowerBasisCurve2D(const std::vector<double>& x_coeffs, const std::vector<double>& y_coeffs)
        : x_(x_coeffs), y_(y_coeffs) {}

    // Construct from initializer lists
    PowerBasisCurve2D(std::initializer_list<double> x_coeffs, std::initializer_list<double> y_coeffs)
        : x_(x_coeffs), y_(y_coeffs) {}

    // Evaluate point (x(t), y(t))
    std::pair<double,double> evaluate(double t) const {
        return { x_.evaluate(t), y_.evaluate(t) };
    }

    // First derivative (dx/dt, dy/dt)
    std::pair<double,double> derivative(double t) const {
        return { x_.evaluateDerivative(t), y_.evaluateDerivative(t) };
    }

    // Second derivative (d2x/dt2, d2y/dt2)
    std::pair<double,double> secondDerivative(double t) const {
        return { x_.evaluateSecondDerivative(t), y_.evaluateSecondDerivative(t) };
    }

    // Access sub-curves
    const PowerBasisCurve1D& xCurve() const { return x_; }
    const PowerBasisCurve1D& yCurve() const { return y_; }

    void print(std::ostream& os = std::cout) const {
        os << "x(t): "; x_.print(os);
        os << "y(t): "; y_.print(os);
    }

private:
    PowerBasisCurve1D x_;
    PowerBasisCurve1D y_;
};

#endif // POWER_BASIS_CURVE_2D_H
