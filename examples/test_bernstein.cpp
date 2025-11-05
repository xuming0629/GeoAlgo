#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// ===================== 计算组合数 C(n, k) =====================
long long combination(int n, int k) {
    if (k == 0 || k == n) return 1;
    if (k > n) return 0;
    long long res = 1;
    for (int i = 1; i <= k; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

// ===================== 计算单个 Bernstein =====================
// B_{i,n}(t) = C(n,i) * t^i * (1-t)^(n-i)
double bernstein_single(int n, int i, double t) {
    long long c = combination(n, i);
    return c * pow(t, i) * pow(1 - t, n - i);
}

// ===================== 计算所有 Bernstein =====================
// 返回长度为 n+1 的向量 [B_{0,n}(t), B_{1,n}(t), ..., B_{n,n}(t)]
vector<double> bernstein_all(int n, double t) {
    vector<double> B(n + 1);
    for (int i = 0; i <= n; ++i) {
        B[i] = bernstein_single(n, i, t);
    }
    return B;
}

// ===================== 主函数示例 =====================
int main() {
    int n = 3;
    double t = 0.5;

    cout << "单个 Bernstein:" << endl;
    cout << "B(2," << n << ") = " << bernstein_single(n, 2, t) << endl;

    cout << "\n全部 Bernstein:" << endl;
    vector<double> B = bernstein_all(n, t);
    for (int i = 0; i <= n; ++i) {
        cout << "B(" << i << "," << n << ") = " << B[i] << endl;
    }

    // 验证所有 Bernstein 之和为 1
    double sum = 0;
    for (auto v : B) sum += v;
    cout << "\nΣ B(i," << n << ") = " << sum << endl;

    return 0;
}
