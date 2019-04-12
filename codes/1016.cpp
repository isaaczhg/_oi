#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int f[15][105][105], t[15];
int n, a, b, c, p1, p2, p3;

int main() {
    int maxx, ans = -0x7fffffff / 2;
    scanf("%d%d%d%d%d%d%d", &a, &b, &c, &p1, &p2, &p3, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &t[i]);
    maxx = min(100 / a, min(100 / b, 100 / c));
    memset(f, -1, sizeof(f));
    f[0][0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= maxx * a; j++)
            for (int k = 0; k <= maxx * b; k++)
                for (int j1 = 0; j1 <= j; j1++)
                    for (int k1 = 0; k1 <= k; k1++)
                        if (f[i - 1][j - j1][k - k1] != -1 &&
                            t[i] - j1 * p1 - k1 * p2 >= 0) {
                            if (f[i][j][k] >= maxx * c)
                                break;
                            f[i][j][k] =
                                max(f[i][j][k],
                                    f[i - 1][j - j1][k - k1] +
                                        (t[i] - j1 * p1 - k1 * p2) / p3);
                        }
    for (int i = 0; i <= maxx * a; i++)
        for (int j = 0; j <= maxx * b; j++)
            ans = max(ans, min(i / a, min(j / b, f[n][i][j] / c)));
    printf("%d\n", ans);
    return 0;
}