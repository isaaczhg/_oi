#include <iostream>
#include <cstdio>
using namespace std;

int n, R, r, c, maxn;
int s[5005][5005];

int main() {
    int x, y, v;
    scanf("%d%d", &n, &R);
    r = c = R;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &x, &y, &v);
        s[++x][++y] = v;
        r = max(x, r);
        c = max(y, c);
    }
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    maxn = 0;
    for (int i = R; i <= r; i++)
        for (int j = R; j <= c; j++) {
            maxn = max(maxn, s[i][j] - s[i - R][j] - s[i][j - R] + s[i - R][j - R]);
        }
    printf("%d\n", maxn);
    return 0;
}