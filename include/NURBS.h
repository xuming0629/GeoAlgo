#pragma once
#include <vector>

namespace GeoAlgo {

class NURBS {
public:
    NURBS(const std::vector<double>& controlPoints, int degree);

    double evaluate(double u) const;

private:
    std::vector<double> controlPoints_;
    int degree_;
};

} // namespace GeoAlgo
