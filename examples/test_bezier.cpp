#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <pybind11/embed.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace std;

/**
 * @brief 计算组合数 C(n, k)
 */
double combination(int n, int k)
{
    if (k < 0 || k > n) return 0.0;
    if (k == 0 || k == n) return 1.0;
    double c = 1.0;
    for (int i = 1; i <= k; ++i)
        c = c * (n - i + 1) / i;
    return c;
}

/**
 * @brief 计算单个 Bernstein 基函数 B_{i,n}(u)
 */
double bernstein(int i, int n, double u)
{
    if (i < 0 || i > n) return 0.0;
    double coeff = combination(n, i);
    return coeff * pow(u, i) * pow(1 - u, n - i);
}

/**
 * @brief 计算所有 Bernstein 基函数
 */
vector<double> bernstein_all(int n, double u)
{
    vector<double> B(n + 1);
    for (int i = 0; i <= n; ++i)
        B[i] = bernstein(i, n, u);
    return B;
}

/**
 * @brief 计算 Bézier 曲线在参数 u 下的点坐标（Bernstein）
 */
vector<double> bezier_point(const vector<vector<double>>& control, double u)
{
    int n = control.size() - 1;
    vector<double> B = bernstein_all(n, u);
    double x = 0.0, y = 0.0;
    for (int i = 0; i <= n; ++i)
    {
        x += B[i] * control[i][0];
        y += B[i] * control[i][1];
    }
    return {x, y};
}

/**
 * @brief 使用 de Casteljau 算法计算 Bézier 曲线点
 * @param control 控制点
 * @param u 参数 (0~1)
 * @return 曲线点 [x, y]
 */
vector<double> deCasteljau(const vector<vector<double>>& control, double u)
{
    int n = control.size();
    vector<vector<double>> temp = control; // 复制控制点

    // 迭代计算
    for (int k = 1; k < n; ++k) {
        for (int i = 0; i < n - k; ++i) {
            temp[i][0] = (1 - u) * temp[i][0] + u * temp[i + 1][0];
            temp[i][1] = (1 - u) * temp[i][1] + u * temp[i + 1][1];
        }
    }
    return temp[0]; // 返回最终点
}

/**
 * @brief 使用 Python 的 matplotlib 绘制 Bézier 曲线并标注控制点
 */
void plot_bezier(py::module_& plt, const vector<vector<double>>& control)
{
    int n = control.size() - 1;
    int N = 100; // 曲线采样点数

    vector<double> xu, yu;
    for (int k = 0; k <= N; ++k)
    {
        double u = static_cast<double>(k) / N;
        vector<double> pt = deCasteljau(control, u); // 使用 de Casteljau
        xu.push_back(pt[0]);
        yu.push_back(pt[1]);
    }

    // 控制点
    vector<double> xc, yc;
    for (auto& p : control)
    {
        xc.push_back(p[0]);
        yc.push_back(p[1]);
    }

    // 绘制控制多边形和曲线
    plt.attr("figure")();
    plt.attr("plot")(xc, yc, "ro--", py::arg("label")="Control Polygon");
    plt.attr("plot")(xu, yu, "b-", py::arg("label")="Bezier Curve");

    // 标注控制点
    for (size_t i = 0; i < control.size(); ++i)
    {
        string label = "P" + to_string(i);
        plt.attr("text")(
            control[i][0] + 0.05, control[i][1] + 0.05,
            label,
            py::arg("fontsize")=10,
            py::arg("color")="black"
        );
    }

    plt.attr("xlabel")("X");
    plt.attr("ylabel")("Y");
    plt.attr("title")("Bezier Curve plotted from C++ via Python (de Casteljau)");
    plt.attr("legend")();
    plt.attr("grid")(true);
    plt.attr("axis")("equal");
}

int main()
{
    cout << "==============================\n";
    cout << " Bézier 曲线计算与可视化程序 \n";
    cout << "==============================\n\n";

    int n;
    cout << "请输入控制点数量 n (例如 4 表示三次曲线): ";
    cin >> n;

    vector<vector<double>> control(n, vector<double>(2));
    cout << "请输入控制点坐标 (x y):\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "P" << i << ": ";
        cin >> control[i][0] >> control[i][1];
    }

    double u = 0.5;
    vector<double> pt1 = bezier_point(control, u);
    vector<double> pt2 = deCasteljau(control, u);

    cout << "\n[Bernstein] u = 0.5 的曲线点: (" << pt1[0] << ", " << pt1[1] << ")\n";
    cout << "[deCasteljau] u = 0.5 的曲线点: (" << pt2[0] << ", " << pt2[1] << ")\n";

    py::scoped_interpreter guard{};
    py::module_ plt = py::module_::import("matplotlib.pyplot");

    plot_bezier(plt, control);
    plt.attr("show")();

    return 0;
}
