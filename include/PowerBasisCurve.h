#ifndef GEOALGO_POWER_BASIS_CURVE_H
#define GEOALGO_POWER_BASIS_CURVE_H

#include "Point2D.h"
#include <vector>

namespace GeoAlgo {

/**
 * 幂基曲线（Power Basis Curve）
 * 形如：P(u) = a0 + a1*u + a2*u^2 + ... + an*u^n
 */
class PowerBasisCurve {
public:
    PowerBasisCurve() = default;
    explicit PowerBasisCurve(const std::vector<Point2D>& coefficients)
        : coeffs(coefficients) {}

    // 计算曲线在参数 u 处的点
    Point2D evaluate(double u) const;

private:
    std::vector<Point2D> coeffs;
};

} // namespace GeoAlgo

#endif // GEOALGO_POWER_BASIS_CURVE_H
