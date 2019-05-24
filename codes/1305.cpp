#include <iostream>
#include <cstdio>
using namespace std;

long long mul(long long a, long long b, long long p) {
    long long ans = 0;
    for (; b; b >>= 1) {
        if (b & 1)
            ans = (ans + a) % p;
            a = a * 2 % p;
    }
    return ans;
}

int main() {
    long long a, b, p;
    scanf("%lld%lld%lld", &a, &b, &p);
    printf("%lld\n", mul(a, b, p));
    return 0;
}