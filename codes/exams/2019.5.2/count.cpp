#include <cstdio>
#include <iostream>
using namespace std;

const int Mod = 124567;
int n, m;
int f[1005][1005];

int main() {
    //freopen("count.in", "r", stdin);
    //freopen("count.out", "w", stdout);
    scanf("%d%d", &n, &m);
    f[1][0] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 0; j <= m; j++)
            if (j < i)
                f[i][j] = (f[i - 1][j] % Mod + f[i][j - 1] % Mod) % Mod;
            else 
                f[i][j] = (f[i - 1][j] % Mod + f[i][j - 1] % Mod - f[i - 1][j - i] % Mod + Mod) % Mod;
    printf("%d\n", f[n][m]);
    return 0;
}