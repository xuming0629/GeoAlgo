#include <iostream>
#include "PowerBasisCurve1D.h"
#include "PowerBasisCurve2D.h"
#include "PowerBasisCurve3D.h"

int main() {
    // 1D 示例: f(t) = 1 + 2 t + 3 t^2
    PowerBasisCurve1D f1({1.0, 2.0, 3.0});
    f1.print();
    double t = 2.0;
    std::cout << "f1(" << t << ") = " << f1.evaluate(t) << "\n";
    std::cout << "f1'(" << t << ") = " << f1.evaluateDerivative(t) << "\n";

    // 2D 示例: x(t)=1 + t + t^2; y(t)=2 - t
    PowerBasisCurve2D curve2({1.0, 1.0, 1.0}, {2.0, -1.0});
    curve2.print();
    auto p = curve2.evaluate(t);
    std::cout << "curve2(" << t << ") = (" << p.first << "," << p.second << ")\n";
    auto dp = curve2.derivative(t);
    std::cout << "curve2'(" << t << ") = (" << dp.first << "," << dp.second << ")\n";

    // 3D 示例: x(t)=t, y(t)=t^2, z(t)=1
    PowerBasisCurve3D curve3({0.0, 1.0}, {0.0, 0.0, 1.0}, {1.0});
    curve3.print();
    auto q = curve3.evaluate(t);
    std::cout << "curve3(" << t << ") = (" << std::get<0>(q) << "," << std::get<1>(q) << "," << std::get<2>(q) << ")\n";
    auto dq = curve3.derivative(t);
    std::cout << "curve3'(" << t << ") = (" << std::get<0>(dq) << "," << std::get<1>(dq) << "," << std::get<2>(dq) << ")\n";

    return 0;
}
