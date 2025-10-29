#include "NURBS.h"
#include <cassert>
#include <iostream>

int main() {
    GeoAlgo::NURBS nurbs({0, 1, 2}, 2);
    double v = nurbs.evaluate(0.5);
    std::cout << "Test evaluate(0.5) = " << v << std::endl;
    assert(v >= 0 && v <= 2);
    std::cout << "✅ NURBS basic test passed!" << std::endl;
    return 0;
}
