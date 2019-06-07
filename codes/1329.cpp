#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int n, ans;
int x[10005], y[10005];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &x[i], &y[i]);
    sort(y + 1, y + n + 1);
    int midy = y[(n + 1) >> 1];
    sort(x + 1, x + n + 1);
    for (int i = 1; i <= n; i++)
        x[i] -= i;
    sort(x + 1, x + n + 1);
    int  midx = x[(n + 1) >> 1];
    for (int i = 1; i <= n; i++)
        ans += abs(x[i] - midx) + abs(y[i] - midy);
    printf("%d\n", ans);
    return 0;
}