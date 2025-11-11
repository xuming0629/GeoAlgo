#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

/**
 * @brief Horner 算法（霍纳法）计算多项式值 f(u0)
 *
 * 数学定义：
 *      f(u) = a0 + a1*u + a2*u^2 + ... + an*u^n
 *
 * Horner 递推形式：
 *      f(u) = (...((an*u + a_{n-1})*u + a_{n-2})*u + ... + a0)
 *
 * @param a   多项式系数 [a0, a1, ..., an] （按幂次从低到高）
 * @param u0  计算点
 * @return    f(u0)
 */
double horner(const vector<double>& a, double u0)
{
    double C = 0.0;
    for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i) {
        C = C * u0 + a[i];
    }
    return C;
}

/**
 * @brief Horner 算法计算多项式导数 f'(u0)
 *
 * 数学定义：
 *      f'(u) = a1 + 2a2*u + 3a3*u^2 + ... + n*an*u^{n-1}
 *
 * Horner 递推形式：
 *      f'(u) = (...((n*an)*u + (n-1)*a_{n-1})*u + ... + 1*a1)
 *
 * 实现思路：
 *      先构造导数的系数向量 d[i] = (i+1) * a[i+1]
 *      然后调用 Horner 算法求 f'(u0)
 *
 * @param a   多项式系数 [a0, a1, ..., an]
 * @param u0  计算点
 * @return    f'(u0)
 */
double horner_derivative(const vector<double>& a, double u0)
{
    int n = static_cast<int>(a.size());
    if (n <= 1)
        return 0.0;  // 常数项的导数为 0

    // 构造导数系数向量
    vector<double> d(n - 1);
    for (int i = 1; i < n; ++i) {
        d[i - 1] = i * a[i];
    }

    // 使用 Horner 法计算导数值
    return horner(d, u0);
}

int main()
{
    cout << "==============================\n";
    cout << "  Horner 多项式及导数计算程序 \n";
    cout << "==============================\n\n";

    int n;
    double u0;

    // 输入多项式次数
    cout << "请输入多项式的最高次数 n: ";
    cin >> n;

    // 输入系数
    vector<double> a(n + 1);
    cout << "请输入多项式系数 a0, a1, ..., an (按幂次从低到高):\n";
    for (int i = 0; i <= n; ++i) {
        cin >> a[i];
    }

    // 输入计算点
    cout << "请输入计算点 u0: ";
    cin >> u0;

    // 调用 Horner 算法
    double fval = horner(a, u0);
    double fder = horner_derivative(a, u0);

    // 输出结果
    cout << fixed << setprecision(8);
    cout << "\n--------------------------------\n";
    cout << "  f(" << u0 << ")  = " << fval << endl;
    cout << "  f'(" << u0 << ") = " << fder << endl;
    cout << "--------------------------------\n";

    return 0;
}
