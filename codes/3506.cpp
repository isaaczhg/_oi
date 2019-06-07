#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

struct cow {
    long long x, y;
} w[50005];
int n;
long long ans = -0x7fffffff / 2, num;

bool cmp(const cow &x, const cow &y) {
    return x.x - y.y < y.x - x.y;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &w[i].x, &w[i].y);
    sort(w + 1, w + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        ans = max(ans, num - w[i].y);
        num += w[i].x;
    }
    printf("%lld\n", ans);
    return 0;
}