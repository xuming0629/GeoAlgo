#include <pybind11/embed.h>
#include <pybind11/stl.h>   // ⚠️ 必须
#include "BezierCurve.h"
#include "Point2D.h"
#include <vector>
#include <iostream>

namespace py = pybind11;
using namespace GeoAlgo;

int main() {
    py::scoped_interpreter guard{}; // 初始化 Python

    // Bezier 曲线
    std::vector<Point2D> controlPoints = {{0,0}, {1,2}, {3,3}, {4,0}};
    BezierCurve bezier(controlPoints);

    std::vector<double> xs, ys;
    int nSamples = 20;
    for(int i=0; i<=nSamples; ++i){
        double u = static_cast<double>(i)/nSamples;
        Point2D p = bezier.evaluate(u);
        xs.push_back(p.x);
        ys.push_back(p.y);
    }

    // 导入 matplotlib
    py::module_ plt = py::module_::import("matplotlib.pyplot");

    // 绘图
    plt.attr("plot")(xs, ys, "o-", py::arg("label")="Bezier Curve");
    plt.attr("xlabel")("X");
    plt.attr("ylabel")("Y");
    plt.attr("title")("Bezier Curve plotted from C++ via Python");
    plt.attr("legend")();
    plt.attr("grid")(true);
    plt.attr("show")();

    return 0;
}
