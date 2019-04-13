#include <iostream>
#include <cstdio>
using namespace std;

int n, m;
long long ans;
long long f[55][55];

int main() {
    scanf("%d%d", &n, &m);
    f[1][0] = 1;
    f[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < m; j++)
            f[i][0] += f[i - 1][j];
        for (int j = 1; j < m; j++)
            f[i][j] = f[i - 1][j - 1];
    }
    for (int i = 0; i < m; i++)
        ans += f[n][i];
    printf("%lld", ans);
    return 0;
}