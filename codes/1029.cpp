#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

long long k, m, a, b, ans1, ans2, ans3;
long long A[4][4], B[4][4], c[4][4];

long long gcd(long long x, long long y) {
    if (y == 0)
        return x % m;
    else 
        return gcd(y, x % y);
}

void jzcf(long long A[][4], long long B[][4], int u) {
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= 2; i++) 
        for (int j = 1; j <= u; j++)
            for (int k = 1; k <= 2; k++)
                c[i][j] = (c[i][j] + A[i][k] * B[k][j]) % m;
    memcpy(B, c, sizeof(c));
}

long long ksm(long long x) {//快速幂
    A[1][1] = 1, A[1][2] = k, A[2][1] = 1, A[2][2] = 0;
    B[1][1] = 1, B[2][1] = 1;
    while (x) {
        if (x & 1)
            jzcf(A, B, 1);
        jzcf(A, A, 2);
        x = x >> 1;
    }
    return B[1][1] % m;
}

int main() {
    scanf("%lld%lld%lld%lld", &k, &m, &a, &b);
    if (a > 2)
        ans1 = ksm(a - 2);
    else 
        ans1 = 1;
    if (b > 2)
        ans2 = ksm(b - 2);
    else 
        ans2 = 1;
    long long u;
    u = gcd(a, b);
    if (u > 2) 
        ans3 = ksm(u - 2);
    else 
        ans3 = 1;
    printf("%lld\n%lld\n%lld\n", ans1, ans2, ans3);
    return 0;
}