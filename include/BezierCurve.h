#ifndef GEOALGO_BEZIER_CURVE_H
#define GEOALGO_BEZIER_CURVE_H

#include "Point2D.h"
#include <vector>

namespace GeoAlgo {

/**
 * 贝塞尔曲线（Bezier Curve）
 * 定义：P(u) = Σ B_i^n(u) * P_i
 * 其中 B_i^n(u) = C(n,i) * (1-u)^(n-i) * u^i
 */
class BezierCurve {
public:
    BezierCurve() = default;
    explicit BezierCurve(const std::vector<Point2D>& controlPoints)
        : ctrlPoints(controlPoints) {}

    Point2D evaluate(double u) const;

private:
    std::vector<Point2D> ctrlPoints;
    static double binomial(int n, int i);
};

} // namespace GeoAlgo

#endif // GEOALGO_BEZIER_CURVE_H
