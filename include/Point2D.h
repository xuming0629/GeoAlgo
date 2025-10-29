#ifndef GEOALGO_POINT2D_H
#define GEOALGO_POINT2D_H

#include <cmath>
#include <iostream>

namespace GeoAlgo {

struct Point2D {
    double x{0.0};
    double y{0.0};

    Point2D() = default;
    Point2D(double x_, double y_) : x(x_), y(y_) {}

    // 加法
    Point2D operator+(const Point2D& other) const {
        return {x + other.x, y + other.y};
    }

    // 减法
    Point2D operator-(const Point2D& other) const {
        return {x - other.x, y - other.y};
    }

    // 乘标量
    Point2D operator*(double scalar) const {
        return {x * scalar, y * scalar};
    }

    // 除标量
    Point2D operator/(double scalar) const {
        return {x / scalar, y / scalar};
    }

    // 输出
    friend std::ostream& operator<<(std::ostream& os, const Point2D& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    // 距离
    double distanceTo(const Point2D& other) const {
        return std::hypot(x - other.x, y - other.y);
    }
};

} // namespace GeoAlgo

#endif // GEOALGO_POINT2D_H
