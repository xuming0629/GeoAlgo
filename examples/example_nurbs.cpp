#include "GeoAlgo.h"
#include "NURBS.h"
#include <iostream>

int main() {
    std::cout << GeoAlgo::version() << std::endl;

    std::vector<double> ctrl = {0.0, 1.5, 3.0, 2.0};
    GeoAlgo::NURBS curve(ctrl, 2);

    for (double u = 0; u <= 1.0; u += 0.25) {
        std::cout << "u=" << u << " -> value=" << curve.evaluate(u) << std::endl;
    }

    return 0;
}
