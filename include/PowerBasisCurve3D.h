#ifndef POWER_BASIS_CURVE_3D_H
#define POWER_BASIS_CURVE_3D_H

#include "PowerBasisCurve1D.h"
#include <tuple>

/*
 PowerBasisCurve3D
 - Parametric curve (x(t), y(t), z(t))
 - Internally holds three PowerBasisCurve1D for x,y,z components.
*/
class PowerBasisCurve3D {
public:
    PowerBasisCurve3D() = default;

    PowerBasisCurve3D(const std::vector<double>& x_coeffs,
                      const std::vector<double>& y_coeffs,
                      const std::vector<double>& z_coeffs)
        : x_(x_coeffs), y_(y_coeffs), z_(z_coeffs) {}

    PowerBasisCurve3D(std::initializer_list<double> x_coeffs,
                      std::initializer_list<double> y_coeffs,
                      std::initializer_list<double> z_coeffs)
        : x_(x_coeffs), y_(y_coeffs), z_(z_coeffs) {}

    // Evaluate point (x,y,z)
    std::tuple<double,double,double> evaluate(double t) const {
        return { x_.evaluate(t), y_.evaluate(t), z_.evaluate(t) };
    }

    // First derivative (dx/dt, dy/dt, dz/dt)
    std::tuple<double,double,double> derivative(double t) const {
        return { x_.evaluateDerivative(t), y_.evaluateDerivative(t), z_.evaluateDerivative(t) };
    }

    // Second derivative (d2x/dt2, d2y/dt2, d2z/dt2)
    std::tuple<double,double,double> secondDerivative(double t) const {
        return { x_.evaluateSecondDerivative(t), y_.evaluateSecondDerivative(t), z_.evaluateSecondDerivative(t) };
    }

    void print(std::ostream& os = std::cout) const {
        os << "x(t): "; x_.print(os);
        os << "y(t): "; y_.print(os);
        os << "z(t): "; z_.print(os);
    }

    const PowerBasisCurve1D& xCurve() const { return x_; }
    const PowerBasisCurve1D& yCurve() const { return y_; }
    const PowerBasisCurve1D& zCurve() const { return z_; }

private:
    PowerBasisCurve1D x_;
    PowerBasisCurve1D y_;
    PowerBasisCurve1D z_;
};

#endif // POWER_BASIS_CURVE_3D_H
