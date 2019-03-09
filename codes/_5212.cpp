#include <iostream>
#include <cstdio>
using namespace std;

long long p[1005];
int cnt = 0;
bool zero;

void insert(long long x) {
    for (int i = 62; i >= 0; i--) {
        if (x & (1ll << i)) {
            if (p[i])
                x ^= p[i];
            else {
                p[i] = x;
                return;
            }
        }
    }
    if (!x)
        zero = true;
    return;
}

void rebuild() {
    for (int i = 62; i >= 0; i--) {
        if (p[i]) {
            for (int j = 62; j >= 0; j--)
                if (i != j && (p[j] & (1ll << i)))
                    p[j] ^= p[i];
        }
    }
    for (int i = 0; i <= 62; i++)
        if (p[i])
            p[cnt++] = p[i];
}

long long query(long long k) {
    if (k > (1ll << cnt))
        return -1;
    if (zero)
        k--;
    long long res = 0;
    for (int i = cnt; i >= 0; i--)
        if (k & (1ll << i))
            res ^= p[i];
    return res;
}

int main() {
    long long m, n, x, k;
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &x);
        insert(x);
    }
    rebuild();
    scanf("%lld", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%lld", &k);
        printf("%lld\n", query(k));
    }
    return 0;
}