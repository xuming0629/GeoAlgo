#include "PowerBasisCurve.h"
#include "BezierCurve.h"
#include <iostream>

using namespace GeoAlgo;

int main() {
    std::cout << "GeoAlgo Example\n";

    // 幂基曲线示例
    std::vector<Point2D> coeffs = {
        {0, 0}, {1, 2}, {0.5, 0.5}
    };
    PowerBasisCurve powerCurve(coeffs);
    std::cout << "PowerBasisCurve(u=0.5): " << powerCurve.evaluate(0.5) << std::endl;

    // Bezier 曲线示例
    std::vector<Point2D> controlPoints = {
        {0, 0}, {1, 2}, {3, 3}, {4, 0}
    };
    BezierCurve bezier(controlPoints);
    std::cout << "BezierCurve(u=0.5): " << bezier.evaluate(0.5) << std::endl;

    return 0;
}
