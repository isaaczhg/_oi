#include <iostream>
#include <cstdio>
using namespace std;

long long p[1005];

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
    printf("%lld", getmax());
    return 0;
}