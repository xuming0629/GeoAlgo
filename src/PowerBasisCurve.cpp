#include "PowerBasisCurve.h"

namespace GeoAlgo {

Point2D PowerBasisCurve::evaluate(double u) const {
    Point2D result(0, 0);
    double u_power = 1.0;

    for (const auto& c : coeffs) {
        result = result + c * u_power;
        u_power *= u;
    }
    return result;
}

} // namespace GeoAlgo
