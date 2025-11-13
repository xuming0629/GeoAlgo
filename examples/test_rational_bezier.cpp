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
 * @brief 计算有理 Bézier 曲线上的点（支持二维/三维）
 * @param control 控制点坐标
 * @param weights 权重
 * @param u 参数值 [0,1]
 * @return 曲线点坐标
 */
vector<double> rational_bezier_point(const vector<vector<double>>& control, const vector<double>& weights, double u)
{
    int n = control.size() - 1;
    int dim = control[0].size(); // 2 或 3
    vector<double> B = bernstein_all(n, u);

    vector<double> num(dim, 0.0);
    double denom = 0.0;

    for (int i = 0; i <= n; ++i)
    {
        double wB = weights[i] * B[i];
        for (int d = 0; d < dim; ++d)
            num[d] += wB * control[i][d];
        denom += wB;
    }

    for (int d = 0; d < dim; ++d)
        num[d] /= denom;

    return num;
}

/**
 * @brief 绘制二维有理 Bézier 曲线
 */
void plot_rational_bezier_2d(py::module_& plt, const vector<vector<double>>& control, const vector<double>& weights)
{
    int N = 100;
    vector<double> xu, yu;

    for (int k = 0; k <= N; ++k)
    {
        double u = static_cast<double>(k) / N;
        vector<double> pt = rational_bezier_point(control, weights, u);
        xu.push_back(pt[0]);
        yu.push_back(pt[1]);
    }

    vector<double> xc, yc;
    for (auto& p : control)
    {
        xc.push_back(p[0]);
        yc.push_back(p[1]);
    }

    plt.attr("figure")();
    plt.attr("plot")(xc, yc, "ro--", py::arg("label")="Control Polygon");
    plt.attr("plot")(xu, yu, "b-", py::arg("label")="Rational Bézier Curve");

    // 标注控制点
    for (size_t i = 0; i < control.size(); ++i)
    {
        string label = "P" + to_string(i) + "(w=" + to_string(weights[i]) + ")";
        plt.attr("text")(control[i][0] + 0.05, control[i][1] + 0.05, label,
                         py::arg("fontsize")=10, py::arg("color")="black");
    }

    plt.attr("xlabel")("X");
    plt.attr("ylabel")("Y");
    plt.attr("title")("2D Rational Bézier Curve");
    plt.attr("legend")();
    plt.attr("grid")(true);
    plt.attr("axis")("equal");
}

/**
 * @brief 绘制三维有理 Bézier 曲线
 */
void plot_rational_bezier_3d(py::module_& plt, const vector<vector<double>>& control, const vector<double>& weights)
{
    py::module_ mpl_toolkits = py::module_::import("mpl_toolkits.mplot3d");

    py::object fig = plt.attr("figure")();
    py::object ax = fig.attr("add_subplot")(111, py::arg("projection")="3d");

    int N = 100;
    vector<double> xu, yu, zu;
    for (int k = 0; k <= N; ++k)
    {
        double u = static_cast<double>(k) / N;
        vector<double> pt = rational_bezier_point(control, weights, u);
        xu.push_back(pt[0]);
        yu.push_back(pt[1]);
        zu.push_back(pt[2]);
    }

    vector<double> xc, yc, zc;
    for (auto& p : control)
    {
        xc.push_back(p[0]);
        yc.push_back(p[1]);
        zc.push_back(p[2]);
    }

    ax.attr("plot")(xc, yc, zc, "ro--", py::arg("label")="Control Polygon");
    ax.attr("plot")(xu, yu, zu, "b-", py::arg("label")="Rational Bézier Curve");

    // 标注控制点
    for (size_t i = 0; i < control.size(); ++i)
    {
        string label = "P" + to_string(i) + "(w=" + to_string(weights[i]) + ")";
        ax.attr("text")(control[i][0], control[i][1], control[i][2], label);
    }

    ax.attr("set_xlabel")("X");
    ax.attr("set_ylabel")("Y");
    ax.attr("set_zlabel")("Z");
    ax.attr("set_title")("3D Rational Bézier Curve");
    ax.attr("legend")();
    plt.attr("show")();
}

int main()
{
    cout << "==============================\n";
    cout << " 有理 Bézier 曲线计算与可视化程序 (2D / 3D)\n";
    cout << "==============================\n\n";

    int n, dim;
    cout << "请输入控制点数量 n (例如 4 表示三次曲线): ";
    cin >> n;

    cout << "请输入维度 (2 或 3): ";
    cin >> dim;

    vector<vector<double>> control(n, vector<double>(dim));
    vector<double> weights(n);

    if (dim == 2)
    {
        cout << "请输入控制点坐标 (x y) 和权重 w:\n";
        for (int i = 0; i < n; ++i)
        {
            cout << "P" << i << ": ";
            cin >> control[i][0] >> control[i][1] >> weights[i];
        }
    }
    else if (dim == 3)
    {
        cout << "请输入控制点坐标 (x y z) 和权重 w:\n";
        for (int i = 0; i < n; ++i)
        {
            cout << "P" << i << ": ";
            cin >> control[i][0] >> control[i][1] >> control[i][2] >> weights[i];
        }
    }
    else
    {
        cerr << "维度必须为 2 或 3！" << endl;
        return -1;
    }

    double u = 0.5;
    vector<double> pt = rational_bezier_point(control, weights, u);

    cout << "\n在 u = 0.5 时的有理 Bézier 曲线点坐标: ";
    for (double val : pt) cout << val << " ";
    cout << endl;

    py::scoped_interpreter guard{};
    py::module_ plt = py::module_::import("matplotlib.pyplot");

    if (dim == 2)
        plot_rational_bezier_2d(plt, control, weights);
    else
        plot_rational_bezier_3d(plt, control, weights);

    plt.attr("show")();
    return 0;
}
