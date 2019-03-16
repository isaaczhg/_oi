#include <iostream>
#include <cstdio>
using namespace std;

long long x[105], y[105];
long long n, m;
int k;

long long solve() {
    long long x1, x2, y1, y2, ans = 0;
    for (int i = 1; i < (1 << k); ++i) {
        long long cnt = 0;
        for (int j = 0; j < k; ++j) {
            if ((1 << j) & i) {
                if (!cnt)
                    x1 = x2 = x[j], y1 = y2 = y[j];
                else {
                    x1 = min(x1, x[j]);
                    y1 = min(y1, y[j]);
                    x2 = max(x2, x[j]);
                    y2 = max(y2, y[j]);
                }
                ++cnt;
            }
        }
        long long t = x1 * (n - x2 + 1) * y1 * (m - y2 + 1);
        if (cnt & 1)
            ans += t;
        else
            ans -= t;
    }

    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld%d", &n, &m, &k);
        for (int i = 0; i < k; i++)
            scanf("%lld%lld", &x[i], &y[i]);
        long long ans = (1LL + n) * n * (1LL + m) * m / 4LL - solve();
        printf("%lld\n", ans);
    }
    return 0;
}
