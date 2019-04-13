#include <iostream>
#include <cstring>
using namespace std;

int n, numa, numop;
long long a[55], fmax[55][55], fmin[55][55];
bool op[55];
string s;

int main() {
    cin >> n >> s;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '*' || s[i] == '+') {
            if (s[i] == '*')
                op[++numop] = 1;
            else
                op[++numop] = 0; 
        }
        else 
            a[++numa] = s[i] - '0';
    }
    for (int i = 1; i <= numa; i++) {
        a[i + numa] = a[i];
        op[i + numa] = op[i];
    }
    for (int i = 1; i <= numa; i++)
        fmax[i][i] = fmin[i][i] = a[i];
    for (int t = 1; t <= n - 1; t++)
        for (int i = 1; i <= 2 * n - t; i++) {
            int j = i + t;
            for (int k = i; k < j; k++) {
                if (!op[k]) {
                    fmax[i][j] = max(fmax[i][j], fmax[i][k] + fmax[k + 1][j]);
                    fmin[i][j] = min(fmin[i][j], fmin[i][k] + fmin[k + 1][j]);
                } 
                else {
                    fmax[i][j] = max(fmax[i][k] * fmax[k + 1][j], max(fmax[i][k] * fmin[k + 1][j], max(fmin[i][k] * fmax[k + 1][j], fmin[i][k] * fmin[k + 1][j])));
                    fmin[i][j] = min(fmax[i][k] * fmax[k + 1][j], min(fmax[i][k] * fmin[k + 1][j], min(fmin[i][k] * fmax[k + 1][j], fmin[i][k] * fmin[k + 1][j])));
                }
            }
        }
    long long ans = -10000000000LL;
    for (int i = 1; i <= n; i++)
        ans = max(ans, fmax[i][i + n - 1]);
    cout << ans << "\n";
    return 0;
}