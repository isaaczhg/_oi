#include <cstdio>
#include <iostream>
using namespace std;

long long n, m, f[55][55];
int map[55][55];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    char ch;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++) {
            cin >> ch;
            map[i][j] = (ch == '*');
        }
    long long b = f[1][1] = 1ll << n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++) {
            if (map[i][j]) {
                f[i + 1][j] += f[i][j] * 0.5;
                f[i + 1][j + 1] += f[i][j] * 0.5;
            } else
                f[i + 2][j + 1] += f[i][j];
        }
    if (!f[n + 1][m + 1]) {
        cout << "0/1" << "\n";
        return 0;
    }
    while (f[n + 1][m + 1] % 2 == 0) {
        f[n + 1][m + 1] /= 2;
        b /= 2;
    }
    cout << f[n + 1][m + 1] << "/" << b << "\n";
    return 0;
}