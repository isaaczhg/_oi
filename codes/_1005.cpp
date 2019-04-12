#include <cstring>
#include <iostream>
using namespace std;
const int Mod = 100000000;

int n, f[205][205][205];
int g1[205], g2[205], g3[205], g[205];
char a[205], b[205], c[205];

int main() {
    cin >> n;
    memset(g, 0, sizeof(g));
    for (int i = 1; i <= n; i++)
        cin >> a[i], g1[i] = g[a[i] - 'a'], g[a[i] - 'a'] = i;
    memset(g, 0, sizeof(g));
    for (int i = 1; i <= n; i++)
        cin >> b[i], g2[i] = g[b[i] - 'a'], g[b[i] - 'a'] = i;
    memset(g, 0, sizeof(g));
    for (int i = 1; i <= n; i++)
        cin >> c[i], g3[i] = g[c[i] - 'a'], g[c[i] - 'a'] = i;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            for (int k = 0; k <= n; k++)
                f[i][j][k] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++) {
                if (a[i] == b[j] && b[j] == c[k]) {
                    f[i][j][k] = f[i - 1][j - 1][k - 1] * 2;
                    if (g1[i] && g2[j] && g3[k])
                        f[i][j][k] -= f[g1[i] - 1][g2[j] - 1][g3[k] - 1];
                } else {
                    f[i][j][k] = f[i - 1][j][k] + f[i][j - 1][k] + f[i][j][k - 1];
                    f[i][j][k] -= f[i - 1][j - 1][k] + f[i][j - 1][k - 1] +
                                  f[i - 1][j][k - 1];
                    f[i][j][k] += f[i - 1][j - 1][k - 1];
                }
                f[i][j][k] = (f[i][j][k] % Mod + Mod) % Mod;
            }
    cout << (f[n][n][n] - 1) % Mod << '\n';
    return 0;
}