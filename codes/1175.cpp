#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

int fly[100005];
double f[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, x, y;
    while (cin >> n >> m) {
        if (!n && !m)
            break;
        memset(fly, -1, sizeof(fly));
        for (int i = 0; i <= n; i++)
            f[i] = 0.0;
        for (int i = 1; i <= m; i++) {
            cin >> x >> y;
            fly[x] = y;
        }
        f[n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (fly[i] != -1)
                f[i] = f[fly[i]];
            else {
                for (int j = 1; j <= 6; j++) {
                    if (i + j >= n)
                        f[i] += 1.0 / 6 * f[n];
                    else
                        f[i] += 1.0 / 6 * f[i + j];
                }
                f[i]++;
            }
        }
        cout << fixed << setprecision(4) << f[0] << "\n";
    }
    return 0;
}