#include <cstdio>
#include <iostream>
#include <map>
using namespace std;

int m, n, A, B, tot, Q;
char s[1005];
map<unsigned long long, int> a;
unsigned long long f[1005][1005], g[1005][1005];
unsigned long long p, q;

int main() {
    scanf("%d%d%d%d", &m, &n, &A, &B);
    for (int i = 1; i <= m; i++) {
        scanf("%s", s + 1);
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i - 1][j] * 131 + f[i][j - 1] * 13331 -
                      f[i - 1][j - 1] * 131 * 13331 + s[j];
        }
    }
    p = 1, q = 1;
    for (int i = 1; i <= A; i++)
        p *= 131;
    for (int i = 1; i <= B; i++)
        q *= 13331;
    for (int i = A; i <= m; i++)
        for (int j = B; j <= n; j++) {
            a[f[i][j] - f[i - A][j] * p - f[i][j - B] * q +
              f[i - A][j - B] * p * q] = tot++;
        }
    scanf("%d", &Q);
    while (Q--) {
        for (int i = 1; i <= A; i++) {
            scanf("%s", s + 1);
            for (int j = 1; j <= B; j++) {
                g[i][j] = g[i - 1][j] * 131 + g[i][j - 1] * 13331 -
                          g[i - 1][j - 1] * 131 * 13331 + s[j];
            }
        }
        if (a[g[A][B]] != 0)
            printf("1\n");
        else
            printf("0\n");
    }
    return 0;
}
