#include <cstdio>
#include <iostream>
using namespace std;

int n, m;
long long f[105]/*首尾不相同*/, g[105]/*首尾相同*/;

int main() {
    scanf("%d%d", &n, &m);
    f[1] = m;
    g[2] = 0;
    f[2] = m * (m - 1);//初始化
    for (int i = 3; i <= n; i++) {
        f[i] = g[i - 1] * (m - 1) + f[i - 1] * (m - 2);
        g[i] = f[i - 1];
    }
    printf("%d", f[n]);
    return 0;
}