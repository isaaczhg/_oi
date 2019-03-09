#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

long long p[1005], ans;

bool insert(long long x) {
    for (int i = 62; i >= 0; i--)
        if (x >> i & 1) {
            if (!p[i]) {
                p[i] = x;
                break;
            }
            x ^= p[i];
        }
    return x > 0;
}

long long getmax() {
    long long res = 0;
    for (int i = 62; i >= 0; i--) {
        if (res < (res ^ p[i]))
            res ^= p[i];
    }
    return res;
}

int main() {
    long long n, x;
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &x);
        insert(x);
    }
    ans = getmax();
    printf("%lld ", ans);
    sort(p, p + 62);
    for (int i = 0; i <= 62; i++)
        if (p[i]) {
            ans ^= p[i];
            break;
        }
    printf("%lld", ans);
    return 0;
}    