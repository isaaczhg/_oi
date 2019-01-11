#include <cstdio>
#include <iostream>
using namespace std;
int main() {
    int n, a[1005], f[1005] = {0}, maxx = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        f[i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= i - 1; j++)
            if (a[i] >= a[j] && f[j] + 1 > f[i])
                f[i] = f[j] + 1;
    for (int i = 1; i <= n; i++)
        maxx = max(maxx, f[i]);
    printf("%d", maxx);
}
