#include "NURBS.h"
#include <stdexcept>

namespace GeoAlgo {

NURBS::NURBS(const std::vector<double>& ctrl, int deg)
    : controlPoints_(ctrl), degree_(deg) {}

double NURBS::evaluate(double u) const {
    // 暂时返回一个简单结果，便于验证工程
    if (controlPoints_.empty()) return 0.0;
    size_t idx = static_cast<size_t>(u * (controlPoints_.size() - 1));
    if (idx >= controlPoints_.size()) idx = controlPoints_.size() - 1;
    return controlPoints_[idx];
}

} // namespace GeoAlgo
