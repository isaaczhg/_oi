#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

struct point {
    int t, x, y;
} a[10005];
int n, m, ans;
int f[10005];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &a[i].t, &a[i].x, &a[i].y);
    for (int i = 1; i <= m; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++) {
            if ((a[i].t - a[j].t) >= (abs(a[i].x - a[j].x) + abs(a[i].y - a[j].y)))
                f[i] = max(f[i], f[j] + 1);
        }
    }
    for (int i = 1; i <= m; i++)
        ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}