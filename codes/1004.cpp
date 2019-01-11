#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int main() {
    int x, n, maxx, a[5005], f[5005], ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        maxx = 0;
        for (int j = 1; j <= n; j++)
            if (a[j] == x)
                f[j] = maxx + 1;
            else if (a[j] < x)
                maxx = max(maxx, f[j]);
    }
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i]);
    printf("%d", ans);
}