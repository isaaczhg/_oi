#include <iomanip>
#include <iostream>
using namespace std;

double f[1005][1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, s;
    cin >> n >> s;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= s; j++)
            f[i][j] = 1.0;
    f[n][s] = 0;
    for (int i = n; i >= 0; i--)
        for (int j = s; j >= 0; j--)
            if (i != n || j != s)
                f[i][j] = (n * s + i * (s - j) * f[i][j + 1] +
                           (n - i) * j * f[i + 1][j] +
                           (n - i) * (s - j) * f[i + 1][j + 1]) /
                          (n * s - i * j);
    cout << fixed << setprecision(4) << f[0][0] << "\n";
    return 0;
}