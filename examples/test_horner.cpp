#include <iostream>
#include <vector>
using namespace std;

// Horner 法则求多项式值
double horner(const vector<double>& a, double u0) {
    double C = 0.0;
    for (int i = a.size() - 1; i >= 0; --i) {
        C = C * u0 + a[i];
    }
    return C;
}

int main() {
    int n;
    cout << "输入多项式次数 n: ";
    cin >> n;

    vector<double> a(n + 1);
    cout << "依次输入 " << n + 1 << " 个系数 a0 ~ a" << n << "（空格分隔）: ";
    for (int i = 0; i <= n; ++i)
        cin >> a[i];

    double u0;
    cout << "输入 u0: ";
    cin >> u0;

    double C = horner(a, u0);
    cout << "计算结果 C = " << C << endl;

    return 0;
}
