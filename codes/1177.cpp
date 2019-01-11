#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

double f[2005][2005], p[2005][2005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, num;
    cin >> n;
    num = 1 << n;
    memset(f, 0, sizeof(f));
    for (int i = 0; i < num; i++)
        f[0][i] = 1;
    for (int i = 0; i < num; i++)
        for (int j = 0; j < num; ++j)
            cin >> p[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < num; j++)
            for (int k = 0; k < num; k++)
                if ((j >> (i - 1)) == ((k >> (i - 1)) ^ 1))
                    f[i][j] += f[i - 1][j] * (f[i - 1][k] * (p[j][k] / 100));
    int ans = 0;
    for (int i = 1; i < num; i++)
        if (f[n][i] > f[n][ans])
            ans = i;
    cout << ans + 1 << "\n";
    return 0;
}