#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

long long n, sum, ave, ans;
long long a[1000005], f[1000005];

int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        sum += a[i];
    }
    ave = sum / n;
    for (int i = 1; i <= n; i++)
        a[i] -= ave;
    for (int i = 1; i <= n; i++)
        f[i] = f[i - 1] + a[i];
    sort(f + 1, f + n + 1);
    for (int i = 1; i <= n; i++) 
        ans += abs(f[i] - f[(n + 1) >> 1]);
    printf("%lld\n", ans);
    return 0;
}