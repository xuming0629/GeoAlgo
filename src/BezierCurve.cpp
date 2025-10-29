#include "BezierCurve.h"
#include <cmath>

namespace GeoAlgo {

double BezierCurve::binomial(int n, int i) {
    if (i < 0 || i > n) return 0;
    double res = 1;
    for (int k = 1; k <= i; ++k)
        res *= (n - k + 1) / static_cast<double>(k);
    return res;
}

Point2D BezierCurve::evaluate(double u) const {
    int n = static_cast<int>(ctrlPoints.size()) - 1;
    Point2D result(0, 0);
    for (int i = 0; i <= n; ++i) {
        double coeff = binomial(n, i) * std::pow(1 - u, n - i) * std::pow(u, i);
        result = result + ctrlPoints[i] * coeff;
    }
    return result;
}

} // namespace GeoAlgo
