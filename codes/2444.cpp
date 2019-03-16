#include <cstdio>
#include <iostream>
using namespace std;

long long prime[1000005];
long long a, b, n, num;

void calc(long long x) {
    num = 0;
    for (long long i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            prime[num++] = i;
            while (x % i == 0)
                x = x / i;
        }
    }
    if (x > 1)
        prime[num++] = x;
}

long long solve(long long x) {
    long long t, ans = 0;
    long long cnt;
    for (long long i = 1; i < (long long)(1 << num); i++)
    {
        t = 1;
        cnt = 0;
        for (long long j = 0; j < num; j++)
        {
            if ((long long)(1 << j) & i) {
                cnt++;
                t *= prime[j];
            }
        }

        if (cnt & 1)
            ans += x / t;
        else
            ans -= x / t;
    }

    return ans;
}

int main() {
    long long t;
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld%lld%lld", &a, &b, &n);
        calc(n);
        printf("%lld\n", b - (a - 1) - (solve(b) - solve(a - 1)));
    }
    return 0;
}